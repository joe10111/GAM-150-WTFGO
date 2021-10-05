//------------------------------------------------------------------------------
// File Name:	Graphics.c
// Project:		What The Food is Going On!
// Author(s):	Joe Centeno
//
// All content © 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include <AEengine.h>
#include "Graphics.h"
#include "ParticleSystem.h"
#include "CuttingBoard.h"
#include <AEGraphics.h>
#include <AEEngine.h>

#define ZERO 0.0f
#define ONE 1.0f

#define MAP_ORGIN_X 250.0f

#define BOX_SIZE 80.0f
#define FOOD_SIZE 40.0f

#define FRIDGE_X -320.0f
#define PANTRY_X 820.0f

#define BOX_1_Y 100.0f
#define BOX_2_Y -50.0f
#define BOX_3_Y -200.0f

///////////////////////////////////////////////////////////////////////////////
/* Disc: A rendering system to draw sprites, map, ect                        */
///////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
AEGfxTexture* FoodPassSpriteSheet[7];

AEGfxTexture* Background;
AEGfxTexture* CuttingBoard;
AEGfxTexture* PrepTable;
AEGfxTexture* Fridge;
AEGfxTexture* Oven;
AEGfxTexture* OvenHeat;
AEGfxTexture* Pantry;
AEGfxTexture* Lettuce;
AEGfxTexture* Buns;
AEGfxTexture* Cheese;
AEGfxTexture* Onion;
AEGfxTexture* RawPatty;
AEGfxTexture* Tomato;
AEGfxTexture* UiBoard;
AEGfxTexture* UiTop;
AEGfxTexture* ReportCardBackground;
AEGfxTexture* ReportCard_Monday;
AEGfxTexture* ReportCard_Tuseday;
AEGfxTexture* ReportCard_Wensday;
AEGfxTexture* ReportCard_Thursday;
AEGfxTexture* ReportCard_Firday;
AEGfxTexture* ReportCard_Sunday;
AEGfxTexture* BlackSquare;

AEGfxTexture* RestrauntBackground;

AEGfxVertexList* pMesh;
//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static float screenshakeRemaining;
static bool screenshakeActive;

float currDuration;
float currIntensity;

float oldCamPosX;
float oldCamPosY;

static float currentAnimTime;
static float animSpeed;
static unsigned curFrame;
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Core Functions:
//------------------------------------------------------------------------------

void GraphicsLoad()
{
  //load in all textures
  
  // Luke Taranowski
  for (int i = 0; i < sizeof(FoodPassSpriteSheet) / sizeof(AEGfxTexture*); i++)
  {
    // Construct the correct filename
    char buffer[64];
    sprintf_s(buffer, sizeof(buffer), "./Assets/PlaceHolderSprites/FoodPass/FoodPass-%d.png", i);

    // Load in the correct image
    FoodPassSpriteSheet[i] = AEGfxTextureLoad(buffer);
    AE_ASSERT_MESG(FoodPassSpriteSheet[i], "ASSET LOAD FAILED FOODPASS");
  }


  animSpeed = 0.6f;
  currentAnimTime = animSpeed;
  curFrame = 0;
  //----------------

  BlackSquare = AEGfxTextureLoad("./Assets/BlackSquare.png");

  RestrauntBackground = AEGfxTextureLoad("./Assets/Restaurant.png");

  Background = AEGfxTextureLoad("./Assets/PlaceHolderSprites/Background1.png");
  AE_ASSERT_MESG(Background, "ASSET LOAD FAILED Background");

  CuttingBoard = AEGfxTextureLoad("./Assets/PlaceHolderSprites/CuttingBoard.png");
  AE_ASSERT_MESG(CuttingBoard, "ASSET LOAD FAILED CUTTING BOARD");

  PrepTable = AEGfxTextureLoad("./Assets/PlaceHolderSprites/CuttingBoard.png");
  AE_ASSERT_MESG(CuttingBoard, "ASSET LOAD FAILED CUTTING BOARD");

  Fridge = AEGfxTextureLoad("./Assets/PlaceHolderSprites/Fridge.png");
  AE_ASSERT_MESG(Fridge, "ASSET LOAD FAILED FRIDGE");

  Oven = AEGfxTextureLoad("./Assets/PlaceHolderSprites/Oven.png");
  AE_ASSERT_MESG(Oven, "ASSET LOAD FAILED OVEN");

  Pantry = AEGfxTextureLoad("./Assets/PlaceHolderSprites/Create.png");
  AE_ASSERT_MESG(Pantry, "ASSET LOAD FAILED PANTRY");

  Lettuce = AEGfxTextureLoad("./Assets/FoodItemsSprites/Lettuce.png");
  AE_ASSERT_MESG(Lettuce, "ASSET LOAD FAILED");

  Tomato = AEGfxTextureLoad("./Assets/FoodItemsSprites/Tomato.png");
  AE_ASSERT_MESG(Tomato, "ASSET LOAD FAILED");

  Onion = AEGfxTextureLoad("./Assets/FoodItemsSprites/Onion.png");
  AE_ASSERT_MESG(Onion, "ASSET LOAD FAILED");

  Cheese = AEGfxTextureLoad("./Assets/FoodItemsSprites/Cheese.png");
  AE_ASSERT_MESG(Cheese, "ASSET LOAD FAILED");

  Buns = AEGfxTextureLoad("./Assets/FoodItemsSprites/Buns.png");
  AE_ASSERT_MESG(Buns, "ASSET LOAD FAILED");

  RawPatty = AEGfxTextureLoad("./Assets/FoodItemsSprites/RawPatty.png");
  AE_ASSERT_MESG(RawPatty, "ASSET LOAD FAILED");

  UiBoard = AEGfxTextureLoad("./Assets/PlaceHolderSprites/Orders.png");
  AE_ASSERT_MESG(UiBoard, "ASSET LOAD FAILED");

  UiTop = AEGfxTextureLoad("./Assets/PlaceHolderSprites/Topside.png");
  AE_ASSERT_MESG(UiBoard, "ASSET LOAD FAILED");

  ReportCardBackground = AEGfxTextureLoad("./Assets/Report/WoodBackground.png");
  AE_ASSERT_MESG(ReportCardBackground, "ASSET LOAD FAILED");

  ReportCard_Monday = AEGfxTextureLoad("./Assets/Report/ReportMonday.png");
  AE_ASSERT_MESG(ReportCard_Monday, "ASSET LOAD FAILED");

  ReportCard_Tuseday = AEGfxTextureLoad("./Assets/Report/ReportTuesday.png");
  AE_ASSERT_MESG(ReportCard_Tuseday, "ASSET LOAD FAILED");

  ReportCard_Wensday = AEGfxTextureLoad("./Assets/Report/ReportWednesday.png");
  AE_ASSERT_MESG(ReportCard_Wensday, "ASSET LOAD FAILED");

  ReportCard_Thursday = AEGfxTextureLoad("./Assets/Report/ReportThursday.png");
  AE_ASSERT_MESG(ReportCard_Thursday, "ASSET LOAD FAILED");

  ReportCard_Firday = AEGfxTextureLoad("./Assets/Report/ReportFriday.png");
  AE_ASSERT_MESG(ReportCard_Firday, "ASSET LOAD FAILED");

  ReportCard_Sunday = AEGfxTextureLoad("./Assets/Report/ReportSunday.png");
  AE_ASSERT_MESG(ReportCard_Sunday, "ASSET LOAD FAILED");
}

// Initialize the Graphics
void GraphicsInit()
{
  GraphicsLoad();

  //Quad Mesh Code Start
  AEGfxMeshStart();

  AEGfxSetBlendColor(0, 0, 0, 1);

  AEGfxSetBlendMode(AE_GFX_BM_BLEND);

  AEGfxTriAdd( //First Triangle
    -0.5f, -0.5f, 0xFFFFFFFF, 0.0f, 1.0f,
    0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
    -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);

  AEGfxTriAdd( //Second Triangle
    0.5f, -0.5f, 0xFFFFFFFF, 1.0f, 1.0f,
    0.5f, 0.5f, 0xFFFFFFFF, 1.0f, 0.0f,
    -0.5f, 0.5f, 0xFFFFFFFF, 0.0f, 0.0f);
  //Quad Mesh Code End
  pMesh = AEGfxMeshEnd();

  screenshakeActive = false;
}

void GraphicsUnload()
{
  for (int i = 0; i < sizeof(FoodPassSpriteSheet) / sizeof(AEGfxTexture*); i++)
  {
    AEGfxTextureUnload(FoodPassSpriteSheet[i]);      //Unload Food Pass
  }
  
  AEGfxTextureUnload(Background);  //Unload Cutting Board
  AEGfxTextureUnload(CuttingBoard);  //Unload Cutting Board
  AEGfxTextureUnload(PrepTable);
  AEGfxTextureUnload(Fridge);        //Unload Fridge
  AEGfxTextureUnload(Oven);          //Unload Oven
  AEGfxTextureUnload(Pantry);        //Unload Pantry
  AEGfxTextureUnload(Buns);        //Unload Buns
  AEGfxTextureUnload(Tomato);        //Unload Tomato
  AEGfxTextureUnload(Onion);        //Unload Onion
  AEGfxTextureUnload(Cheese);        //Unload Cheese
  AEGfxTextureUnload(RawPatty);        //Unload RawPatty
  AEGfxTextureUnload(ReportCardBackground);      //Unload ReportCardBackground
  AEGfxTextureUnload(ReportCard_Monday);
  AEGfxTextureUnload(ReportCard_Tuseday);
  AEGfxTextureUnload(ReportCard_Wensday);
  AEGfxTextureUnload(ReportCard_Thursday);
  AEGfxTextureUnload(ReportCard_Firday);
}

void GraphicsUpdate(float dt)
{
  /* Going to use DT for physics helper function */
  UNREFERENCED_PARAMETER(dt);
}

// Shutdown the Graphics
void GraphicsShutdown()
{
  //Unload Textures
  GraphicsUnload();
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

//      Pointer to Texture for Sprite / Pos X    / Pos Y     / Transparency  / X & Y Size Of Image in Pixels  
void DrawSprite(AEGfxTexture* texture, float posX, float posY, float degree, float alpha, float xPixelSize, float yPixelSize)
{
  if (!texture)
    return;

  AEGfxSetRenderMode(AE_GFX_RM_TEXTURE);                  //Start Rendering

  AEGfxSetFullTransform(posX, posY, degree, xPixelSize, yPixelSize); //Set Transform
  AEGfxTextureSet(texture, 0, 0);                         //Set Texture
  AEGfxSetTransparency(alpha);                            //Set Alpha
  AEGfxSetBlendColor(0.0f, 0.0f, 0.0, 0.0f);              //Set Blend Colors

  AEGfxMeshDraw(pMesh, AE_GFX_MDM_TRIANGLES);             //Draw Mesh & Sprite

  AE_ASSERT_MESG(pMesh, "ERROR: CANT MAKE %s MESH!", pMesh);
}

static void AdvanceFrame()
{
  ++curFrame;
  currentAnimTime = animSpeed;

  // If we are going to overun the array
  if (curFrame == sizeof(FoodPassSpriteSheet) / sizeof(AEGfxTexture*))
  {
    curFrame = 0;
  }
}

void DrawMapSprite(float dt)
{
    
  DrawSprite(RestrauntBackground, -500.0f, 60, ZERO, ONE, (1080), (1920 * 0.5));
  DrawSprite(RestrauntBackground, -500.0f, -960 / 2.0f, ZERO, ONE, (1080), (1920 * 0.5));

  DrawSprite(RestrauntBackground, 500.0f, 60, ZERO, ONE, (1080), (1920 * 0.5));
  DrawSprite(RestrauntBackground, 500.0f, -960 / 2.0f, ZERO, ONE, (1080), (1920 * 0.5));

  DrawSprite(BlackSquare, 0, 0, ZERO, 0.5f, (1920), 1080);

  DrawSprite(Background, MAP_ORGIN_X, -60.0f, ZERO, ONE, 1331.0f, 832.0f);

  DrawSprite(UiBoard, -615.0f, 0.0f, ZERO, ONE, 400, 840);

  DrawSprite(UiTop, MAP_ORGIN_X, 430.0f, ZERO, ONE, 1024, 150);

  // Draw particles
  UNREFERENCED_PARAMETER(dt);

  // Luke Taranowski
  // Food pass conveyer belt animation
  if (currentAnimTime <= 0)
    AdvanceFrame();
  else
    currentAnimTime -= dt;

  DrawSprite(FoodPassSpriteSheet[curFrame], MAP_ORGIN_X, 250.0f, ZERO, ONE, 1200.0f, BOX_SIZE);

  DrawSprite(Fridge, FRIDGE_X, BOX_1_Y, ZERO, ONE, BOX_SIZE, BOX_SIZE);
  DrawSprite(Lettuce, FRIDGE_X, BOX_1_Y, ZERO, ONE, FOOD_SIZE, FOOD_SIZE); //Lettuce Sprite

  DrawSprite(Pantry, PANTRY_X, BOX_1_Y, ZERO, ONE, BOX_SIZE, BOX_SIZE);
  DrawSprite(Buns, PANTRY_X, BOX_1_Y, ZERO, ONE, FOOD_SIZE, FOOD_SIZE); //Buns Sprite

  DrawSprite(Fridge, FRIDGE_X, BOX_2_Y, ZERO, ONE, BOX_SIZE, BOX_SIZE);
  DrawSprite(Cheese, FRIDGE_X, BOX_2_Y, ZERO, ONE, FOOD_SIZE, FOOD_SIZE); //Cheese Sprite

  DrawSprite(Pantry, PANTRY_X, BOX_2_Y, ZERO, ONE, BOX_SIZE, BOX_SIZE);
  DrawSprite(Tomato, PANTRY_X, BOX_2_Y, ZERO, ONE, FOOD_SIZE, FOOD_SIZE); //Tomato Sprite

  DrawSprite(Fridge, FRIDGE_X, BOX_3_Y, ZERO, ONE, BOX_SIZE, BOX_SIZE);
  DrawSprite(RawPatty, FRIDGE_X, BOX_3_Y, ZERO, ONE, FOOD_SIZE, FOOD_SIZE); //Raw Patty Sprite

  DrawSprite(Pantry, PANTRY_X, BOX_3_Y, ZERO, ONE, BOX_SIZE, BOX_SIZE);
  DrawSprite(Onion, PANTRY_X, BOX_3_Y, ZERO, ONE, FOOD_SIZE, FOOD_SIZE);  //Onion Sprite
}

static float RandomFloat(float min, float max)
{
  float x = AERandFloat();
  float range = max - min;
  return (float)((range * x) + min);
}

void ScreenShakeCreate(float duration, float intensity)
{
  if (!screenshakeActive)
  {
    screenshakeRemaining = duration;
    currIntensity = intensity;
    screenshakeActive = true;

    AEGfxGetCamPosition(&oldCamPosX, &oldCamPosY);
  }
}

void ScreenShakeUpdate(float dt)
{
  if (screenshakeRemaining >= 0 && screenshakeActive)
  {
    f32 xPos;
    f32 yPos;
    AEGfxGetCamPosition(&xPos, &yPos);

    xPos += (RandomFloat(-1, 1) * currIntensity);
    yPos += (RandomFloat(-1, 1) * currIntensity);

    AEGfxSetCamPosition(xPos, yPos);

    screenshakeRemaining -= dt;
  }
  else
  {
    AEGfxSetCamPosition(oldCamPosX, oldCamPosY);
    screenshakeActive = false;
  }
}

void DrawReport(int day)
{
  DrawSprite(ReportCardBackground, 0.0f, 0.0f, 0.0f, 1, 1920, 1080);

  switch (day)
  {
  case 1: DrawSprite(ReportCard_Monday, 0.0f, 0.0f, 0.0f, 1, 1920, 1080);
    break;

  case 2: DrawSprite(ReportCard_Tuseday, 0.0f, 0.0f, 0.0f, 1, 1920, 1080);
    break;

  case 3: DrawSprite(ReportCard_Wensday, 0.0f, 0.0f, 0.0f, 1, 1920, 1080);
    break;

  case 4: DrawSprite(ReportCard_Thursday, 0.0f, 0.0f, 0.0f, 1, 1920, 1080);
    break;

  case 5: DrawSprite(ReportCard_Firday, 0.0f, 0.0f, 0.0f, 1, 1920, 1080);
    break;

  case 6: DrawSprite(ReportCard_Sunday, 0.0f, 0.0f, 0.0f, 1, 1920, 1080);
      break;
  }
}

bool ShouldMove()
{
  return (currentAnimTime <= 0);
}

void DrawStations(int day)
{
    if (day > 1)
    {
        DrawSprite(CuttingBoard, FRIDGE_X + 150, -350.0f, ZERO, ONE, BOX_SIZE + 20, BOX_SIZE + 20);
        drawKnifeAnimation();
    }
    
    if (day > 2)
    {
        DrawSprite(Oven, PANTRY_X - 150, -350.0f, ZERO, 1.0f, BOX_SIZE + 20, BOX_SIZE + 20);
    }
    if (day >= 4)
    {
      //  DrawSprite(PrepTable, 0, 0, ZERO, ONE, BOX_SIZE, BOX_SIZE);
        DrawSprite(PrepTable, 250, -350, ZERO, ONE, BOX_SIZE, BOX_SIZE);
       // DrawSprite(PrepTable, 500, 0, ZERO, ONE, BOX_SIZE, BOX_SIZE);
        DrawSprite(PrepTable, 100, -170, ZERO, ONE, BOX_SIZE, BOX_SIZE);
        DrawSprite(PrepTable, 400, -170, ZERO, ONE, BOX_SIZE, BOX_SIZE);
    }
}
//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------