#include "enemycopy.h"
#include "player.h"
#include "game.h"

EnemyCopy::EnemyCopy(Game* game, ActorType type, const sf::Vector2f pos, float size, float speed)
	:Actor{game, type, pos, speed, size }
{
	shape.setTexture(game->GetShipTexture());
	shape.setTextureRect(sf::IntRect{ 32,0,8,8 }); // {x,y,width,height}

	shape.setScale(sf::Vector2f{ size,size });
}

EnemyCopy::~EnemyCopy()
{
}

void EnemyCopy::Update(float dt)
{
	if (isActive)
	{
		UpdatePosition(dt);
		shape.setPosition(position);
	}
}

void EnemyCopy::UpdatePosition(float dt)
{
	sf::Vector2f enemyToPlayer = game->GetPlayer()->GetPosition() - position;

	float length = sqrt(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.y * enemyToPlayer.y);

	enemyToPlayer /= length;

	position += enemyToPlayer * speed * dt;
}
