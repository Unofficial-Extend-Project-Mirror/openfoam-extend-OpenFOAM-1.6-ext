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
    Foam::linearValveFvMesh

Description
    Linear valve mesh with sliding interface and mesh motion.

SourceFiles
    linearValveFvMesh.C

\*---------------------------------------------------------------------------*/

#ifndef linearValveFvMesh_H
#define linearValveFvMesh_H

#include "topoChangerFvMesh.H"
#include "motionSolver.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                       Class linearValveFvMesh Declaration
\*---------------------------------------------------------------------------*/

class linearValveFvMesh
:
    public topoChangerFvMesh
{
    // Private data

        //- Motion dictionary
        dictionary motionDict_;

        //- Motion solver
        autoPtr<motionSolver> msPtr_;


    // Private Member Functions

        //- Disallow default bitwise copy construct
        linearValveFvMesh(const linearValveFvMesh&);

        //- Disallow default bitwise assignment
        void operator=(const linearValveFvMesh&);


        //- Add linearValve zones and modifiers
        void addZonesAndModifiers();

        //- Make sliding modifiers live
        void makeSlidersDead();

        //- Make sliding modifiers live
        void makeSlidersLive();

        //- Return true if sliders are attached
        bool attached() const;


public:

    //- Runtime type information
    TypeName("linearValveFvMesh");


    // Constructors

        //- Construct from database
        explicit linearValveFvMesh(const IOobject& io);


    // Destructor

        virtual ~linearValveFvMesh();


    // Member Functions

        //- Update the mesh for both mesh motion and topology change
        virtual bool update();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
