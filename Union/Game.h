#pragma once
#include <Siv3D.hpp>
#include "Actor.h"

class Player;
class Enemy;
class Bullet;

using BulletManager = ActorManager<Bullet>;
using EnemyManager = ActorManager<Enemy>;

class Game{
public:
	enum class State{
		TITLE,
		PLAY,
		GAMEOVER,
	};
	Game();
	void update();
	void draw();

	std::shared_ptr<Player> getPlayer()const{ return player; }
	std::shared_ptr<BulletManager> getBulletManager()const{ return bulletManager; }
	std::shared_ptr<EnemyManager> getEnemyManager()const{ return enemyManager; }

	void drawBack();
	void gameStart();
	void creatActors();
	static const Size stageSize;
private:
	std::shared_ptr<Player> player;
	std::shared_ptr<BulletManager> bulletManager;
	std::shared_ptr<EnemyManager> enemyManager;

	State state;
	int frameCount;
};