#pragma once
#include <Siv3D.hpp>

#include "Actor.h"

class Game;

class Enemy : public Actor{
public:
	using Super = Enemy;
	Enemy(Vec2 pos);
	void update(Game* game)override;

	Vec2 getPos() const{ return pos; }
protected:
	Vec2 pos;
	double rad, size;
	int hp;
	int frameCount, damageCount, fireCount;
};

//Circle
class CEnemy : public Enemy{
public:
	CEnemy(Vec2 pos);
	void update(Game* game)override;
	void draw(Game* game)override;
private:
};

//Square
class SEnemy : public Enemy{
public:
	SEnemy(Vec2 pos);
	void update(Game* game)override;
	void draw(Game* game)override;
private:
};
