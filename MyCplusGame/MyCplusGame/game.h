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
	bool Initialize(); // 게임 객체 생성 + @
	void RunLoop(); // 게임 루프
	void Shutdown(); // 프로그램 종료

	Player* GetPlayer() { return player; }
	std::vector<Actor*> GetActors() const { return actors; }

	//std::vector<EnemyCopy*> GetEnemies() const { return enemies; }
	//std::vector<Bullet*> GetBullets() const { return bullets; }

	// 참조자로 반환해야 함
	sf::Texture& GetShipTexture() { return shipsText; }
	sf::Texture& GetProjectileTexture() { return projectileText; }

private:
	void InitializeGame(); // 게임 객체 생성
	void ProcessInput(); // 게임 종료 탐지
	void UpdateGame(); // 게임 로직 업데이트
	void DrawGame(); // 게임 요소들을 그리는 부분
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

	// 게임 데이터
	Player* player;
	//std::vector<EnemyCopy*> enemies;
	std::vector<Actor*> actors;

	/*Player* player;
	std::vector<EnemyCopy*> enemies;
	std::vector<Bullet*> bullets;*/
};
