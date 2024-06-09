#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "actor.h"

class Player;
class EnemyCopy;
class Bullet;

class Game
{
public:
	Game();
	bool Initialize(); // ���� ��ü ���� + @
	void RunLoop(); // ���� ����
	void Shutdown(); // ���α׷� ����

	Player* GetPlayer() { return player; }
	std::vector<Actor*> GetActors() const { return actors; }

	//std::vector<EnemyCopy*> GetEnemies() const { return enemies; }
	//std::vector<Bullet*> GetBullets() const { return bullets; }

	// �����ڷ� ��ȯ�ؾ� ��
	sf::Texture& GetShipTexture() { return shipsText; }
	sf::Texture& GetProjectileTexture() { return projectileText; }

private:
	void InitializeGame(); // ���� ��ü ����
	void ProcessInput(); // ���� ���� Ž��
	void UpdateGame(); // ���� ���� ������Ʈ
	void DrawGame(); // ���� ��ҵ��� �׸��� �κ�
	void SpawnBullet(float dt);
	void CheckCrash();
	void ClearData();
private:
	int screenWidth = 800;
	int screenHeight = 450;
	sf::RenderWindow window{ sf::VideoMode(screenWidth, screenHeight), "SFML works!" };

	float bulletFirePeriod;
	float bulletFireTimer;

	float enemySpawnTime = 0.75;

	int killEnemy = 0;
	bool isGameOver = false;

	sf::Clock deltaClock;

	sf::Texture shipsText;
	sf::Texture projectileText;
	sf::Texture background;

	sf::Sprite backpicture;

	// ���� ������
	Player* player;
	//std::vector<EnemyCopy*> enemies;
	std::vector<Actor*> actors;

	/*Player* player;
	std::vector<EnemyCopy*> enemies;
	std::vector<Bullet*> bullets;*/
};
