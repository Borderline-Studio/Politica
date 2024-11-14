#include "Utils.h"

sf::Vector2f CartesianToIsometric(float _x, float _y, float _z, float _size)
{
	return sf::Vector2f
	(
		(float)((_x - _y) * _size / 2.f),
		(float)((_x + _y) * _size / 3.5f - _z * _size * 0.54687f)
	);
}

sf::Vector2f CartesianToIsometricNotEquilateral(float _x, float _y, float _z, float _size)
{
	return sf::Vector2f(
		(float)((_x - _y) * _size / 2),
		(float)((_x + _y) * _size / 4 - _z * _size * 0.625f)
	);
}

sf::Vector2f IsometricToCartesian(float _x, float _y, float _z, float _size)
{
	float X = (7 * _y + 4 * _x + 3.85 * _size * _z) / (4 * _size);
	float Y = X - 2 * _x / _size;

	return sf::Vector2f(X, Y);
}

sf::Vector2f IsometricToCartesianNotEquilateral(float _x, float _y, float _size)
{
	return sf::Vector2f
	(
		(_y / (float)(_size / 2.f) + _x / (float)(_size)),
		(_y / (float)(_size / 2.f) - _x / (float)(_size))

	);
}

sf::Vector2f PosToScreen(sf::Vector2f _pos)
{
	return sf::Vector2f
	(
		(_pos.x / WORKING_WIDTH) * GetScreen().width,
		(_pos.y / WORKING_HEIGHT) * GetScreen().height
	);
}

float PosToScreenX(float _x)
{
	return (_x / WORKING_WIDTH) * GetScreen().width;
}

float PosToScreenY(float _y)
{
	return (_y / WORKING_HEIGHT) * GetScreen().height;
}

sf::Vector2f ScaleToScreen(float _scaleX, float _scaleY)
{
	return sf::Vector2f
	(
		(float)(GetScreen().width / WORKING_WIDTH) * _scaleX,
		(float)(GetScreen().height / WORKING_HEIGHT) * _scaleY
	);
}

sf::Sprite LoadSprite(std::string _sNom, bool _isCentered)
{
	sf::Sprite tempSprite;
	sf::Texture* tempTexture = new sf::Texture();
	tempTexture->loadFromFile(_sNom);
	tempTexture->setSmooth(true);
	tempSprite.setTexture(*tempTexture);
	tempSprite.setScale(ScaleToScreen(1.f, 1.f));

	if (_isCentered) //Centrage
	{
		sf::Vector2u tempTaille = tempTexture->getSize();
		sf::Vector2f nouvelleTaille(tempTaille.x / 2.0f, tempTaille.y / 2.0f);
		tempSprite.setOrigin(nouvelleTaille);
	}


	return tempSprite;
}

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window, float _angle, sf::RenderStates _blendMode)
{
	_sprite.setPosition(_pos);
	_sprite.setRotation(_angle);
	_window.draw(_sprite, _blendMode);
}

void BlitRectangleShape(sf::RectangleShape _rect, sf::Vector2f _pos, sf::RenderWindow& _window, float _angle)
{
	_rect.setPosition(_pos);
	_rect.setRotation(_angle);
	_window.draw(_rect);
}

sf::Sprite& CreateSprite(sf::Texture& _texture, sf::Vector2f _pos, bool _isCentered, sf::Vector2f _scale, float _rotation)
{
	sf::Sprite temp;
	_texture.setSmooth(true);
	temp.setTexture(_texture);
	temp.setScale(_scale);
	if (_isCentered)
	{
		temp.setOrigin((float)(_texture.getSize().x) / 2.f, (float)(_texture.getSize().y) / 2.f);
	}
	temp.setPosition(_pos);
	temp.setRotation(_rotation);


	return temp;
}

sf::Sprite CreateSpriteWithAnims(sf::Texture& _texture, sf::Vector2i _nbFramesXY, bool _isCentered, sf::Vector2f _scale, sf::Vector2f _pos)
{
	sf::Sprite* temp = new sf::Sprite;
	temp->setTexture(_texture);
	if (_isCentered)
	{
		temp->setOrigin(_texture.getSize().x / (2.f * _nbFramesXY.x), _texture.getSize().y / (2.f * _nbFramesXY.y));
	}
	temp->setPosition(_pos);
	temp->setScale(_scale);


	return (*temp);
}

void CreateRectangleShape(sf::RectangleShape& _rect, sf::Vector2f _pos, sf::Vector2f _size, sf::Color _color, bool _isCentered)
{
	_rect.setSize(_size);
	if (_isCentered)
	{
		_rect.setOrigin(sf::Vector2f(_size.x / 2.f, _size.y / 2.f));
	}
	_rect.setPosition(_pos);
	_rect.setFillColor(_color);
	_rect.setOutlineColor(sf::Color::Magenta);
}

void CreateCircleShape(sf::CircleShape& _circle, sf::Vector2f _pos, float _rad, bool _isCentered, sf::Color _color)
{
	_circle.setRadius(_rad);
	if (_isCentered)
	{
		_circle.setOrigin(_rad / 2.f, _rad / 2.f);
	}
	_circle.setPosition(_pos);
	_circle.setFillColor(_color);
	_circle.setOutlineColor(sf::Color::Magenta);
}

void SetCenteredString(sf::Text& _text, const std::string _string)
{
	_text.setString(_string);
	_text.setOrigin(sf::Vector2f(_text.getGlobalBounds().width / 2.f, _text.getGlobalBounds().height / 2.f));
}

void CreateText(sf::Text& _text, sf::Font& _font, const std::string _string, int _size, sf::Color _color, bool _isCentered)
{
	_text.setFont(_font);
	_text.setCharacterSize(_size);
	_text.setScale(1.f, 1.f);
	if (_isCentered)
	{
		SetCenteredString(_text, _string);
	}
	else
	{
		_text.setString(_string);
	}
	_text.setFillColor(_color);
}

sf::String ToString(int _int)
{
	char numstr[10];
	sprintf_s(numstr, "%i", _int);
	return numstr;
}

std::string ConvertKeyToString(sf::Event::TextEvent _text)
{
	sf::Uint32 unicode = _text.unicode;
	std::string string;
	sf::Utf32::encodeWide(unicode, std::back_inserter(string));

	return string;
}


bool IsCircleContains(sf::CircleShape& _c1, sf::Vector2f _p1)
{
	float distX = _c1.getPosition().x - _p1.x;
	float distY = _c1.getPosition().y - _p1.y;
	float distance = distX * distX + distY * distY;
	return distance < _c1.getRadius()* _c1.getRadius();
}

void CreateFade(Fade& _fade, bool _isFadingIn, bool _isFadingOut)
{
	_fade.isFadingIn = _isFadingIn;
	_fade.isFadingOut = _isFadingOut;

	_fade.timerMin = 0;
	_fade.timerMax = 2;
	_fade.timer = (float)_fade.timerMin;

	_fade.alphaMin = 0;
	_fade.alphaMax = 255;
	_fade.alpha = (float)_fade.alphaMin;
	_fade.color = sf::Color(255, 255, 255, (sf::Uint8)_fade.alpha);
}

void CreateFadeRect(Fade& _fade, bool _isFadingIn, bool _isFadingOut)
{
	_fade.isFadingIn = _isFadingIn;
	_fade.isFadingOut = _isFadingOut;

	_fade.timerMin = 0.f;
	_fade.timerMax = 2.f;
	_fade.timer = _fade.timerMax;

	_fade.alphaMin = 0.f;
	_fade.alphaMax = 255.f;
	_fade.alpha = _fade.alphaMax;
	_fade.color = sf::Color(0, 0, 0, (sf::Uint8)_fade.alpha);
	CreateRectangleShape(_fade.rect, PosToScreen(sf::Vector2f(0.f, 0.f)), sf::Vector2f(GetScreen().width, GetScreen().height), _fade.color, false);
}

void UpdateFade(Fade& _fade, float _dt, float _speedPerSec = 1.f)
{
	if (_fade.isFadingOut)
	{

		_fade.timer = _fade.timer - _dt;
		_fade.alpha = fmaxf(((_fade.timer * _speedPerSec) / _fade.timerMax) * _fade.alphaMax, (float)_fade.alphaMin);
		_fade.color = sf::Color(255, 255, 255, (sf::Uint8)_fade.alpha);
		if (_fade.timer <= _fade.timerMin)
		{
			_fade.isFadingOut = false;
		}
	}

	if (_fade.isFadingIn)
	{

		_fade.timer = _fade.timer + _dt;
		_fade.alpha = fminf(((_fade.timer * _speedPerSec) / _fade.timerMax) * _fade.alphaMax, _fade.alphaMax);
		_fade.color = sf::Color(255, 255, 255, (sf::Uint8)_fade.alpha);
		if (_fade.timer >= _fade.timerMax)
		{
			_fade.isFadingIn = false;
		}
	}
}

//Maths

float DegreesToRadians(float angle)
{
	return angle * (float)PI / 180;
}

float RadiansToDegrees(float angle)
{
	return angle * 180 / (float)PI;
}

sf::Vector2f GetVector(sf::Vector2f p1, sf::Vector2f p2)
{
	return sf::Vector2f(p2.x - p1.x, p2.y - p1.y);
}

float GetVectorLength(sf::Vector2f vector)
{
	return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float GetSquaredLength(sf::Vector2f vector)
{
	return vector.x * vector.x + vector.y * vector.y;
}

float SquaredDistance(sf::Vector2f p1, sf::Vector2f p2)
{
	return GetSquaredLength(GetVector(p1, p2));
}

float DotProduct(sf::Vector2f v1, sf::Vector2f v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

sf::Vector2f NormalizeVector(sf::Vector2f vector)
{
	float vectorLength = GetVectorLength(vector);

	if (vectorLength == 0.0f)
	{
		return sf::Vector2f(0, 0);
	}

	float newX = vector.x / vectorLength;
	float newY = vector.y / vectorLength;

	return sf::Vector2f(newX, newY);
}

static sf::Vector2f RotateVector(sf::Vector2f vector, float angle)
{
	float COS = cos(angle);
	float SIN = sin(angle);

	float newX = vector.x * COS - vector.y * SIN;
	float newY = vector.x * SIN + vector.y * COS;

	return sf::Vector2f(newX, newY);
}

sf::Vector2f GetRectangleLengthAxis(sf::RectangleShape& rect)
{
	sf::Vector2f rectSize = rect.getSize();
	float rectRotation = DegreesToRadians(rect.getRotation());

	return sf::Vector2f(rectSize.x * cos(rectRotation), rectSize.x * sin(rectRotation));
}

sf::Vector2f GetRectangleHeightAxis(sf::RectangleShape& rect)
{
	sf::Vector2f rectSize = rect.getSize();
	float rectRotation = DegreesToRadians(rect.getRotation());

	return sf::Vector2f(-rectSize.y * sin(rectRotation), rectSize.y * cos(rectRotation));
}

sf::Vector2f* GetRectangleCorners(sf::RectangleShape& rect)
{
	sf::Vector2f* corners = new sf::Vector2f[4];

	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f lengthAxis = GetRectangleLengthAxis(rect);
	sf::Vector2f heightAxis = GetRectangleHeightAxis(rect);

	corners[0] = sf::Vector2f(rectPos.x - lengthAxis.x / 2 - heightAxis.x / 2, rectPos.y - lengthAxis.y / 2 - heightAxis.y / 2);
	corners[1] = sf::Vector2f(rectPos.x - lengthAxis.x / 2 + heightAxis.x / 2, rectPos.y - lengthAxis.y / 2 + heightAxis.y / 2);
	corners[2] = sf::Vector2f(rectPos.x + lengthAxis.x / 2 + heightAxis.x / 2, rectPos.y + lengthAxis.y / 2 + heightAxis.y / 2);
	corners[3] = sf::Vector2f(rectPos.x + lengthAxis.x / 2 - heightAxis.x / 2, rectPos.y + lengthAxis.y / 2 - heightAxis.y / 2);

	return corners;
}

bool CollisionCirleCircle(sf::CircleShape& _c1, sf::CircleShape& _c2)
{
	return SquaredDistance(sf::Vector2f(_c1.getGlobalBounds().left, _c1.getGlobalBounds().top), sf::Vector2f(_c2.getGlobalBounds().left, _c2.getGlobalBounds().top)) <= (_c1.getRadius() + _c2.getRadius()) * (_c1.getRadius() + _c2.getRadius());
}

bool IsCollidingAABBs(sf::FloatRect _rect1, sf::FloatRect _rect2)
{
	if (_rect1.left + _rect1.width < _rect2.left || _rect1.left > _rect2.left + _rect2.width || _rect1.top + _rect1.height < _rect2.top || _rect1.top > _rect2.top + _rect2.height)
	{
		return false;
	}

	return true;
}

bool RectContains(sf::FloatRect _rect, sf::Vector2f _point)
{
	return (_point.x > _rect.left) && (_point.x < _rect.left + _rect.width) && (_point.y > _rect.top) && (_point.y < _rect.top + _rect.height);
}

bool OBBContains(sf::RectangleShape& rect, sf::Vector2f pos)
{
	sf::Vector2f rectPos = rect.getPosition();
	sf::Vector2f rectSize = rect.getSize();
	float rectRotation = DegreesToRadians(rect.getRotation());

	float COS = cos(rectRotation);
	float SIN = sin(rectRotation);

	sf::Vector2f lengthAxis(rectSize.x * COS, rectSize.x * SIN);
	sf::Vector2f heightAxis(-rectSize.y * SIN, rectSize.y * COS);

	sf::Vector2f corner(rectPos.x - lengthAxis.x / 2 - heightAxis.x / 2, rectPos.y - lengthAxis.y / 2 - heightAxis.y / 2);
	sf::Vector2f CornerToPos(pos.x - corner.x, pos.y - corner.y);

	float xDot = DotProduct(lengthAxis, CornerToPos);
	float maxDotX = DotProduct(lengthAxis, lengthAxis);

	if (xDot < 0 || xDot > maxDotX)
	{
		return false;
	}

	float yDot = DotProduct(heightAxis, CornerToPos);
	float maxDotY = DotProduct(heightAxis, heightAxis);

	if (yDot < 0 || yDot > maxDotY)
	{
		return false;
	}

	return true;
}


bool SpriteContainsPixelPerfect(sf::Image _image, sf::Vector2f _imagePos, sf::Vector2f _point)
{
	sf::Color pixColor = _image.getPixel((unsigned int)(_point.x - _imagePos.x), (unsigned int)(_point.y - _imagePos.y));
	return (pixColor.a != 0);
}

bool CircleSegmentCollision(sf::CircleShape& circle, sf::Vector2f point1, sf::Vector2f point2)
{
	//init
	sf::Vector2f P1CircleVect = GetVector(point1, circle.getPosition());
	sf::Vector2f P2CircleVect = GetVector(point2, circle.getPosition());
	sf::Vector2f P1P2Vect = GetVector(point1, point2);

	sf::Vector2f P1ProjectionVect =
	{ DotProduct(P1P2Vect,P1CircleVect) / GetSquaredLength(P1P2Vect) * P1P2Vect.x,
		DotProduct(P1P2Vect,P1CircleVect) / GetSquaredLength(P1P2Vect) * P1P2Vect.y
	};

	sf::Vector2f projectionPoint = { point1.x + P1ProjectionVect.x, point1.y + P1ProjectionVect.y };
	sf::Vector2f CircleProjectionVect = GetVector(circle.getPosition(), projectionPoint);

	//collision tests

	if (GetVectorLength(P1CircleVect) <= circle.getRadius() || GetVectorLength(P2CircleVect) <= circle.getRadius())
	{
		return true;
	}

	if (DotProduct(P1P2Vect, P1ProjectionVect) < 0 || DotProduct(P1P2Vect, P1ProjectionVect) > GetSquaredLength(P1P2Vect))
	{
		return false;
	}

	if (GetSquaredLength(CircleProjectionVect) < circle.getRadius() * circle.getRadius())
	{
		return true;
	}

	return false;
}

bool CircleRectangleCollision(sf::CircleShape& circle, sf::RectangleShape& rect)
{
	sf::FloatRect rectBounds = rect.getGlobalBounds();
	sf::Vector2f* corners = GetRectangleCorners(rect);

	if (RectContains(rect.getGlobalBounds(), circle.getPosition()))
	{
		delete[] corners;
		return true;
	}

	if (IsCircleContains(circle, rect.getPosition()))
	{
		delete[] corners;
		return true;
	}

	for (unsigned char i = 0; i < 4; i++)
	{
		for (unsigned char j = 0; j < 4; j++)
		{
			if (CircleSegmentCollision(circle, corners[i], corners[j]))
			{
				delete[] corners;
				return true;
			}
		}
	}

	delete[] corners;

	return false;
}


//Rand functions

int RandomMinMax(int _min, int _max)
{
	return rand() % (_max - _min) + _min;
}

//easings and Lerps

//for cerp and lerp, returns a vector that is the current position between a and b according to t that represents the progression of the action between 0 and 1
sf::Vector2f Cerp(sf::Vector2f _a, sf::Vector2f _b, float _t)
{
	float temp;
	temp = (1.f - cosf(_t * PI)) * 0.5f;

	return sf::Vector2f(
		(_a.x * (1.f - temp) + _b.x * temp),
		(_a.y * (1.f - temp) + _b.y * temp)
	);

}

sf::Vector2f Lerp(sf::Vector2f _a, sf::Vector2f _b, float _t)
{
	return sf::Vector2f
	(
		(1.f - _t) * _a.x + _t * _b.x,
		(1.f - _t) * _a.y + _t * _b.y
	);
}

sf::Vector2f Lerp2(sf::Vector2f _a, sf::Vector2f _b, float _t)
{
	return sf::Vector2f
	(
		_a.x + (_b.x - _a.x) * _t,
		_a.y + (_b.y - _a.y) * _t
	);
}

//for easings, just give the progression between 0 and 1 and multiply the return by the speed of your object (i think?)

float EaseInSine(float _t)
{
	return 1 - cosf((_t * PI) / 2.f);
}

float EaseOutSine(float _t)
{
	return sinf((_t * PI) / 2.f);
}

float EaseInOutSine(float _t)
{
	return -(cosf(PI * _t) - 1.f) / 2.f;
}

float EaseInQuad(float _t)
{
	return _t * _t;
}

float EaseOutQuad(float _t)
{
	return 1.f - (1.f - _t) * (1.f - _t);
}

float EaseInOutQuad(float _t)
{
	return _t < 0.5f ? 2.f * _t * _t : 1.f - powf(-2.f * _t + 2.f, 2.f) / 2.f;
}

float EaseInCubic(float _t)
{
	return _t * _t * _t;
}

float EaseOutCubic(float _t)
{
	return 1.f - powf(1.f - _t, 3.f);
}

float EaseInOutCubic(float _t)
{
	return _t < 0.5f ? 4.f * _t * _t * _t : 1.f - powf(-2.f * _t + 2.f, 3.f) / 2.f;
}

float EaseInQuart(float _t)
{
	return _t * _t * _t * _t;
}

float EaseOutQuart(float _t)
{
	return 1.f - powf(1.f - _t, 4.f);
}

float EaseInOutQuart(float _t)
{
	return _t < 0.5f ? 8.f * _t * _t * _t * _t : 1.f - powf(-2.f * _t + 2.f, 4.f) / 2.f;
}

float EaseInQuint(float _t)
{
	return _t * _t * _t * _t * _t;
}

float EaseOutQuint(float _t)
{
	return 1.f - powf(1.f - _t, 5.f);
}

float EaseInOutQuint(float _t)
{
	return _t < 0.5f ? 16.f * _t * _t * _t * _t * _t : 1.f - powf(-2.f * _t + 2.f, 5.f) / 2.f;
}

float EaseInExpo(float _t)
{
	return _t == 0.f ? 0.f : powf(2.f, 10.f * _t - 10.f);
}

float EaseOutExpo(float _t)
{
	return _t == 1.f ? 1.f : 1.f - powf(2.f, -10.f * _t);
}

float EaseInOutExpo(float _t)
{
	if (_t == 0)
	{
		return 0;
	}
	else if (_t == 1)
	{
		return 1;
	}
	else
	{
		return  _t < 0.5f ? powf(2.f, 20.f * _t - 10.f) / 2.f : (2.f - powf(2.f, -20.f * _t + 10.f)) / 2.f;
	}
}

float EaseInCirc(float _t)
{
	return 1.f - sqrtf(1.f - powf(_t, 2.f));
}

float EaseOutCirc(float _t)
{
	return sqrtf(1.f - powf(_t - 1.f, 2.f));
}

float EaseInOutCirc(float _t)
{
	return _t < 0.5f
		? (1.f - sqrtf(1.f - powf(2.f * _t, 2.f))) / 2.f
		: (sqrtf(1.f - powf(-2.f * _t + 2.f, 2.f)) + 1.f) / 2.f;
}

float EaseInBack(float _t)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.f;

	return c3 * _t * _t * _t - c1 * _t * _t;
}

float EaseOutBack(float _t)
{
	const float c1 = 1.70158f;
	const float c3 = c1 + 1.f;

	return 1.f + c3 * powf(_t - 1.f, 3.f) + c1 * powf(_t - 1.f, 2.f);
}

float EaseInOutBack(float _t)
{
	const float c1 = 1.70158f;
	const float c2 = c1 * 1.525f;

	return _t < 0.5f
		? (powf(2.f * _t, 2.f) * ((c2 + 1.f) * 2.f * _t - c2)) / 2.f
		: (powf(2.f * _t - 2.f, 2.f) * ((c2 + 1.f) * (_t * 2.f - 2.f) + c2) + 2.f) / 2.f;
}

float EaseInElastic(float _t)
{
	const float c4 = (2.f * PI) / 3.f;

	if (_t == 0)
	{
		return 0;
	}
	else if (_t == 1)
	{
		return 1;
	}
	else
	{
		return -powf(2.f, 10.f * _t - 10.f) * sinf((_t * 10.f - 10.75f) * c4);
	}
}

float EaseOutElastic(float _t)
{
	const float c4 = (2.f * PI) / 3.f;

	if (_t == 0)
	{
		return 0;
	}
	else if (_t == 1)
	{
		return 1;
	}
	else
	{
		return powf(2.f, -10.f * _t) * sinf((_t * 10.f - 0.75f) * c4) + 1.f;
	}
}

float EaseInOutElastic(float _t)
{
	const float c5 = (2.f * PI) / 4.5f;

	if (_t == 0)
	{
		return 0;
	}
	else if (_t == 1)
	{
		return 1;
	}
	else
	{
		return _t < 0.5f
			? -(powf(2.f, 20.f * _t - 10.f) * sinf((20.f * _t - 11.125f) * c5)) / 2.f
			: (powf(2.f, -20.f * _t + 10.f) * sinf((20.f * _t - 11.125f) * c5)) / 2.f + 1.f;
	}
}

float EaseInBounce(float _t)
{
	return 1.f - EaseOutBounce(1.f - _t);
}

float EaseOutBounce(float _t)
{
	const float n1 = 7.5625f;
	const float d1 = 2.75f;

	if (_t < 1.f / d1)
	{
		return n1 * _t * _t;
	}
	else if (_t < 2.f / d1)
	{
		return n1 * (_t -= 1.5f / d1) * _t + 0.75f;
	}
	else if (_t < 2.5f / d1)
	{
		return n1 * (_t -= 2.25f / d1) * _t + 0.9375f;
	}
	else
	{
		return n1 * (_t -= 2.625 / d1) * _t + 0.984375f;
	}
}

float EaseInOutBounce(float _t)
{
	return _t < 0.5f
		? (1.f - EaseOutBounce(1.f - 2.f * _t)) / 2.f
		: (1.f + EaseOutBounce(2.f * _t - 1.f)) / 2.f;
}