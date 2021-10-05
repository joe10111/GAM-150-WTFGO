//------------------------------------------------------------------------------
// File Name:	GameStateTuesday.h
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

	void GameStateTusedayLoad();
// Initialize the ...
void GameStateTusedayInit();

// Update the ...
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateTusedayUpdate(float dt);

// Shutdown the ...
void GameStateTusedayShutdown();

void GameStateTusedayUnload();
//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif
