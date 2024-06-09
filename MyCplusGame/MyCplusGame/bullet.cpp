#include "bullet.h"
#include <iostream>
#include "game.h"
#include "player.h"
#include "enemycopy.h"

#include "windows.h"

Bullet::Bullet(Game* game, ActorType type,  float size, float speed)
	:Actor{game, type, game->GetPlayer()->GetPosition(), speed, size }
{
	direction = GetCloseEnemyDirection();

	shape.setTexture(game->GetProjectileTexture());
	shape.setTextureRect(sf::IntRect{ 0,0,8,8 }); // {x,y,width,height}

	shape.setScale(sf::Vector2f{ size,size });
}

Bullet::~Bullet()
{
}

void Bullet::Update(float dt)
{
	if (isActive)
	{
		UpdatePosition(dt);
		shape.setPosition(position);
	}
}


void Bullet::UpdatePosition(float dt)
{
	position += direction * speed * dt;
}

sf::Vector2f Bullet::GetCloseEnemyDirection() // 가장 가까운 적의 위치값 계산 로직
{
	std::vector<Actor*> actors = game->GetActors();

	int minDist = 0;
	sf::Vector2f minDistVec;

	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i]->GetActorType() == ActorType::ENEMY || actors[i]->GetIsActive() == true)
		{
			sf::Vector2f enemyPos = actors[i]->GetPosition();
			sf::Vector2f bulletToEnemyVec = enemyPos - position;

			float dist = sqrt(bulletToEnemyVec.x * bulletToEnemyVec.x + bulletToEnemyVec.y * bulletToEnemyVec.y);
			if (minDist == 0 || dist < minDist)
			{
				minDist = dist; // 가장 거리가 가까운 적을 찾기 위한 변수
				minDistVec = bulletToEnemyVec / dist;
			}
		}
	}

	return minDistVec;
}
