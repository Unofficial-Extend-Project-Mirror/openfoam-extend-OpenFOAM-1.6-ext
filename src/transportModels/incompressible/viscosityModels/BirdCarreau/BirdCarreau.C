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

#include "BirdCarreau.H"
#include "addToRunTimeSelectionTable.H"
#include "surfaceFields.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
namespace viscosityModels
{
    defineTypeNameAndDebug(BirdCarreau, 0);
    addToRunTimeSelectionTable
    (
        viscosityModel,
        BirdCarreau,
        dictionary
    );
}
}


// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

Foam::tmp<Foam::volScalarField>
Foam::viscosityModels::BirdCarreau::calcNu() const
{
    return
        nuInf_
      + (nu0_ - nuInf_)
       *pow(scalar(1) + sqr(k_*strainRate()), (n_ - 1.0)/2.0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::viscosityModels::BirdCarreau::BirdCarreau
(
    const word& name,
    const dictionary& viscosityProperties,
    const volVectorField& U,
    const surfaceScalarField& phi
)
:
    viscosityModel(name, viscosityProperties, U, phi),
    BirdCarreauCoeffs_(viscosityProperties.subDict(typeName + "Coeffs")),
    nu0_(BirdCarreauCoeffs_.lookup("nu0")),
    nuInf_(BirdCarreauCoeffs_.lookup("nuInf")),
    k_(BirdCarreauCoeffs_.lookup("k")),
    n_(BirdCarreauCoeffs_.lookup("n")),
    nu_
    (
        IOobject
        (
            "nu",
            U_.time().timeName(),
            U_.db(),
            IOobject::NO_READ,
            IOobject::AUTO_WRITE
        ),
        calcNu()
    )
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool Foam::viscosityModels::BirdCarreau::read
(
    const dictionary& viscosityProperties
)
{
    viscosityModel::read(viscosityProperties);

    BirdCarreauCoeffs_ = viscosityProperties.subDict(typeName + "Coeffs");

    BirdCarreauCoeffs_.lookup("nu0") >> nu0_;
    BirdCarreauCoeffs_.lookup("nuInf") >> nuInf_;
    BirdCarreauCoeffs_.lookup("k") >> k_;
    BirdCarreauCoeffs_.lookup("n") >> n_;

    return true;
}


// ************************************************************************* //
