#pragma once

#include <SFML/Graphics.hpp>
#include "actor.h"

class Game; // Game Ŭ������ ���

class Bullet : public Actor
{
public:
	Bullet(Game* game, ActorType type, float size, float speed);
	virtual ~Bullet();

	virtual void Update(float dt) override;

private:
	void UpdatePosition(float dt);
	sf::Vector2f GetCloseEnemyDirection();

private:
	sf::Vector2f direction;
};

