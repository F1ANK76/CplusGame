#pragma once

#include <SFML/Graphics.hpp>
#include "actor.h"

class Game;

class Player : public Actor
{
public:
	Player(Game* game, ActorType type, sf::Vector2f pos, float size, float speed);
	virtual ~Player();

	virtual void Update(float dt) override; // 플레이어의 동작

private:
	void ProcessInput(float dt); // 키보드 입력 처리
};
