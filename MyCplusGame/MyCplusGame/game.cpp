#include "game.h"
#include "player.h"
#include "enemycopy.h"
#include "bullet.h"

Game::Game()
{
	actors.clear();
}

bool Game::Initialize()
{
	// Initialize Resource
	if (!shipsText.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png"))
	{
		return false;
	}

	if (!projectileText.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Projectiles.png"))
	{
		return false;
	}

	if (!background.loadFromFile("../resources/sprites/SpaceShooterAssetPack_BackGrounds.png"))
	{
		return false;
	}

	InitializeGame();
	return true;
}

void Game::RunLoop()
{
	while (window.isOpen())
	{
		ProcessInput();
		UpdateGame();
		DrawGame();
	}
}

void Game::Shutdown()
{
	for (int i = 0; i < actors.size(); i++)
	{
		delete actors[i];
	}
}

void Game::InitializeGame()
{
	// Player
	Player* player = new Player { this, ActorType::PLAYER, sf::Vector2f{float(screenWidth / 2),float(screenHeight / 2)}, 3, 100 };
	actors.push_back(player);
	this->player = player;

	// Bullet
	bulletFirePeriod = 1;
	bulletFireTimer = bulletFirePeriod;
}

void Game::ProcessInput()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::UpdateGame()
{
	float dt = deltaClock.restart().asSeconds();

	enemySpawnTime -= dt;

	if (enemySpawnTime < 0)
	{
		float enemyX = rand() % screenWidth;
		float enemyY = rand() % screenHeight;
		sf::Vector2f enemyPos{ enemyX ,enemyY };

		// this = �� ��� �Լ��� ȣ���� ��ü�� �ּ�
		EnemyCopy* e = new EnemyCopy{ this, ActorType::ENEMY, enemyPos, 3, 80 };
		actors.push_back(e);
		//enemies.push_back(e);

		enemySpawnTime = 0.75;
	}

	SpawnBullet(dt);

	// �÷��̾� �̵� ����
	// player->Update(dt); // ������ �������� ���ϴ� �Լ� ȣ���

	for (int i = 0; i < actors.size(); i++)
	{
		actors[i]->Update(dt); // ���� ���ε��� Ÿ���� ���� ȣ�� �Լ� ����, ���� ���ε����� �ٲ�� ��ü�� ���� �׿� ���� �Լ��� ���� (virtual, override ���)
	}

	CheckCrash();

	if (isGameOver)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			ClearData();
			Initialize();
			RunLoop();
			Shutdown();
		}
	}
}

void Game::DrawGame()
{
	backpicture.setTexture(background);
	backpicture.setTextureRect(sf::IntRect{ 0,0,128,256 });
	backpicture.setScale(sf::Vector2f{ 7,7 });

	sf::Font font;
	if (!font.loadFromFile("../resources/font/arial.ttf"))
	{
		printf("ERROR");
	}

	sf::Text text;

	window.clear();

	window.draw(backpicture);

	if (isGameOver)
	{
		text.setFont(font);
		text.setPosition(20, 20);
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::White);
		text.setString("Game Over. Press R to Retry");

		window.draw(text);
	}
	else
	{
		text.setFont(font);
		text.setCharacterSize(24);
		text.setFillColor(sf::Color::White);
		text.setString("Score : " + std::to_string(killEnemy));

		window.draw(text);

		for (int i = 0; i < actors.size(); i++)
		{
			//printf("%d \n", actors.size());
			actors[i]->Draw(window);
		}
	}

	window.display();
}

void Game::SpawnBullet(float dt)
{
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		bulletFireTimer -= dt;
		// 1�ʸ��� �Ѿ� ����
		if (bulletFireTimer < 0)
		{
			Actor* b = new Bullet{ this, ActorType::BULLET, 3, 500 };
			actors.push_back(b);

			bulletFireTimer = bulletFirePeriod;
		}
	}
}

void Game::CheckCrash()
{
	for (int i = 0; i < actors.size(); i++)
	{
		for (int j = 0; j < actors.size(); j++)
		{
			if (actors[i]->GetActorType() == ActorType::PLAYER && actors[j]->GetActorType() == ActorType::ENEMY)
			{
				sf::Vector2f PlayerPos = actors[i]->GetPosition();
				sf::Vector2f enemyPos = actors[j]->GetPosition();

				sf::Vector2f bulletToEnemyPos = PlayerPos - enemyPos;
				float dist = sqrt(bulletToEnemyPos.x * bulletToEnemyPos.x + bulletToEnemyPos.y * bulletToEnemyPos.y);

				if (dist < 5)
				{
					isGameOver = true;

					break;
				}
			}

			// true�� �����ϴ� �ֵ鸸 ����
			if (actors[i]->GetIsActive() || actors[j]->GetIsActive())
			{
				if (actors[i]->GetActorType() == ActorType::BULLET && actors[j]->GetActorType() == ActorType::ENEMY)
				{
					sf::Vector2f bulletPos = actors[i]->GetPosition();
					sf::Vector2f enemyPos = actors[j]->GetPosition();

					sf::Vector2f bulletToEnemyPos = bulletPos - enemyPos;
					float dist = sqrt(bulletToEnemyPos.x * bulletToEnemyPos.x + bulletToEnemyPos.y * bulletToEnemyPos.y);

					if (dist < 5)
					{
						actors[i]->SetIsActive(false);
						actors[j]->SetIsActive(false);

						killEnemy += 1;

						break;
					}
				}
			}
		}
	}
}

void Game::ClearData()
{
	killEnemy = 0;
	isGameOver = false;

	// ��� ���� ��ü ������ �ʱ�ȭ
	actors.clear();
}
