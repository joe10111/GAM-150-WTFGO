//------------------------------------------------------------------------------
// File Name:	LevelFunctions.c
// Project:		What The Food is Going On!
// Author(s): Joe Centeno
//
// All content © 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "LevelFunctions.h"
#include "AEEngine.h"    
#include "GameStateManager.h"
#include "GameStateKitchenSandbox.h"
#include "Trace.h"
#include "FoodItem.h"
#include "Plate.h"
#include "Order.h"
#include "MenuLogic.h"
#include "Graphics.h"
#include "TestFunctions.h"
#include "Player.h"
#include "AudioSystem.h" //Audio Header File
#include "Stations.h"
#include "Oven.h"
#include "Score.h"
#include "Inventory.h"
#include "ParticleSystem.h"
#include "Time.h"
#include "ProgressBar.h"
#include "LevelManager.h"
#include "Text.h"
#include "Stats.h"
#include "StickyNotes.h"
#include "Pause.h"

#define CBINITX -300
#define CBY 250
#define CBENDX 810.0F

#define CAL_X 375.0f
#define CAL_Y 430.0f

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
enum DayOfWeek
{
    Invalid = 0,
    Monday = 1,
    Tuseday,
    Wensday,
    Thursday,
    Firday,
    Endless,
};

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
int CurrDay = Invalid; // Current Day tells the level what day to start and end 
                       // Set this in Each Level Init 

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static PlayerPtr player; // Player Object 
static int i;            // Reusable loop counter

static AEGfxTexture * handTexture;
static AEGfxTexture* LevelSprite;

static float handCordX;
static float handCordY;
static float handSpeedX;
static float handSpeedY;

static float orderCooldown;
static float levelOrderCooldown;
static int orderCount;
static int maxOrderCount;

static float ReportTimer;

static bool pressed = false;
static bool pressed1 = false;
bool pauseb = false;
static int TotalOrdersDone;

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

static void MuteBotton();                                // Music Mute
static void NewRandFoodItem();                           // Make a New Random Food
static void ConveyerBeltUpdate();                        // Move Belt
static void PlateOrdersUpdate(float dt);                 // Orders Update
static void HandAnimation();                             // Hand Animation for Plate
static void KeyBinds();                                  // All Key Binds for Exiting and Restarting
static void CheckForLevelEnd(float dt);                  // Check If the Level is over
static void DrawLevelSprites(AEGfxTexture* LevelSprite); // Draw Level Based Sprites 
static void LevelReport(int day, float dt);
static void UpdateLevelScore(int day, float dt);



//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void LevelInit()
{
    // Add player to scene.
    player = CreatePlayer();

    // Hide the default cursor
    AEInputShowCursor(0);

    StatsInit();
    LevelManagerInit();
    InitProgressBars();
    GraphicsInit();
    MenuLogicInit();
    TestFunctionsInit();
    LoadScore();
    InitScore();
    StationsInit();
    TextInit();
    LoadSoundSystem();
    PauseInit();
    pauseb = false;
    handTexture = AEGfxTextureLoad("Assets/PlaceHolderSprites/hand.png");
    handCordX = -300.0f;
    handCordY = 700.0f;
    handSpeedX = 0.0f;
    handSpeedY = 0.0f;
    
    orderCount = 0;
   ReportTimer = 10;

    TimeInit();
    StartDay(CurrDay);
}

// Call Day of the Week Init Functions First 
// Before Level Init Or else Each Level will 
// have Invalid Start and End
void MondayInit()
{
    CurrDay = Monday;

    orderCooldown = 5.0f;      // Initial Order Cooldown
    levelOrderCooldown = 15.0f; // Order Cooldown in Level
    maxOrderCount = 3;          // Max Order Count in Level

    LevelSprite = AEGfxTextureLoad("./Assets/Monday.png");
}

void TusedayInit()
{
    CurrDay = Tuseday;

    orderCooldown = 5.0f;       // Initial Order Cooldown
    levelOrderCooldown = 30.0f; // Order Cooldown in Level
    maxOrderCount = 6;          // Max Order Count in Level

    LevelSprite = AEGfxTextureLoad("./Assets/Tuseday.png");
}

void WensdayInit()
{
    CurrDay = Wensday;

    orderCooldown = 3.0f;       // Initial Order Cooldown
    levelOrderCooldown = 25.0f; // Order Cooldown in Level
    maxOrderCount = 9;          // Max Order Count in Level

    LevelSprite = AEGfxTextureLoad("./Assets/Wensday.png");
}

void ThursdayInit()
{
    CurrDay = Thursday;

    orderCooldown = 2.0f;       // Initial Order Cooldown
    levelOrderCooldown = 20.0f; // Order Cooldown in Level
    maxOrderCount = 12;          // Max Order Count in Level

    LevelSprite = AEGfxTextureLoad("./Assets/Thursday.png");
}

void FirdayInit()
{
    CurrDay = Firday;

    orderCooldown = 0.0f;        // Initial Order Cooldown
    levelOrderCooldown = 15.0f;  // Order Cooldown in Level
    maxOrderCount = 20;          // Max Order Count in Level

    LevelSprite = AEGfxTextureLoad("./Assets/Friday.png");
}

void EndlessInit()
{
    CurrDay = Endless;

    orderCooldown = 0.0f;        // Initial Order Cooldown
    levelOrderCooldown = 15.0f;  // Order Cooldown in Level
    maxOrderCount = 2000;          // Max Order Count in Level

    LevelSprite = AEGfxTextureLoad("./Assets/Endless.png");
}

void LevelUpdate(float dt)
{
    StatsUpdate(dt);
    // Update the Level Mangment Data
    LevelManagerUpdate(dt);

    // Mute Music With 'M'
    MuteBotton();

    // Make a new Random food with 'N'
    NewRandFoodItem();

    // Update Converyer Belt Movement 
    ConveyerBeltUpdate();

    //Update Orders and Plates
    PlateOrdersUpdate(dt);

    // Test Functions
    TestFunctionsUpdate(dt);

    StationsUpdate(dt, CurrDay);
  
    // Key Binds for Exit and Restart
    KeyBinds();

    // Hand Animation for Plates
    HandAnimation();

    if(pauseb == false){
        UpdatePlayer(player, dt);
    }

    //Draw Map Sprite
    DrawMapSprite(dt);

    DrawStations(CurrDay);

    //Draw everything else :)
    OvenDrawOverlay();

    DrawPlayerFeet(player);

    DrawPlayerBody(player);

    DrawPlayerHands(player);

    GraphicsUpdate(dt);
    
    PlateUpdate(dt);

    FoodItemUpdate(dt);

    OrderUpdate(dt);

    updatePlateCheckmarks();

    ParticleSystemUpdate(dt);

    ScreenShakeUpdate(dt);

    TimeUpdate(dt);

    UpdateProgressBars(player);

    UpdateScore();

    DrawLevelSprites(LevelSprite);

    // Update the player
    if (pauseb == true) {
        PauseUpdate(dt);
    }

    UpdateLevelScore(CurrDay, dt);
    CheckForLevelEnd(dt);
    LevelFadeIn(dt);
}

void LevelShutdown(void)
{
    //reset the stickynotes
    ClearStickyNotes();
    //reset the food items, Orders and plates arrays.
    ClearOrders();
    ClearPlates();
    ClearFoodItems();
    PauseShutdown();

    // Free all objects.
    GraphicsShutdown();
    //UnloadSounds();

    // Free the memory allocated to player.
    //DeleteInventory(&player->inventory);
    DeletePlayer(&player);

    TimeShutdown();
}

int GetCurrDay()
{
    return CurrDay;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

static void MuteBotton()
{
    if (AEInputCheckTriggered('M')) //Mute Button  
    {
        if (AEInputCheckTriggered('M') && pressed == true)
        {
            FMOD_SoundGroup_SetVolume(Music, 0.20f);
            pressed = false;
        }
        else if (AEInputCheckTriggered('M') && pressed == false)
        {
            FMOD_SoundGroup_SetVolume(Music, 0.0f);
            pressed = true;
        }
    }
}

static void NewRandFoodItem()
{
    //New rand food item
    if (AEInputCheckTriggered('N'))
    {
        FoodItemInit(RandomFoodID(12));
        TraceMessage("Random FoodItem Created");
    }
}

static void ConveyerBeltUpdate()
{
    //Rewind conveyer belt
    if (AEInputCheckCurr(VK_LEFT))
    {
        for (i = 0; i < SIZEOFORDERSARRAY; i++)
        {
            if (Plates[i].isActive)
            {
                Plates[i].transform.translation.x -= 6.0f;
            }
        }
    }

    //fast-forward conveyer belt
    if (AEInputCheckCurr(VK_RIGHT))
    {

        for (i = 0; i < SIZEOFORDERSARRAY; i++)
        {
            if (Plates[i].isActive)
            {
                Plates[i].transform.translation.x += 5.0f;
            }
        }
    }
}

static void PlateOrdersUpdate(float dt)
{
    if (orderCount < maxOrderCount)
    {
        orderCooldown -= dt; // If Max Orders have not been reached 
    }
    
    if (AEInputCheckTriggered('O'))
    {
        orderCooldown = 0.0f;
        orderCount++;
    }

    //Create Order and moving plate
    if (orderCooldown <= 0.0)
    {
        if (CurrDay == Monday)
        {
            OrderInitMonday();
        }
        else if (CurrDay == Tuseday)
        {
            OrderInitTuesday();
        }
        else
        {
            OrderInit();
        }
        //Creat Order Test
        
        orderCooldown = levelOrderCooldown;
        orderCount++;
    }
}

static void HandAnimation()
{
    //Plate reaches end, animations for the Hand at the end.
    for (i = 0; i < SIZEOFORDERSARRAY; i++)
    {
        if (Plates[i].isActive)
        {
            //sends hand down with plate init
            if (Plates[i].transform.translation.y > CBY)
            {
                handSpeedY = -5.0f;
                handSpeedX = 0.2f;
            }

            //if plate is at the end of belt
            if (Plates[i].transform.translation.x > CBENDX)
            {
                CheckPlateOrders(i);
            }

            //when plate init lands on conveyer belt
            if (Plates[i].transform.translation.y < CBY)
            {
                Plates[i].transform.translation.y = CBY;
                Plates[i].rigidbody.velocity.y = 0.0f;
                handSpeedY = 5.0f;
            }

            //spawns hand down when plate is about to reach the end
            if (Plates[i].transform.translation.x > (CBENDX - 20.0f) && Plates[i].transform.translation.x < (CBENDX - 19.0f))
            {
                handCordX = CBENDX + 5;
                handCordY = CBY + 325.0f;
                handSpeedY = -5.0f;
                handSpeedX = 0.2f;
            }

            //sends hand back up
            if (Plates[i].transform.translation.x > (CBENDX - 10.0f))
            {
                handSpeedY = 5.0f;
                Plates[i].rigidbody.velocity.y = 5.0f;
            }
        }
    }

    handCordX += handSpeedX;
    handCordY += handSpeedY;
}

static void KeyBinds()
{   //--------------------------------------------
    //-Check if Forcing the Application to Quit---
    //--------------------------------------------
    //if (AEInputCheckTriggered(VK_ESCAPE) 
    //     || 0 == AESysDoesWindowExist())
    //{
    //  GameStateManagerSetNextState(GsQuit);
    //}
    if (AEInputCheckTriggered(VK_ESCAPE))
    {
        if (pauseb == true) {
            pauseb = false;
        }
        else {
            pauseb = true;
        }
    }
    //-----------------------------------------------
    //-CHECK FOR LEVEL RESTART ('0' KEY TRIGGERED)---
    //-----------------------------------------------
    if (AEInputCheckCurr('C') == FALSE) 
    {
        if (AEInputCheckTriggered('0')) 
        {
            GameStateManagerSetNextState(GsRestart);
        }
    }
    
}

static void CheckForLevelEnd(float dt)
{
    float time = GetTimePassed();
    int ordersDone = GetOrdersDone() + GetOrdersMissed();

    if (time < 0.0f && CurrDay != 7)
    {
        if (LevelFadeOut(dt) == false)
        {
            LevelReport(CurrDay, dt);
        }
    }
    else if (ordersDone >= maxOrderCount && CurrDay != 7)
    {
        if (LevelFadeOut(dt) == false)
        {
            LevelReport(CurrDay, dt);
        }
        else
        {
            DrawGameText("Shift Completed!", -300.0f, 50.0f, 60);
        }
    }
    else if (time < 0.0f && CurrDay == 7)
    {
        time = 360;
    }
}

static void DrawLevelSprites(AEGfxTexture* LevelSpriteToDraw)
{
    DrawSprite(LevelSpriteToDraw, CAL_X * 2.3f, CAL_Y, 0, 1, 120.0f, 120.0f);
    DrawSprite(handTexture, handCordX, handCordY, 0, 1, 100, 200);
}

static void LevelReport(int day, float dt)
{
    StopTime();      // Stop Level Time 

    DrawReport(day);  

   char buffer[100];

    float time = GetTimeNormlized();
    sprintf_s(buffer, 100, "%f", time);
    DrawGameNumberBlack(buffer, 30.0f, 50.0f, 40);

    int ordersDone = GetOrdersDone();
    sprintf_s(buffer, 100, "%d", ordersDone);
    DrawGameNumberBlack(buffer, 200.0f, -20.0f, 40);

    int ordersMissed = GetOrdersMissed();
    sprintf_s(buffer, 100, "%d", ordersMissed);
    DrawGameNumberBlack(buffer, 200.0f, -110.0f, 40);

    int itemsThrown = GetFoodThrows();
    sprintf_s(buffer, 100, "%d", itemsThrown);
    DrawGameNumberBlack(buffer, 30.0f, -300.0f, 60);
    
    ReportTimer -= dt;

    if (ReportTimer <= 0.0f && CurrDay != 6)
    {
        ReportTimer = 0.0f;
        EndDay(day);
    }
    else if (ReportTimer <= 0.0f && CurrDay == 6)
    {
        GameStateManagerSetNextState(GsGameOver);
    }

    // Time Left Untill Level Switch
    sprintf_s(buffer, 100, "%f", ReportTimer);
    DrawGameNumberBlack(buffer, 30.0f, -400.0f, 50);
}

static void UpdateLevelScore(int day, float dt)
{
    int score = GetScore();


    if (day == 6 && score <= 0)
    {
        LevelReport(day, dt);
    }
}