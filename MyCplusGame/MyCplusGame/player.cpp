#include "player.h"
#include "game.h"

Player::Player(Game* game, ActorType type, sf::Vector2f pos, float size, float speed)
	:Actor{game, type, pos, speed, size}
{
	shape.setTexture(game->GetShipTexture());
	shape.setTextureRect(sf::IntRect{ 32,64,16,16 }); // {x,y,width,height}

	shape.setScale(sf::Vector2f{ size,size });
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	ProcessInput(dt);
	shape.setPosition(position);
}

void Player::ProcessInput(float dt) // 입력 처리
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		position.x += speed * dt;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) position.x -= speed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) position.y -= speed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) position.y += speed * dt;
}
