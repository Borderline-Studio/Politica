#ifndef  UTILS_H
#define UTILS_H

#define PI 3.141592f
#define WORKING_WIDTH 1920
#define WORKING_HEIGHT 1080
#include <iostream>
#include <time.h>
#include<cmath>
#include<vector>
#include<string>
#include <vector>

#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/freeglut.h>
#include "SFML/OpenGL.hpp"

//#include <json/json.h>

struct Screen
{
	float width;
	float height;
};

struct Hitbox
{
	sf::Vector2f position;
	sf::Vector2f size;
};

struct Fade
{
	bool isFadingIn = false;
	bool isFadingOut = false;
	float timerMin = 0.f;
	float timerMax = 2.f;
	float timer = 0.f;
	float alphaMin = 0.f;
	float alphaMax = 0.f;
	float alpha = 0.f;
	sf::Color color;
	sf::RectangleShape rect;
};

Screen GetScreen(void);

sf::Vector2f CartesianToIsometric(float _x, float _y, float _z, float _size);

sf::Vector2f IsometricToCartesian(float _x, float _y, float _z, float _size);

sf::Vector2f IsometricToCartesianNotEquilateral(float _x, float _y, float _size);

sf::Vector2f PosToScreen(sf::Vector2f _pos);

float PosToScreenX(float _x);

float PosToScreenY(float _y);

sf::Vector2f ScaleToScreen(float _scaleX, float _scaleY);

sf::Sprite LoadSprite(std::string _sNom, bool _isCentered = false);

sf::Sprite& CreateSprite(sf::Texture& _texture, sf::Vector2f _pos, bool _isCentered = true, sf::Vector2f _scale = ScaleToScreen(1.f, 1.f), float _rotation = 0.f);

sf::Sprite CreateSpriteWithAnims(sf::Texture& _texture, sf::Vector2i _nbFramesXY, bool _isCentered, sf::Vector2f _scale, sf::Vector2f _pos);

void SetCenteredString(sf::Text& _text, const std::string _string);

void CreateText(sf::Text& _text, sf::Font& _font, const std::string _string, int _size, sf::Color _color, bool _isCentered = true);

void CreateRectangleShape(sf::RectangleShape& _rect, sf::Vector2f _pos = { GetScreen().width / 2.f, GetScreen().height / 2.f }, sf::Vector2f _size = { 100.f, 100.f }, sf::Color _color = sf::Color::White, bool _isCentered = true);

void CreateCircleShape(sf::CircleShape& _circle, sf::Vector2f _pos = {GetScreen().width/2.f, GetScreen().height/2.f}, float _rad = 50.f, bool _isCentered = true, sf::Color _color = sf::Color::White);

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window, float _angle = 0.f, sf::RenderStates _blendMode = sf::BlendAlpha);

void BlitRectangleShape(sf::RectangleShape _rect, sf::Vector2f _pos, sf::RenderWindow& _window, float _angle);

sf::String ToString(int _int);

std::string ConvertKeyToString(sf::Event::TextEvent _text);

bool IsCircleContains(sf::CircleShape& _c1, sf::Vector2f _p1);

void CreateFade(Fade& _fade, bool _isFadingIn = false, bool _isFadingOut = false);

void CreateFadeRect(Fade& _fade, bool _isFadingIn = false, bool _isFadingOut = false);

void UpdateFade(Fade& _fade, float _dt, float _speedPerSec);

float DegreesToRadians(float angle);

float RadiansToDegrees(float angle);

sf::Vector2f GetVector(sf::Vector2f p1, sf::Vector2f p2);

float GetVectorLength(sf::Vector2f vector);

float GetSquaredLength(sf::Vector2f vector);

float SquaredDistance(sf::Vector2f p1, sf::Vector2f p2);

float DotProduct(sf::Vector2f v1, sf::Vector2f v2);

sf::Vector2f NormalizeVector(sf::Vector2f vector);

sf::Vector2f RotateVector(sf::Vector2f vector, float angle);

sf::Vector2f GetRectangleLengthAxis(sf::RectangleShape& rect);

sf::Vector2f GetRectangleHeightAxis(sf::RectangleShape& rect);

sf::Vector2f* GetRectangleCorners(sf::RectangleShape& rect);

bool CollisionCirleCircle(sf::CircleShape& _c1, sf::CircleShape& _c2);

bool IsCollidingAABBs(sf::FloatRect _rect1, sf::FloatRect _rect2);

bool RectContains(sf::FloatRect _rect, sf::Vector2f _point);

bool OBBContains(sf::RectangleShape& rect, sf::Vector2f pos);

bool SpriteContainsPixelPerfect(sf::Image _image, sf::Vector2f _imagePos, sf::Vector2f _point);

bool CircleSegmentCollision(sf::CircleShape& circle, sf::Vector2f point1, sf::Vector2f point2);

bool CircleRectangleCollision(sf::CircleShape& circle, sf::RectangleShape& rect);

int RandomMinMax(int _min, int _max);

sf::Vector2f Cerp(sf::Vector2f _a, sf::Vector2f _b, float _t);

sf::Vector2f Lerp(sf::Vector2f _a, sf::Vector2f _b, float _t);

sf::Vector2f Lerp2(sf::Vector2f _a, sf::Vector2f _b, float _t);

float EaseInSine(float _t);

float EaseOutSine(float _t);

float EaseInOutSine(float _t);

float EaseInQuad(float _t);

float EaseOutQuad(float _t);

float EaseInOutQuad(float _t);

float EaseInCubic(float _t);

float EaseOutCubic(float _t);

float EaseInOutCubic(float _t);

float EaseInQuart(float _t);

float EaseOutQuart(float _t);

float EaseInOutQuart(float _t);

float EaseInQuint(float _t);

float EaseOutQuint(float _t);

float EaseInOutQuint(float _t);

float EaseInExpo(float _t);

float EaseOutExpo(float _t);

float EaseInOutExpo(float _t);

float EaseInCirc(float _t);

float EaseOutCirc(float _t);

float EaseInOutCirc(float _t);

float EaseInBack(float _t);

float EaseOutBack(float _t);

float EaseInOutBack(float _t);

float EaseInElastic(float _t);

float EaseOutElastic(float _t);

float EaseInOutElastic(float _t);

float EaseInBounce(float _t);

float EaseOutBounce(float _t);

float EaseInOutBounce(float _t);


#endif 

