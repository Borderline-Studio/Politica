#ifndef  PARTICLE_H
#define PARTICLE_H

#include "Common.h"
#include "Audio.h"
#define MAX_PARTICLE 1024

struct Particle
{
    sf::Vector2f pos;
    sf::Vector2f speed;
    float ttl;
    float ttlMax;
    sf::Vector3i factorColor;
};


struct FireWork
{
    sf::Vector2f pos;
    sf::Vector2f speed;
    float heightMax;
    sf::Sprite firework;
    bool soundHissPlay;
    float timerSoundHiss;
};

void DrawParticleFireWork(sf::RenderWindow& _window);
#endif