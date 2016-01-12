#pragma once
#include <Siv3D.hpp>
#include <deque>
#include "Actor.h"

class Game;

class Shot : public Actor{
public:
	Shot(Vec2 pos, double rad);
	void update(Game* game) override;
	void draw(Game* game) override;

	Vec2 getPos() const { return pos; }
	double getSize() const{ return size; }
	int getStrong() const { return strong; }
private:
	Vec2 pos, vec;
	double rad, size;

	int strong;
};

using ShotManager = ActorManager < Shot > ;

class Player{
public:
	enum class State{
		NORMAL,
		CATCHER,
		GAMEOVER,
	};

	Player(double size);
	void init();
	void update(Game* game);
	void draw(Game* game);

	Vec2 getPos() const { return pos; }
	double getSize() const{ return size; }
	int getHp() const { return hp; }
	bool boolCatcherState() const { 
		if(state == State::CATCHER) return true; 
		else return false;
	}
	void checkBulletHit(Game* game);
	std::shared_ptr<ShotManager> getShotManager() const { return shotManager; }
private:
	State state;
	Vec2 pos;
	double size;
	unsigned int frameCount,fireCount;
	int hp;
	std::shared_ptr<ShotManager> shotManager;
};