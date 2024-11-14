#include "Particle.h"
#define NB_FIREWORK 3
std::vector <Particle> particle;
std::vector <Particle> particleFireWork;
FireWork fireWork[NB_FIREWORK];

sf::Sprite sprite = LoadSprite("Assets/Images/Particle/Particle.png", false);
float timer = 0;
float timer2 = 0;
float timer3 = 0;

unsigned char boomSound[NB_FIREWORK] = {0};

unsigned char hissSound[NB_FIREWORK] = {0};

void InitFireWork()
{

	for (int i = 0; i < NB_FIREWORK; i++)
	{
		fireWork[i].pos = { (float)(rand() % (int)GetScreen().width),(float)(rand() % (int)GetScreen().height- 100- (int)GetScreen().height) };
		fireWork[i].speed = { (float)(rand()%50),800};
		fireWork[i].heightMax = (float)(rand() % ((int)GetScreen().height / 2));
		fireWork[i].firework = LoadSprite("Assets/Images/Particle/FireWork.png", true);

		boomSound[i] = AddSound("Assets/Sounds/FireworkBoom.ogg");
		hissSound[i] = AddSound("Assets/Sounds/HissFirework.ogg");
	}
}

void AddParticleHud(sf::Vector2f& _hudPos)
{
	Particle tempParticle;

	//Dices
	tempParticle.pos.x = _hudPos.x + rand() % (int)PosToScreenX(200) - (int)PosToScreenX(100);
	tempParticle.pos.y = _hudPos.y + rand() % (int)PosToScreenY(100) - (int)PosToScreenY(50);

	float angle = 2 * PI * rand() / (float)RAND_MAX;
	float amplitude = rand() / (float)RAND_MAX * 300;

	tempParticle.speed.x = (cosf(angle) * amplitude * 1.1f);
	tempParticle.speed.y = (sinf(angle) * amplitude / 1.5f);

	tempParticle.ttl = 0;
	tempParticle.ttlMax = 0.01f + 1 * rand() / (float)RAND_MAX;

	particle.push_back(tempParticle);
}

void AddParticleStack(sf::Vector2f& _hudPos)
{
	Particle tempParticle;

	//Dices
	tempParticle.pos.x = _hudPos.x + rand() % (int)PosToScreenX(350) - (int)PosToScreenX(175);
	tempParticle.pos.y = _hudPos.y + rand() % (int)PosToScreenY(190) - (int)PosToScreenY(95);

	float angle = 2 * PI * rand() / (float)RAND_MAX;
	float amplitude = rand() / (float)RAND_MAX * 300;

	tempParticle.speed.x = (cosf(angle) * amplitude * 1.1f);
	tempParticle.speed.y = (sinf(angle) * amplitude / 1.5f);

	tempParticle.ttl = 0;
	tempParticle.ttlMax = 0.01f + 1 * rand() / (float)RAND_MAX;

	particle.push_back(tempParticle);
}
void AddParticleFirework(sf::Vector2f& _fireWorkPos)
{
	Particle tempParticle;

	//Dices
	tempParticle.pos.x = _fireWorkPos.x - PosToScreenX(2);
	tempParticle.pos.y = _fireWorkPos.y + PosToScreenY(25);

	tempParticle.ttl = 0;
	tempParticle.ttlMax = 0.01f + 1 * rand() / (float)RAND_MAX;
	tempParticle.factorColor = {1,2,4};
	particleFireWork.push_back(tempParticle);
}

void AddParticleGameOver(sf::Vector2f& _pos, sf::Vector3i& _randColor)
{
	//Création particule temporaire
	for (int i = 0; i < 500; i++)
	{
		Particle tempParticle;

		tempParticle.pos = _pos;


		float angle = 2 * PI * rand() / (float)RAND_MAX;
		float amplitude = powf(rand() / (float)RAND_MAX, 1) * 2000;

		tempParticle.speed.x = cosf(angle) * amplitude;
		tempParticle.speed.y = sinf(angle) * amplitude;

		tempParticle.ttl = 0;
		tempParticle.ttlMax = 0.01f + 5 * rand() / (float)RAND_MAX;
		tempParticle.factorColor = _randColor;
		particle.push_back(tempParticle);
	}
}

void UpdateFireWork(float& _dt)
{
	for (int i = 0; i < NB_FIREWORK; i++)
	{
		fireWork[i].speed.x += _dt*5;
		fireWork[i].pos.x += cosf(fireWork[i].speed.x);
		fireWork[i].pos.y -= fireWork[i].speed.y * _dt;
		AddParticleFirework(fireWork[i].pos);
		if (fireWork[i].pos.y <= fireWork[i].heightMax)
		{
			sf::Vector3i randColor = { rand() % 16 + 1,rand() % 16 + 1,rand() % 16 + 1 };
			sf::Vector2f pos = fireWork[i].pos;
			StopSound(boomSound[i]);
			PlaySoundFromList(boomSound[i], 10);
			AddParticleGameOver(pos, randColor);
			fireWork[i].heightMax = (float)(rand() % ((int)GetScreen().height / 2));
			fireWork[i].pos = { (float)(rand() % (int)GetScreen().width),(float)(rand()% (int)PosToScreenY(100)+  (int)GetScreen().height) };
			fireWork[i].soundHissPlay = true;
			fireWork[i].timerSoundHiss = 0;
			
		}
		if (fireWork[i].soundHissPlay)
		{
			fireWork[i].timerSoundHiss += _dt;
			if (fireWork[i].timerSoundHiss >= 0.05f)
			{
				StopSound(hissSound[i]);
				PlaySoundFromList(hissSound[i], 1);
				fireWork[i].timerSoundHiss = 0;
				fireWork[i].soundHissPlay = false;

			}
		}
	}
}


void UpdateParticleHudPlayer(float& _dt)
{
	for (int i = particle.size() - 1; i >= 0; i--)
	{

		//Variation de speed (ralentissement)
		particle[i].speed /= 1 + _dt * 5;
		//particle[i].speed.x += sin(10 * particle[i].ttl);
		//Application de la speed

/*		particle[i].pos.y += particle[i].speed.y * _dt;
		particle[i].pos.x += particle[i].speed.x * _dt / 10;*/

		particle[i].pos += particle[i].speed * _dt;
		//Gestion du TTL
		particle[i].ttl += _dt;

		if (particle[i].ttl >= particle[i].ttlMax)
		{
			//Suppression Swap'n'pop, on écrase l'élément à effacer avec le dernier élément et on pop
			particle[i] = particle[particle.size() - 1];
			particle.pop_back();
		}

	}
}

void UpdateParticleFireWork(float& _dt)
{
	for (int i = particleFireWork.size() - 1; i >= 0; i--)
	{
		particleFireWork[i].ttl += _dt;
		if (particleFireWork[i].ttl >= particleFireWork[i].ttlMax)
		{
			//Suppression Swap'n'pop, on écrase l'élément à effacer avec le dernier élément et on pop
			particleFireWork[i] = particleFireWork[particleFireWork.size() - 1];
			particleFireWork.pop_back();
		}

	}
}

void UpdateParticleGameOver(float& _dt)
{
	UpdateParticleFireWork(_dt);
	for (int i = particle.size() - 1; i >= 0; i--)
	{
		//Variation de vitesse (ralentissement)
		particle[i].speed /= 1 + _dt * 5;

		//Application de la vitesse
		particle[i].pos += particle[i].speed * _dt;

		//Gestion du TTL
		particle[i].ttl += _dt;
		if (particle[i].ttl >= particle[i].ttlMax)
		{
			//Suppression Swap'n'pop, on écrase l'élément à effacer avec le dernier élément et on pop
			particle[i] = particle[particle.size() - 1];
			particle.pop_back();
		}
	}
}

void DrawParticleHudPlayer(sf::RenderWindow& _window)
{
	for (int i = 0; i < particle.size(); i++)
	{

		//Couleur de la particule
		float facteur = 1 - (particle[i].ttl / particle[i].ttlMax);

		sf::Color couleur = {
			(sf::Uint8)(facteur * 255),
			(sf::Uint8)(facteur * facteur * facteur * facteur * 255),
			(sf::Uint8)(powf(facteur, 16) * 255),
			(sf::Uint8)(facteur * 255) };
		sprite.setColor(couleur);

		//Orientation de la particule
		float angle = atan2f(particle[i].speed.y, particle[i].speed.x) * 180 / PI;

		//Etirement de la particule
		//float norme = sqrtf(particle[i].speed.x * particle[i].speed.x + particle[i].speed.y * particle[i].speed.y);
		sprite.setScale(1, 1);

		BlitSprite(sprite, particle[i].pos, _window, angle, sf::BlendAdd);
	}
}

void DrawParticleGameOver(sf::RenderWindow& _window)
{
	
	for (int i = 0; i < particle.size(); i++)
	{
		//Couleur de la particule
		float facteur = 1 - (particle[i].ttl / particle[i].ttlMax);

		sf::Color couleur = {
			(sf::Uint8)(powf(facteur, particle[i].factorColor.x) * 255),
			(sf::Uint8)(powf(facteur,particle[i].factorColor.y) * 255),
			(sf::Uint8)(powf(facteur, particle[i].factorColor.z) * 255),
			(sf::Uint8)(facteur * 255) };
		sprite.setColor(couleur);

		//Orientation de la particule
		float angle = atan2f(particle[i].speed.y, particle[i].speed.x) * 180 / PI;

		//Etirement de la particule
		float norme = sqrtf(particle[i].speed.x * particle[i].speed.x + particle[i].speed.y * particle[i].speed.y);
		sprite.setScale(1 + norme * 0.01f, 1);

		BlitSprite(sprite, particle[i].pos, _window, angle, sf::BlendAdd);
	}
	DrawParticleFireWork(_window);
	for (int i = 0; i < NB_FIREWORK; i++)
	{
		BlitSprite(fireWork[i].firework, fireWork[i].pos, _window, 0);
	}
}

void DrawParticleFireWork(sf::RenderWindow& _window)
{
	for (int i = 0; i < particleFireWork.size(); i++)
	{
		//Couleur de la particule
		float facteur = 1 - (particleFireWork[i].ttl / particleFireWork[i].ttlMax);
		sf::Color couleur = {
			(sf::Uint8)(powf(facteur, particleFireWork[i].factorColor.x) * 255),
			(sf::Uint8)(powf(facteur,particleFireWork[i].factorColor.y) * 255),
			(sf::Uint8)(powf(facteur, particleFireWork[i].factorColor.z) * 255),
			(sf::Uint8)(facteur * 255) };
		sprite.setColor(couleur);

		//Orientation de la particule
		float angle = atan2f(particleFireWork[i].speed.y, particleFireWork[i].speed.x) * 180 / PI;

		//Etirement de la particule
		//float norme = sqrtf(particle[i].speed.x * particle[i].speed.x + particle[i].speed.y * particle[i].speed.y);
		sprite.setScale(1, 1);

		BlitSprite(sprite, particleFireWork[i].pos, _window, angle, sf::BlendAdd);
	}
}