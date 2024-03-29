//------------------------------------------------------------------------------
// File Name:	GameStateThursday.c
// Project:		What The Food is Going On!
// Author(s): Joe Centeno
//
// All content � 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameStateThursday.h"
#include "LevelFunctions.h"

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void GameStateThursdayLoad()
{

}

// Initialize the ...
void GameStateThursdayInit()
{
    ThursdayInit();
    LevelInit();
}

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateThursdayUpdate(float dt)
{    
    LevelUpdate(dt);
}

// Shutdown the ...
void GameStateThursdayShutdown()
{
    LevelShutdown();
}

void GameStateThursdayUnload()
{

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------
