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

#include "systemCall.H"
#include "dictionary.H"
#include "Time.H"

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(systemCall, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::systemCall::systemCall
(
    const word& name,
    const objectRegistry&,
    const dictionary& dict,
    const bool
)
:
    name_(name),
    executeCalls_(),
    endCalls_(),
    writeCalls_()
{
    read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::systemCall::~systemCall()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::systemCall::read(const dictionary& dict)
{
    dict.readIfPresent("executeCalls", executeCalls_);
    dict.readIfPresent("endCalls",     endCalls_);
    dict.readIfPresent("writeCalls",   writeCalls_);

    if (executeCalls_.empty() && endCalls_.empty() && writeCalls_.empty())
    {
        WarningIn("Foam::system::read(const dictionary&)")
            << "no executeCalls, endCalls or writeCalls defined."
            << endl;
    }
}


void Foam::systemCall::execute()
{
    forAll(executeCalls_, callI)
    {
        ::system(executeCalls_[callI].c_str());
    }
}


void Foam::systemCall::end()
{
    forAll(endCalls_, callI)
    {
        ::system(endCalls_[callI].c_str());
    }
}


void Foam::systemCall::write()
{
    forAll(writeCalls_, callI)
    {
        ::system(writeCalls_[callI].c_str());
    }
}


// ************************************************************************* //
