#ifndef ANIMATION_H

#define ANIMATION_H
#include"Common.h"



void CreateAnimationLeftToRight(Animation& _animation, int _totalFrameX, int _totalFrameY, sf::Vector2u _size);
void CreateAnimationUpToDown(Animation& _animation, int _totalFrameX, int _totalFrameY, sf::Vector2u _size);
void CreateAnimationUpToDownToUp(Animation& _animation, int _totalFrameX, int _totalFrameY, sf::Vector2u _size);
void CreateAnimationLeftToRightMultipleLines(Animation& _animation, int _totalFrameX, int _totalFrameY, int _totalLines, sf::Vector2u _size);
void UpdateAnimationUpToDown(Animation& _animation,sf::Sprite& _sprite, float _speed, int _location, bool _isMoving, float _dt);
void UpdateAnimationUpToDownToUp(Animation& _animation,sf::Sprite& _sprite, float _speed, int _location, bool _isMoving, float _dt);
void UpdateAnimationLeftToRightMultipleLines(Animation& _animation,sf::Sprite& _sprite, float _speed, bool _isPlaying, bool _isLooping, float _dt);
void UpdateAnimationIsEntitySelected(Animation& _animation, bool _isSelected, sf::Sprite& _sprite);
void UpdateAnimationButton(Animation& _animation, sf::Sprite& _sprite, bool& _isSelected, bool& _isPressed, float _dt);
void UpdateAnimationButtonAvailable(Animation& _animation, sf::Sprite& _sprite, bool& _isAvailable, bool& _isSelected, bool& _isPressed, float _dt);
void UpdateAnimationLeftToRight(Animation& _animation,sf::Sprite& _sprite, float _speed, int _direction, bool _isPlaying, bool _isLooping, float _dt);
void ResetAnimRect(sf::Sprite& _sprite, int _spriteWidth, int _spriteHeight);

#endif
