//------------------------------------------------------------------------------
// File Name:	GameStateThursday.h
// Project:		What The Food is Going On!
// Author(s): Joe Centeno
//
// All content � 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
	/* Assume C declarations for C++ */
#endif

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

	void GameStateThursdayLoad();
// Initialize the ...
void GameStateThursdayInit();

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateThursdayUpdate(float dt);

// Shutdown the ...
void GameStateThursdayShutdown();

void GameStateThursdayUnload();
//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

