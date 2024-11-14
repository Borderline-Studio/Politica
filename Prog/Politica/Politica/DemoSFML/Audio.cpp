#include "Audio.h"

std::vector<Sound> soundList;

//std::unique_ptr est un pointeur intelligent, qui agit comme un pointeur sur un objet et supprime cet objet dynamiquement quand l'objet sort de sa portée (une sorte d'équivalent du new)
std::vector<std::unique_ptr<Music>> musicList;

//return la position dans le vector du son, donc pour l'utiliser, conserver le return dans une variable/list/vector (si plusieurs sons à add) et s'en servir pour accéder aux autres fonctions
unsigned char AddSound(std::string _name)
{
	Sound temp;
	temp.buffer = new sf::SoundBuffer();
	temp.buffer->loadFromFile(_name);
	temp.sound.setBuffer(*(temp.buffer));

	soundList.push_back(std::move(temp));

	return ((unsigned char)soundList.size() - 1);
}

//return la position dans le vector de la musique, donc pour l'utiliser, conserver le return dans une variable/list/vector (si plusieurs musiques à add) et s'en servir pour accéder aux autres fonctions
unsigned char AddMusic(std::string _name)
{
	//auto = variable à portée locale avec caractéristiques spécifiques
	//std::make_unique = équivalent du new en plus opti(?)
	auto temp = std::make_unique<Music>();
	temp->music.openFromFile(_name);
	CreateFade(temp->fade, true);

	//déplace directement les données de la variable dans le vector sans les copier, mais peut faire en sorte que la variable en question soit désormais vide
	musicList.push_back(std::move(temp));

	return ((unsigned char)musicList.size() - 1);
}

void PlaySoundFromList(unsigned char _i, float _volume)
{
	if (soundList[_i].sound.getStatus() == sf::Sound::Stopped || soundList[_i].sound.getStatus() == sf::Sound::Paused)
	{
		soundList[_i].volume = _volume;
		soundList[_i].sound.setVolume(soundList[_i].volume * GetSoundMultiplier());
		soundList[_i].sound.play();
	}
}
void PlaySoundRepeated(unsigned char _i, float _volume)
{
	soundList[_i].volume = _volume;
	soundList[_i].sound.setVolume(soundList[_i].volume * GetSoundMultiplier());
	soundList[_i].sound.play();
}

void StopSound(unsigned char _i)
{
	if (soundList[_i].sound.getStatus() == sf::Sound::Playing)
	{
		soundList[_i].sound.stop();
	}
}

void StopAllSounds(void)
{
	for (unsigned char i = 0; i < soundList.size(); i++)
	{
		if (soundList[i].sound.getStatus() == sf::Sound::Playing)
		{
			soundList[i].sound.stop();
		}
	}
}

void PauseAllSounds(void)
{
	for (unsigned char i = 0; i < soundList.size(); i++)
	{
		if (soundList[i].sound.getStatus() == sf::Sound::Playing)
		{
			soundList[i].sound.pause();
		}
	}
}

void UnPauseAllSounds(void)
{
	for (unsigned char i = 0; i < soundList.size(); i++)
	{
		if (soundList[i].sound.getStatus() == sf::Sound::Paused)
		{
			soundList[i].sound.play();
		}
	}
}

void PlayMusic(unsigned char _i, bool _setLoop, float _volume)
{
	if (musicList[_i].get()->music.getStatus() == sf::Music::Stopped || musicList[_i].get()->music.getStatus() == sf::Music::Paused)
	{
		musicList[_i].get()->volume = _volume;
		musicList[_i].get()->music.setPosition((float)GetScreen().width / 2.f, (float)GetScreen().height / 2.f, 0.f);
		musicList[_i].get()->music.setVolume(musicList[_i].get()->volume * GetSoundMultiplier());
		musicList[_i].get()->music.setLoop(_setLoop);
		musicList[_i].get()->music.play();
	}
}


void StopMusic(unsigned char _i)
{
	if (musicList[_i].get()->music.getStatus() == sf::Music::Playing)
	{
		musicList[_i].get()->music.stop();
	}
}

void StopAllMusics(void)
{
	for (unsigned char i = 0; i < musicList.size(); i++)
	{
		if (musicList[i].get()->music.getStatus() == sf::Music::Playing)
		{
			musicList[i].get()->music.stop();
		}
	}
}

void PauseAllMusics(void)
{
	for (unsigned char i = 0; i < musicList.size(); i++)
	{
		if (musicList[i].get()->music.getStatus() == sf::Music::Playing)
		{
			musicList[i].get()->music.pause();
		}
	}
}

void UnPauseAllMusics(void)
{
	for (unsigned char i = 0; i < musicList.size(); i++)
	{
		if (musicList[i].get()->music.getStatus() == sf::Music::Paused)
		{
			musicList[i].get()->music.setPosition((float)GetScreen().width / 2.f, (float)GetScreen().height / 2.f, 0.f);
			musicList[i].get()->music.play();
		}
	}
}

void FadeMusic(int _i, float _speedPerSec, float _dt)
{
	if (musicList[_i].get()->music.getStatus() == sf::Music::Stopped || musicList[_i].get()->music.getStatus() == sf::Music::Paused)
	{
		PlayMusic(_i, 0.f);
	}

	if (musicList[_i].get()->fade.isFadingOut)
	{

		musicList[_i].get()->fade.timer = musicList[_i].get()->fade.timer - _dt;
		musicList[_i].get()->music.setVolume(musicList[_i].get()->fade.timer * _speedPerSec * GetSoundMultiplier());

		if (musicList[_i].get()->fade.timer <= musicList[_i].get()->fade.timerMin)
		{
			musicList[_i].get()->fade.isFadingOut = false;
			StopMusic(_i);
		}
	}

	else if (musicList[_i].get()->fade.isFadingIn)
	{
		musicList[_i].get()->fade.timer = musicList[_i].get()->fade.timer + _dt;
		musicList[_i].get()->music.setVolume(musicList[_i].get()->fade.timer * _speedPerSec * GetSoundMultiplier());

		if (musicList[_i].get()->fade.timer >= musicList[_i].get()->fade.timerMax)
		{
			musicList[_i].get()->fade.isFadingIn = false;

		}

	}
}
void SetMusicFadeOut(int _i, bool _bool)
{

	if (musicList[_i].get()->fade.isFadingIn)
	{
		musicList[_i].get()->fade.isFadingIn = false;
	}

	musicList[_i].get()->fade.isFadingOut = _bool;
}

sf::Sound::Status GetSoundStatus(unsigned char _i)
{
	return soundList[_i].sound.getStatus();
}

float GetSoundVolume(unsigned char _i)
{
	return soundList[_i].sound.getVolume();
}

sf::SoundBuffer* GetSoundBuffer(unsigned char _i)
{
	return (soundList[_i].buffer);
}

sf::Sound GetSound(unsigned char _i)
{
	return soundList[_i].sound;
}

void SetSoundVolume(unsigned char _i, float _volume)
{
	soundList[_i].volume = _volume;
	soundList[_i].sound.setVolume(soundList[_i].volume * GetSoundMultiplier());
}

void SetAllSoundVolume()
{
	for (unsigned char i = 0; i < soundList.size(); i++)
	{
		soundList[i].sound.setVolume(soundList[i].volume * GetSoundMultiplier());
	}	
}

sf::Music::Status GetMusicStatus(unsigned char _i)
{
	return musicList[_i].get()->music.getStatus();
}

float GetMusicVolume(unsigned char _i)
{
	return musicList[_i].get()->music.getVolume();
}

void SetMusicVolume(unsigned char _i, float _volume)
{
	musicList[_i].get()->volume = _volume;
	musicList[_i].get()->music.setVolume(musicList[_i].get()->volume * GetSoundMultiplier());
}

void SetAllMusicVolume()
{
	for (unsigned char i = 0; i < musicList.size(); i++)
	{
		musicList[i].get()->music.setVolume(musicList[i].get()->volume * GetSoundMultiplier());
	}
}

