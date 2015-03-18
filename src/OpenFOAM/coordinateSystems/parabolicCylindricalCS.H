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

Class
    Foam::parabolicCylindricalCS

Description
    Parabolic cylindrical coordinate system.

    Notation: u = a.x() v = a.y() z = a.z();

Note
    The maintenance of this class may lag that of the main types.

SourceFiles
    parabolicCylindricalCS.C

\*---------------------------------------------------------------------------*/

#ifndef parabolicCylindricalCS_H
#define parabolicCylindricalCS_H

#include "coordinateSystem.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                   Class parabolicCylindricalCS Declaration
\*---------------------------------------------------------------------------*/

class parabolicCylindricalCS
:
    public coordinateSystem
{
    // Private data members

        //- Are angles in degrees? (default = true)
        bool inDegrees_;


protected:

    // Protected Member Functions

        //- Convert from local coordinate system to the global Cartesian system
        //  with optional translation for the origin
        virtual vector localToGlobal(const vector&, bool translate) const;

        //- Convert from local coordinate system to the global Cartesian system
        //  with optional translation for the origin
        virtual tmp<vectorField> localToGlobal
        (
            const vectorField&,
            bool translate
        ) const;

        //- Convert from global Cartesian system to the local coordinate system
        //  with optional translation for the origin
        virtual vector globalToLocal(const vector&, bool translate) const;

        //- Convert from global Cartesian system to the local coordinate system
        //  with optional translation for the origin
        virtual tmp<vectorField> globalToLocal
        (
            const vectorField&,
            bool translate
        ) const;

public:

    //- Runtime type information
    TypeName("parabolicCylindrical");


    // Constructors

        //- Construct null
        parabolicCylindricalCS(const bool inDegrees = true);

        //- Construct from origin and rotation
        parabolicCylindricalCS
        (
            const word& name,
            const point& origin,
            const coordinateRotation&,
            const bool inDegrees = true
        );

        //- Construct from dictionary
        parabolicCylindricalCS(const word&, const dictionary&);

        //- Return clone
        virtual autoPtr<coordinateSystem> clone() const
        {
            return autoPtr<coordinateSystem>(new parabolicCylindricalCS(*this));
        }


    // Member Functions

        // Global information about the coordinate system

            //- Directions in which the span is limited
            virtual spanInfo spanLimited() const;

            //- Span bounds
            virtual boundBox spanBounds() const;


        //- Are angles in degrees?
        bool  inDegrees() const;

        //- Non-const access to inDegrees
        bool& inDegrees();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //