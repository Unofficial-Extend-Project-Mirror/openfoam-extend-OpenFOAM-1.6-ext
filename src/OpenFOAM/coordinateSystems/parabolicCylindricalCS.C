/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software; you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation; either version 2 of the License, or (at your
    option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM; if not, write to the Free Software Foundation,
    Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

\*---------------------------------------------------------------------------*/

#include "parabolicCylindricalCS.H"
#include "mathematicalConstants.H"
#include "Switch.H"
#include "boundBox.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(parabolicCylindricalCS, 0);
    addToRunTimeSelectionTable
    (
        coordinateSystem,
        parabolicCylindricalCS,
        dictionary
    );
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::parabolicCylindricalCS::parabolicCylindricalCS(const bool inDegrees)
:
    coordinateSystem(),
    inDegrees_(inDegrees)
{}


Foam::parabolicCylindricalCS::parabolicCylindricalCS
(
    const word& name,
    const point& origin,
    const coordinateRotation& cr,
    const bool inDegrees
)
:
    coordinateSystem(name, origin, cr),
    inDegrees_(inDegrees)
{}


Foam::parabolicCylindricalCS::parabolicCylindricalCS
(
    const word& name,
    const dictionary& dict
)
:
    coordinateSystem(name, dict),
    inDegrees_(dict.lookupOrDefault<Switch>("degrees", true))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::coordinateSystem::spanInfo
Foam::parabolicCylindricalCS::spanLimited() const
{
    spanInfo b(Pair<bool>(true, true));

    // Upper bound or r is unlimited
    b[0] = Pair<bool>(true, false);

    // z is unlimited
    b[2] = Pair<bool>(false, false);

    return b;
}


Foam::boundBox Foam::parabolicCylindricalCS::spanBounds() const
{
    return boundBox
    (
        vector
        (
            0,
            ( inDegrees_ ? -180.0 : -mathematicalConstant::pi ),
            -GREAT
        ),
        vector
        (
            GREAT,
            ( inDegrees_ ? 180.0 : mathematicalConstant::pi ),
            GREAT
        )
    );
}


bool Foam::parabolicCylindricalCS::inDegrees() const
{
    return inDegrees_;
}


bool& Foam::parabolicCylindricalCS::inDegrees()
{
    return inDegrees_;
}


Foam::vector Foam::parabolicCylindricalCS::localToGlobal
(
    const vector& local,
    bool translate
) const
{
    // Notation: u = local.x() v = local.y() z = local.z();
    if (local.y() < 0.0)
    {
        FatalErrorIn
        (
            "parabolicCylindricalCS::localToGlobal(const vector&, bool) const"
        )
            << "parabolic cylindrical coordinates v < 0"
            << abort(FatalError);
    }

    return coordinateSystem::localToGlobal
    (
        vector
        (
            0.5*(sqr(local.x()) - sqr(local.y())),
            local.x()*local.y(),
            local.z()
        ),
        translate
    );
}


Foam::tmp<Foam::vectorField> Foam::parabolicCylindricalCS::localToGlobal
(
    const vectorField& local,
    bool translate
) const
{
    if (min(local.component(vector::Y)) < 0.0)
    {
        FatalErrorIn
        (
            "parabolicCylindricalCS::localToGlobal"
            "(const vectorField&, bool) const"
        )   << "parabolic cylindrical coordinates v < 0"
            << abort(FatalError);
    }

    vectorField lc(local.size());
    lc.replace
    (
        vector::X,
        0.5*
        (
            sqr(local.component(vector::X))
          - sqr(local.component(vector::Y))
        )
    );

    lc.replace
    (
        vector::Y,
        local.component(vector::X) * local.component(vector::Y)
    );

    lc.replace
    (
        vector::Z,
        local.component(vector::Z)
    );

    return coordinateSystem::localToGlobal(lc, translate);
}


Foam::vector Foam::parabolicCylindricalCS::globalToLocal
(
    const vector& global,
    bool translate
) const
{
    notImplemented
    (
        "parabolicCylindricalCS::globalToLocal(const vector&, bool) const"
    );

    return vector::zero;
}

Foam::tmp<Foam::vectorField> Foam::parabolicCylindricalCS::globalToLocal
(
    const vectorField& global,
    bool translate
) const
{
    notImplemented
    (
        "parabolicCylindricalCS::globalToLocal(const vectorField&, bool) const"
    );

    return tmp<vectorField>(vectorField::null());
}


// ************************************************************************* //