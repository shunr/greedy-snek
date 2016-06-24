#include "stdafx.h"
#include "Player.h"
#include <iostream>

Player::Player() : Player(0, 0){}

Player::Player(int x, int y) {
	_id = Globals::uniqueId();
	// Initialize 1-size snake
	_length = 1;
	if (Globals::withinBounds(x, y)) {
		_headPos[0] = 0;
		_headPos[1] = 0;
	} else {
		_headPos[0] = x;
		_headPos[1] = y;
	};
	_body.push_back(_headPos);
}

int Player::getLength() {
	return _length;
}

std::array<int, 2> Player::getHeadPos() {
	return _headPos;
}

int Player::getId() {
	return _id;
}

std::array<int,2> Player::getSegment(int i) {
	if (i < _length) {
		return _body[i];
	}
}

void Player::setLength(int l) {
	_length = l;
}

void Player::addLength(int l) {
	_length += l;
	for (int i = 0; i < G_FOODVALUE; i++) {
		_body.insert(_body.begin(), *_body.begin());
	}
}

void Player::move(Direction dir) {
	if (!_isDead) {
		switch (dir) {
		case Direction::UP:
			_headPos[1] -= 1;
			break;
		case Direction::DOWN:
			_headPos[1] += 1;
			break;
		case Direction::LEFT:
			_headPos[0] -= 1;
			break;
		case Direction::RIGHT:
			_headPos[0] += 1;
			break;
		}
		// Move body segments forward and pop last element of the tail unless food has been eaten
		_body.push_back(_headPos);
		if (_body.size() > _length) {
			_body.erase(_body.begin());
		}
	}
}

void Player::death() {
	// KAPPA
	//_length = 0;
	_isDead = true;
	_id = 256*256*8+256*8+8;
}

Player::~Player()
{
}
