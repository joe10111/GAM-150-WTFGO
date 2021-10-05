//------------------------------------------------------------------------------
// File Name:	AudioSystem.c
// Project:		What The Food is Going On!
// Author(s):	Joe Centeno
//
// All content © 2021 DigiPen(USA) Corporation, all rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "AudioSystem.h" //Audio Header File
#include <AEEngine.h>
#include <stdio.h>		 // printf()
#include <stdbool.h>	 // FALSE

#define MAX_SOUND_LENGTH 1000.0f
#define ZERO 0.0f

///NOTE
// If you are going to add a new sound pleae increase the define of Number of Sounds by one
// Then Add  a new case in the switch to init the sounds properties

//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

FMOD_SYSTEM* SoundSystem;

//FMOD_CHANNEL* Channel_1;
//FMOD_CHANNEL* Channel_2;
//FMOD_CHANNEL* Channel_3;
//FMOD_CHANNEL* Channel_4;

FMOD_RESULT Result;

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

void ERRCHECK(FMOD_RESULT InputResult)
{
	//Professor Code Intergrated into our Sound System
	if (InputResult != FMOD_OK)
	{
		printf("ERROR: AUDIO SYSTEM -> (%d) %s\n", InputResult, FMOD_ErrorString(Result));
	}
}

void LoadSounds() 
{	
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/sample_beep.wav" , FMOD_DEFAULT | FMOD_2D, 0, &Sound1);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/Pickup.wav", FMOD_DEFAULT | FMOD_2D, 0, &PickUp);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/Throw.wav", FMOD_DEFAULT | FMOD_2D, 0, &Throw);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/Walking.wav", FMOD_DEFAULT | FMOD_2D, 0, &Walking);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/OvenBeep.wav", FMOD_DEFAULT | FMOD_2D, 0, &OvenBeep);
	FMOD_System_CreateSound(SoundSystem, "Assets/Music/Track1.mp3", FMOD_DEFAULT | FMOD_2D, 0, &Track1);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/Crowd.wav", FMOD_DEFAULT | FMOD_2D, 0, &Crowd);

	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/Bell.wav", FMOD_DEFAULT | FMOD_2D, 0, &Bell);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/Beep.wav", FMOD_DEFAULT | FMOD_2D, 0, &BeepFood);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/Cutting.wav", FMOD_DEFAULT | FMOD_2D, 0, &Cutting);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/Whistle.wav", FMOD_DEFAULT | FMOD_2D, 0, &Whistle);

	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/joe_centeno_complaint.wav", FMOD_DEFAULT | FMOD_2D, 0, &AngryJoe);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/joe_centeno_happy.wav", FMOD_DEFAULT | FMOD_2D, 0, &HappyJoe);

	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/luke_taranowski_complaint.wav", FMOD_DEFAULT | FMOD_2D, 0, &AngryLuke);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/luke_taranowski_happy.wav", FMOD_DEFAULT | FMOD_2D, 0, &HappyLuke);

	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/AngryJustin1.wav", FMOD_DEFAULT | FMOD_2D, 0, &AngryJustin1);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/AngryJustin2.wav", FMOD_DEFAULT | FMOD_2D, 0, &AngryJustin2);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/AngryJustin3.wav", FMOD_DEFAULT | FMOD_2D, 0, &AngryJustin3);

	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/HappyJustin1.wav", FMOD_DEFAULT | FMOD_2D, 0, &HappyJustin1);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/HappyJustin2.wav", FMOD_DEFAULT | FMOD_2D, 0, &HappyJustin2);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/HappyJustin3.wav", FMOD_DEFAULT | FMOD_2D, 0, &HappyJustin3);

	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/SakethHappy.wav", FMOD_DEFAULT | FMOD_2D, 0, &HappySaketh);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/SakethAngry.wav", FMOD_DEFAULT | FMOD_2D, 0, &AngrySaketh);

	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/AngryCarlos.wav", FMOD_DEFAULT | FMOD_2D, 0, &AngryCarlos);
	FMOD_System_CreateSound(SoundSystem, "Assets/Sounds/HappyCarlos.wav", FMOD_DEFAULT | FMOD_2D, 0, &HappyCarlos);

}

// Initialize the Audio
void AudioSystemInit()
{
	Channel_1 = 0; //Ui and Misc
	Channel_2 = 0; //Player and Food Items
	Channel_3 = 0; //Music
	Channel_4 = 0; //Justin's multiple personalities :)
	
	//Professor Code Intergrated into our Sound System
	FMOD_System_Create(&SoundSystem);
	//ERRCHECK(Result);

	FMOD_System_Init(SoundSystem, 32, FMOD_INIT_NORMAL, 0);
	//ERRCHECK(Result);
}

void LoadSoundSystem()
{
	LoadSounds();

	MakeAllSoundGroups();

	InitSoundIDs();
}

void InitSoundIDs()
{
	for (int i = 1; i < NUMOFSOUNDS; i++)
	{
		sounds[i].ID = i;
		sounds[i].active = false;
		sounds[i].looping = false;
		
		switch (sounds[i].ID)
		{
		case 1:
			sounds[1].soundPath = "Assets/Sounds/sample_beep.wav";
			sounds[1].name = "Test";
			sounds[1].channel = Channel_1;
			sounds[1].fmodSound = Sound1;
			sounds[1].SoundAdress = &Sound1;
			sounds[1].soundGroup = UiSounds;
			break;

		case 2 : 
			sounds[2].soundPath = "Assets/Sounds/Pickup.wav";
			sounds[2].name = "PickUp";
			sounds[2].channel = Channel_2;
			sounds[2].fmodSound = PickUp;
			sounds[2].SoundAdress = &PickUp;
			sounds[3].soundGroup = PlayerSoundEffects;
			break;

		case 3:
			sounds[3].soundPath = "Assets/Sounds/Throw.wav";
			sounds[3].name = "Throw";
			sounds[3].channel = Channel_2;
			sounds[3].fmodSound = Throw;
			sounds[3].SoundAdress = &Throw;
			sounds[3].soundGroup = PlayerSoundEffects;
			break;
		    
		case 4:
			sounds[4].soundPath = "Assets/Sounds/Walking.wav";
			sounds[4].name = "Walking";
			sounds[4].channel = Channel_2;
			sounds[4].fmodSound = Walking;
			sounds[4].SoundAdress = &Walking;
			sounds[4].soundGroup = BackgroundSounds;
			break;

		case 5:
			sounds[5].soundPath = "Assets/Sounds/OvenBeep.wav";
			sounds[5].name = "OvenBeep";
			sounds[5].channel = Channel_1;
			sounds[5].fmodSound = OvenBeep;
			sounds[5].SoundAdress = &OvenBeep;
			sounds[5].soundGroup = BackgroundSounds;
			break;

		case 6:
			sounds[6].soundPath = "Assets/Music/Track1.mp3";
			sounds[6].name = "SoundTrack";
			sounds[6].channel = Channel_1; 
			sounds[6].fmodSound = Track1;
			sounds[6].SoundAdress = &Track1;
			sounds[6].soundGroup = Music;
			break;

		case 7:
			sounds[7].soundPath = "Assets/Sounds/Bell.wav";
			sounds[7].name = "Bell";
			sounds[7].channel = Channel_1;
			sounds[7].fmodSound = Bell;
			sounds[7].SoundAdress = &Bell;
			sounds[7].soundGroup = Details;
			break;

		case 8:
			sounds[8].soundPath = "Assets/Sounds/Beep.wav";
			sounds[8].name = "Beep";
			sounds[8].channel = Channel_1;
			sounds[8].fmodSound = BeepFood;
			sounds[8].SoundAdress = &BeepFood;
			sounds[8].soundGroup = Details;
			break;

		case 9:
			sounds[9].soundPath = "Assets/Sounds/Cutting.wav";
			sounds[9].name = "Cutting";
			sounds[9].channel = Channel_1;
			sounds[9].fmodSound = Cutting;
			sounds[9].SoundAdress = &Cutting;
			sounds[9].soundGroup = Details;
			break;

		case 10:
			sounds[10].soundPath = "Assets/Sounds/Whistle.wav";
			sounds[10].name = "Whistle";
			sounds[10].channel = Channel_1;
			sounds[10].fmodSound = Whistle;
			sounds[10].SoundAdress = &Whistle;
			sounds[10].soundGroup = Details;
			break;
		case 11:
			sounds[11].soundPath = "Assets/Sounds/Crowd.wav";
			sounds[11].name = "Crowd";
			sounds[11].channel = Channel_1;
			sounds[11].fmodSound = Crowd;
			sounds[11].SoundAdress = &Crowd;
			sounds[11].soundGroup = Details;
			break;
		case 12:
			sounds[12].soundPath = "Assets/Sounds/joe_centeno_complaint.wav";
			sounds[12].name = "AngryJoe";
			sounds[12].channel = Channel_3;
			sounds[12].fmodSound = AngryJoe;
			sounds[12].SoundAdress = &AngryJoe;
			sounds[12].soundGroup = Customers;
			break;
		case 13:
			sounds[13].soundPath = "Assets/Sounds/joe_centeno_happy.wav";
			sounds[13].name = "HappyJoe";
			sounds[13].channel = Channel_3;
			sounds[13].fmodSound = HappyJoe;
			sounds[13].SoundAdress = &HappyJoe;
			sounds[13].soundGroup = Customers;
			break;
		case 14:
			sounds[14].soundPath = "Assets/Sounds/luke_taranowski_complaint.wav";
			sounds[14].name = "AngryLuke";
			sounds[14].channel = Channel_3;
			sounds[14].fmodSound = AngryLuke;
			sounds[14].SoundAdress = &AngryLuke;
			sounds[14].soundGroup = Customers;
			break;
		case 15:
			sounds[15].soundPath = "Assets/Sounds/luke_taranowski_happy.wav";
			sounds[15].name = "HappyLuke";
			sounds[15].channel = Channel_3;
			sounds[15].fmodSound = HappyLuke;
			sounds[15].SoundAdress = &HappyLuke;
			sounds[15].soundGroup = Customers;
			break;
		case 16:
			sounds[16].soundPath = "Assets/Sounds/HappyJustin1.wav";
			sounds[16].name = "HappyJustin1";
			sounds[16].channel = Channel_4;
			sounds[16].fmodSound = HappyJustin1;
			sounds[16].SoundAdress = &HappyJustin1;
			sounds[16].soundGroup = Justin;
			break;
		case 17:
			sounds[17].soundPath = "Assets/Sounds/HappyJustin2.wav";
			sounds[17].name = "HappyJustin2";
			sounds[17].channel = Channel_4;
			sounds[17].fmodSound = HappyJustin2;
			sounds[17].SoundAdress = &HappyJustin2;
			sounds[17].soundGroup = Justin;
			break;
		case 18:
			sounds[18].soundPath = "Assets/Sounds/HappyJustin3.wav";
			sounds[18].name = "HappyJustin3";
			sounds[18].channel = Channel_4;
			sounds[18].fmodSound = HappyJustin3;
			sounds[18].SoundAdress = &HappyJustin3;
			sounds[18].soundGroup = Justin;
			break;
		case 19:
			sounds[19].soundPath = "Assets/Sounds/AngryJustin1.wav";
			sounds[19].name = "AngryJustin1";
			sounds[19].channel = Channel_4;
			sounds[19].fmodSound = AngryJustin1;
			sounds[19].SoundAdress = &AngryJustin1;
			sounds[19].soundGroup = Justin;
			break;
		case 20:
			sounds[20].soundPath = "Assets/Sounds/AngryJustin2.wav";
			sounds[20].name = "AngryJustin2";
			sounds[20].channel = Channel_4;
			sounds[20].fmodSound = AngryJustin2;
			sounds[20].SoundAdress = &AngryJustin2;
			sounds[20].soundGroup = Justin;
			break;
		case 21:
			sounds[21].soundPath = "Assets/Sounds/AngryJustin3.wav";
			sounds[21].name = "AngryJustin3";
			sounds[21].channel = Channel_4;
			sounds[21].fmodSound = AngryJustin3;
			sounds[21].SoundAdress = &AngryJustin3;
			sounds[21].soundGroup = Justin;
			break;
		case 22:
			sounds[22].soundPath = "Assets/Sounds/SakethAngry.wav";
			sounds[22].name = "AngrySaketh";
			sounds[22].channel = Channel_3;
			sounds[22].fmodSound = AngrySaketh;
			sounds[22].SoundAdress = &AngrySaketh;
			sounds[22].soundGroup = Customers;
			break;
		case 23:
			sounds[23].soundPath = "Assets/Sounds/SakethHappy.wav";
			sounds[23].name = "HappySaketh";
			sounds[23].channel = Channel_3;
			sounds[23].fmodSound = HappySaketh;
			sounds[23].SoundAdress = &HappySaketh;
			sounds[23].soundGroup = Customers;
			break;
		case 24:
			sounds[24].soundPath = "Assets/Sounds/AngryCarlos.wav";
			sounds[24].name = "AngryCarlos";
			sounds[24].channel = Channel_3;
			sounds[24].fmodSound = AngryCarlos;
			sounds[24].SoundAdress = &AngryCarlos;
			sounds[24].soundGroup = Customers;
			break;
		case 25:
			sounds[25].soundPath = "Assets/Sounds/HappyCarlos.wav";
			sounds[25].name = "HappyCarlos";
			sounds[25].channel = Channel_3;
			sounds[25].fmodSound = HappyCarlos;
			sounds[25].SoundAdress = &HappyCarlos;
			sounds[25].soundGroup = Customers;
			break;
		}
	}
}

void AudioSystemUpdate()
{
	FMOD_System_Update(SoundSystem);
	//ERRCHECK(Result);

	for (int i = 1; i < NUMOFSOUNDS; i++)
	{
		if (sounds[i].looping == false)
		{
			FMOD_Sound_SetMode(sounds[i].fmodSound, FMOD_DEFAULT);
		}
	}
}

// Shutdown the Audio
void AudioSystemShutdown()
{
	Channel_1 = NULL; //Ui and Misc
	Channel_2 = NULL; //Player and Food Items
	Channel_3 = NULL; //Music

	// Close the FMOD System
	FMOD_System_Close(SoundSystem);
	ERRCHECK(Result);

	//Release the FMOD System 
	FMOD_System_Release(SoundSystem);
	ERRCHECK(Result);
}

void UnloadSounds()
{
	FMOD_Sound_Release(Track1);
}

void PlaySoundFile(FMOD_SOUND* sound, float Volume, bool Loop)
{
	int soundID = GetSoundID(sound);

	sounds[soundID].active = true;

	bool SoundActive = sounds[soundID].active;

	FMOD_SOUNDGROUP* SoundGroup = sounds[soundID].soundGroup;

	FMOD_SoundGroup_SetVolume(SoundGroup, Volume);

	switch (SoundActive) //Check if sound is active
	{
	  case true : //If Sound Active is true
		//Loop Sound
		if (Loop) //Check if we need to loop sound
	    {
			FMOD_Sound_SetMode(sound, FMOD_LOOP_NORMAL);
			sounds[soundID].looping = true;
	    }
		else
		{
			FMOD_Sound_SetMode(sound, FMOD_DEFAULT);
		}

		FMOD_System_PlaySound(SoundSystem, sound, 0, false, &sounds[soundID].channel); //Play Sound

		break; //Break out of LoopSound Switch
	
	  case false: //Sound Active false
		printf("Sound Not active");
		break;
	}
	
	sounds[soundID].active = false;
	return; //return from the function
}

void MakeAllSoundGroups()
{
	FMOD_System_CreateSoundGroup(SoundSystem, "PlayerSoundEffects", &PlayerSoundEffects);
	FMOD_System_CreateSoundGroup(SoundSystem, "Music", &Music);
	FMOD_System_CreateSoundGroup(SoundSystem, "BackgroundSounds", &BackgroundSounds);
	FMOD_System_CreateSoundGroup(SoundSystem, "UiSounds", &UiSounds);
	FMOD_System_CreateSoundGroup(SoundSystem, "Details", &Details);
	FMOD_System_CreateSoundGroup(SoundSystem, "Customers", &Customers);
	FMOD_System_CreateSoundGroup(SoundSystem, "Jusin", &Justin);

	FMOD_Sound_SetSoundGroup(Track1, Music);
	FMOD_Sound_SetSoundGroup(Throw, PlayerSoundEffects);
	FMOD_Sound_SetSoundGroup(PickUp, PlayerSoundEffects);
	FMOD_Sound_SetSoundGroup(OvenBeep, BackgroundSounds);

	FMOD_Sound_SetSoundGroup(Crowd, Details);
	FMOD_Sound_SetSoundGroup(BeepFood, Details);
	FMOD_Sound_SetSoundGroup(Bell, Details);
	FMOD_Sound_SetSoundGroup(Cutting, Details);
	FMOD_Sound_SetSoundGroup(Whistle, Details);

	FMOD_Sound_SetSoundGroup(HappyJoe, Customers);
	FMOD_Sound_SetSoundGroup(AngryJoe, Customers);

	FMOD_Sound_SetSoundGroup(HappyLuke, Customers);
	FMOD_Sound_SetSoundGroup(AngryLuke, Customers);

	FMOD_Sound_SetSoundGroup(HappySaketh, Customers);
	FMOD_Sound_SetSoundGroup(AngrySaketh, Customers);

	FMOD_Sound_SetSoundGroup(HappyCarlos, Customers);
	FMOD_Sound_SetSoundGroup(AngryCarlos, Customers);

	FMOD_Sound_SetSoundGroup(HappyJustin1, Justin);
	FMOD_Sound_SetSoundGroup(HappyJustin2, Justin);
	FMOD_Sound_SetSoundGroup(HappyJustin3, Justin);
	FMOD_Sound_SetSoundGroup(AngryJustin1, Justin);
	FMOD_Sound_SetSoundGroup(AngryJustin2, Justin);
	FMOD_Sound_SetSoundGroup(AngryJustin3, Justin);
}

int GetSoundID(FMOD_SOUND* sound)
{
	int soundID;
	if (sound)
	{
		for (int i = 1; i < MAX_SOUND_LENGTH; i++)
		{
			if (sound == (sounds[i].fmodSound))
			{
				soundID = sounds[i].ID;
		
				return soundID;
			}
		}

		AESysPrintf("Cant find Match");
		return 0;
	}

	AESysPrintf("Not Valid Sound");	
	return 0;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------