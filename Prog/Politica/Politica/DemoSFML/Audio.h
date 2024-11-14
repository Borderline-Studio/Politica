#ifndef  AUDIO_H

#define AUDIO_H

#include"Common.h"

struct Sound
{
	sf::Sound sound;
	sf::SoundBuffer* buffer;
	float volume;
};

struct Music
{
	sf::Music music;
	Fade fade;
	float volume;
};

unsigned char AddSound(std::string _name);
unsigned char AddMusic(std::string _name);

void PlaySoundFromList(unsigned char _i, float _volume = 100.f * GetSoundMultiplier());

void PlaySoundRepeated(unsigned char _i, float _volume = 100.f * GetSoundMultiplier());

void StopSound(unsigned char _i);

void StopAllSounds(void);

void PauseAllSounds(void);

void UnPauseAllSounds(void);

void PlayMusic(unsigned char _i, bool _setLoop, float _volume = 100.f * GetSoundMultiplier());

void StopMusic(unsigned char _i);

void StopAllMusics(void);

void PauseAllMusics(void);

void UnPauseAllMusics(void);

void FadeMusic(int _i, float _dt, float _speedPerSec = 1.f);

void SetMusicFadeOut(int _i, bool _bool);

sf::Sound::Status GetSoundStatus(unsigned char _i);

float GetSoundVolume(unsigned char _i);

sf::SoundBuffer* GetSoundBuffer(unsigned char _i);

sf::Sound GetSound(unsigned char _i);

void SetSoundVolume(unsigned char _i, float _volume = 100.f * GetSoundMultiplier());

void SetAllSoundVolume();

sf::Music::Status GetMusicStatus(unsigned char _i);

float GetMusicVolume(unsigned char _i);

void SetMusicVolume(unsigned char _i, float _volume = 100.f * GetSoundMultiplier());

void SetAllMusicVolume();

#endif // ! AUDIO_H



