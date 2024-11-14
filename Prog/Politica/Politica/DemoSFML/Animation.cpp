#include "Animation.h"

void CreateAnimationLeftToRight(Animation& _animation, int _totalFrameX, int _totalFrameY, sf::Vector2u _size)
{
	_animation.maxFrame = _totalFrameX - 1;
	_animation.timer = 0;
	_animation.frameSize.x = _size.x / _totalFrameX;
	_animation.frameSize.y = _size.y / _totalFrameY;
	_animation.currentFrame = 0;
	_animation.isAssigned = false;
	_animation.resetAnimTime = 0.2f;
	_animation.rect = sf::IntRect(0, 0, _animation.frameSize.x, _animation.frameSize.y );
	
}

void CreateAnimationUpToDown(Animation& _animation, int _totalFrameX, int _totalFrameY, sf::Vector2u _size)
{
	_animation.maxFrame = _totalFrameY - 1;
	_animation.timer = 0;
	_animation.frameSize.x = _size.x / _totalFrameX;
	_animation.frameSize.y = _size.y / _totalFrameY;
	_animation.currentFrame = 0;
}

void CreateAnimationUpToDownToUp(Animation& _animation, int _totalFrameX, int _totalFrameY, sf::Vector2u _size)
{
	_animation.maxFrame = _totalFrameY - 1;
	_animation.timer = 0;
	_animation.frameSize.x = _size.x / _totalFrameX;
	_animation.frameSize.y = _size.y / _totalFrameY;
	_animation.currentFrame = 0;
	_animation.upToDownFinished = false;
}

void CreateAnimationLeftToRightMultipleLines(Animation& _animation, int _totalFrameX, int _totalFrameY, int _totalLines, sf::Vector2u _size)
{
	_animation.maxFrame = _totalFrameX - 1;
	_animation.timer = 0;
	_animation.frameSize.x = _size.x / _totalFrameX;
	_animation.frameSize.y = _size.y / _totalFrameY;
	_animation.currentFrame = 0;
	_animation.isAssigned = false;
	_animation.linePlaying = 0;
	_animation.maxLine = _totalLines - 1;
	_animation.rect = sf::IntRect( 0, 0, _animation.frameSize.x, _animation.frameSize.y);
}

void UpdateAnimationLeftToRight(Animation& _animation,sf::Sprite& _sprite, float _speed, int _direction, bool _isPlaying, bool _isLooping, float _dt)
{
	if (!_animation.isAssigned)
	{
		_animation.currentFrame = 0;
		_animation.isPlaying = _isPlaying;
		_animation.isLooping = _isLooping;
		_animation.isAssigned = true;
	}

	if (_animation.isPlaying)
	{
		_animation.timer += _dt;
		if (_animation.timer > 1 / _speed)
		{
			_animation.currentFrame++;
			_animation.timer = 0;
		}
		if (_animation.currentFrame > _animation.maxFrame)
		{
			if (_animation.isLooping)
			{
				_animation.currentFrame = 0;
			}
			else
			{
				_animation.isPlaying = false;
				_animation.currentFrame = _animation.maxFrame;
				_animation.timer = 0;
			}
		}
	}
	_animation.rect.left = _animation.currentFrame * _animation.rect.width;
	_animation.rect.top = _direction * _animation.rect.height;
	_sprite.setTextureRect(_animation.rect);
}

void UpdateAnimationUpToDown(Animation& _animation,sf::Sprite& _sprite, float _speed, int _location, bool _isMoving, float _dt)
{
	if (_isMoving)
	{
		_animation.timer += _dt;
		if (_animation.timer > 1 / _speed)
		{
			_animation.currentFrame++;
			_animation.timer = 0;
		}
		if (_animation.currentFrame > _animation.maxFrame)
		{
			_animation.currentFrame = 0;
		}
	}
	else
	{
		_animation.currentFrame = 1;
	}
	sf::IntRect rect ( _location * _animation.frameSize.x, _animation.currentFrame* _animation.frameSize.y, _animation.frameSize.x, _animation.frameSize.y );
	_sprite.setTextureRect(rect);
}

void UpdateAnimationUpToDownToUp(Animation& _animation,sf::Sprite& _sprite, float _speed, int _location, bool _isMoving, float _dt)
{
	if (_isMoving)
	{
		if (_animation.upToDownFinished == false)
		{
			_animation.timer += _dt;
			if (_animation.timer > 1 / _speed)
			{
				_animation.currentFrame++;
				_animation.timer = 0;
			}
			if (_animation.currentFrame > _animation.maxFrame)
			{

				_animation.upToDownFinished = true;
				_animation.currentFrame = _animation.maxFrame;
			}
		}
		if (_animation.upToDownFinished)
		{
			_animation.timer += _dt;
			if (_animation.timer > 1 / _speed)
			{
				_animation.currentFrame--;
				_animation.timer = 0;
			}
			if (_animation.currentFrame < 0)
			{
				_animation.currentFrame = 0;
			}
		}

	}
	else
	{
		_animation.currentFrame = 1;
	}
	sf::IntRect rect ( _location* _animation.frameSize.x, _animation.currentFrame* _animation.frameSize.y, _animation.frameSize.x, _animation.frameSize.y );
	_sprite.setTextureRect(rect);
}

void UpdateAnimationLeftToRightMultipleLines(Animation& _animation,sf::Sprite& _sprite, float _speed, bool _isPlaying, bool _isLooping, float _dt)
{
	if (!_animation.isAssigned)
	{
		_animation.currentFrame = 0;
		_animation.isPlaying = _isPlaying;
		_animation.isLooping = _isLooping;
		_animation.isAssigned = true;
	}

	if (_animation.isPlaying)
	{
		_animation.timer += _dt;
		if (_animation.timer > 1 / _speed)
		{
			_animation.currentFrame++;
			_animation.timer = 0;
		}
		if (_animation.currentFrame > _animation.maxFrame)
		{
			if (_animation.isLooping)
			{
				_animation.currentFrame = 0;
				if (_animation.linePlaying < _animation.maxLine)
				{
					_animation.linePlaying++;
				}
				else
				{
					_animation.linePlaying = 0;
				}
			}
			else
			{
				_animation.currentFrame = 0;
				if (_animation.linePlaying < _animation.maxLine)
				{
					_animation.linePlaying++;
				}
				else
				{
					_animation.isPlaying = false;
					_animation.currentFrame = _animation.maxFrame;
					_animation.timer = 0;
				}
			}
		}
	}
	_animation.rect.left = _animation.currentFrame * _animation.rect.width;
	_animation.rect.top = _animation.linePlaying * _animation.rect.height;
	_sprite.setTextureRect(_animation.rect);
}

void UpdateAnimationIsEntitySelected(Animation& _animation, bool _isSelected, sf::Sprite& _sprite)
{
	
	if (_isSelected)
	{
		_animation.currentFrame = 1;
	}
	else
	{
		_animation.currentFrame = 0;
	}
	
	//_animation->rect.left = _animation->currentFrame * _animation->rect.width;
	sf::IntRect rect(_animation.currentFrame * _animation.rect.width, 0, _animation.frameSize.x, _animation.frameSize.y);
	_sprite.setTextureRect(rect);
}

void UpdateAnimationButton(Animation& _animation, sf::Sprite& _sprite, bool& _isSelected, bool& _isPressed, float _dt)
{
	if (_isSelected || _isPressed)
	{
		if (_isSelected)
		{
			_animation.currentFrame = 1;
		}

		if (_isPressed)
		{
			_isSelected = false;
			_animation.currentFrame = 2;
			_animation.timer += _dt;
			if (_animation.timer >= _animation.resetAnimTime)
			{
				_animation.timer = 0.f;
				_animation.currentFrame = 0;
				_isPressed = false;
			}
		}
	}
	else
	{
		_animation.currentFrame = 0;
	}

	sf::IntRect rect(_animation.currentFrame * _animation.rect.width, 0, _animation.frameSize.x, _animation.frameSize.y);
	_sprite.setTextureRect(rect);
}

void UpdateAnimationButtonAvailable(Animation& _animation, sf::Sprite& _sprite, bool& _isAvailable, bool& _isSelected, bool& _isPressed, float _dt)
{
	if (_isAvailable || _isSelected || _isPressed)
	{
		if (_isAvailable && !_isSelected && !_isPressed)
		{
			_animation.currentFrame = 1;
		}
		if (_isAvailable && _isSelected && !_isPressed)
		{
			_animation.currentFrame = 2;
		}

		if (_isAvailable && _isPressed)
		{
			_animation.currentFrame = 3;
			_animation.timer += _dt;
			if (_animation.timer >= _animation.resetAnimTime)
			{
				_animation.timer = 0.f;
				_animation.currentFrame = 0;
				_isPressed = false;
			}
		}
	}
	else
	{
		_animation.currentFrame = 0;
	}

	sf::IntRect rect(_animation.currentFrame * _animation.rect.width, 0, _animation.frameSize.x, _animation.frameSize.y);
	_sprite.setTextureRect(rect);
}

void ResetAnimRect(sf::Sprite& _sprite, int _spriteWidth, int _spriteHeight)
{
	sf::IntRect rect ( 0, 0, _spriteWidth, _spriteHeight );
	_sprite.setTextureRect(rect);
}