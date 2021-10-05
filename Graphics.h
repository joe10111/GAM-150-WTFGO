//------------------------------------------------------------------------------
// File Name:	Graphics.h
// Project:		What The Food is Going On!
// Author(s):	Joe Centeno
//
// All content © 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#pragma once
#include <AEEngine.h>

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

void GraphicsLoad();

// Initialize the ...
void GraphicsInit();

void GraphicsUnload();

void GraphicsUpdate(float dt);

// Shutdown the Graphics
void GraphicsShutdown();

               //
void DrawSprite(AEGfxTexture* texture, float posX, float posY, float degree, float alpha, float xPixelSize, float yPixelSize);

void DrawMapSprite(float dt);

void ScreenShakeCreate(float duration, float intensity);
void ScreenShakeUpdate(float dt);

void DrawReport(int day);

void DrawStations(int day);

bool ShouldMove();

//------------------------------------------------------------------------------

#ifdef __cplusplus
}                       /* End of extern "C" { */
#endif

