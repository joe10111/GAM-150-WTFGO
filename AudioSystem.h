//------------------------------------------------------------------------------
// File Name:	AudioSystem.h
// Project:		What The Food is Going On!
// Author(s):	Joe Centeno
//
// All content © 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#pragma warning(disable: 4505)

#include "fmod.h"        //Fmod 
#include "fmod_errors.h" //Audio Error Handler

#define NUMOFSOUNDS 29

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

typedef struct SoundObj
{
	bool active;
	bool looping;
	int ID;
	const char* soundPath;     // file path
	const char* name;          // sound name to be used a future reference
	FMOD_SOUND* fmodSound;     // fmod struct managing fmod stuff
	FMOD_SOUND** SoundAdress;
	FMOD_CHANNEL* channel;       // another fmod struct managing fmod stuff
	FMOD_SOUNDGROUP* soundGroup;      // whether a song is effect or a background sound
}SoundObj;

SoundObj sounds[NUMOFSOUNDS];

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------
FMOD_SYSTEM* SoundSystem;

FMOD_CHANNEL* Channel_1;
FMOD_CHANNEL* Channel_2;
FMOD_CHANNEL* Channel_3;
FMOD_CHANNEL* Channel_4;


FMOD_RESULT Result;

FMOD_SOUND* Sound1;
FMOD_SOUND* PickUp;
FMOD_SOUND* Throw;
FMOD_SOUND* Walking;
FMOD_SOUND* Track1;
FMOD_SOUND* OvenBeep;
FMOD_SOUND* Bell;
FMOD_SOUND* BeepFood;
FMOD_SOUND* Cutting;
FMOD_SOUND* Whistle;
FMOD_SOUND* Crowd;

FMOD_SOUND* HappyJoe;
FMOD_SOUND* AngryJoe;

FMOD_SOUND* HappyLuke;
FMOD_SOUND* AngryLuke;

FMOD_SOUND* HappySaketh;
FMOD_SOUND* AngrySaketh;

FMOD_SOUND* HappyCarlos;
FMOD_SOUND* AngryCarlos;

FMOD_SOUND* HappyJustin1;
FMOD_SOUND* HappyJustin3;
FMOD_SOUND* HappyJustin2;

FMOD_SOUND* AngryJustin1;
FMOD_SOUND* AngryJustin3;
FMOD_SOUND* AngryJustin2;


FMOD_SOUNDGROUP* PlayerSoundEffects;
FMOD_SOUNDGROUP* BackgroundSounds;
FMOD_SOUNDGROUP* UiSounds;
FMOD_SOUNDGROUP* Music;
FMOD_SOUNDGROUP* Details;
FMOD_SOUNDGROUP* Customers;
FMOD_SOUNDGROUP* Justin;


//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void ERRCHECK(FMOD_RESULT InputResult);

void LoadSounds();

void LoadSoundSystem();

void UnloadSounds();

// Initialize the Audio
void AudioSystemInit();

void InitSoundIDs();

int GetSoundID(FMOD_SOUND* sound);

// Update the Audio
void AudioSystemUpdate();

// Shutdown the Audio
void AudioSystemShutdown();

void MakeAllSoundGroups();

void PlaySoundFile(FMOD_SOUND* sound, float Volume, bool Loop);


//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

