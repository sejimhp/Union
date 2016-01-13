#pragma once
#include <Siv3D.hpp>
#include <deque>
#include "Actor.h"

#include "Charactor.h"

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

using ShotManager = ActorManager < Shot >;

class Player : public Charactor{
public:
	Player(Vec2 pos, int sstate, int ffig);
	void init();
	void update(Game* game);
	void draw(Game* game);

	State getState() const { return state; }
	void checkBulletHit(Game* game);
	std::shared_ptr<ShotManager> getShotManager() const { return shotManager; }
private:
	std::shared_ptr<ShotManager> shotManager;
};