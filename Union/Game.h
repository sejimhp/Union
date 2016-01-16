#pragma once
#include <Siv3D.hpp>
#include "Actor.h"

class Player;
class Enemy;
class Bullet;
class MemberManager;

using BulletManager = ActorManager<Bullet>;
using EnemyManager = ActorManager<Enemy>;
using PlayerManager = MemberManager;

class Game{
public:
	enum class State{
		TITLE,
		PLAY,
		GAMEOVER,
	};
	Game();
	void init();
	void update();
	void draw();

	std::shared_ptr<PlayerManager> getPlayerManager()const{ return playerManager; }
	std::shared_ptr<BulletManager> getBulletManager()const{ return bulletManager; }
	std::shared_ptr<BulletManager> getMyBulletManager()const{ return myBulletManager; }
	std::shared_ptr<EnemyManager> getEnemyManager()const{ return enemyManager; }

	void drawBack();
	void gameStart();
	void creatActors();
	static const Size stageSize;
private:
	std::shared_ptr<PlayerManager> playerManager;
	std::shared_ptr<BulletManager> myBulletManager;
	std::shared_ptr<BulletManager> bulletManager;
	std::shared_ptr<EnemyManager> enemyManager;

	State state;
};