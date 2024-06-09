#pragma once

#include <SFML/Graphics.hpp>
#include "actor.h"

class Player;
class Game;

class EnemyCopy : public Actor
{
public:
	EnemyCopy(Game* game, ActorType type, const sf::Vector2f pos, float size,float speed);
	virtual ~EnemyCopy();

	virtual void Update(float dt) override;

private:
	void UpdatePosition(float dt);
};