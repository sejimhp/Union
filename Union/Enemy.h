#pragma once
#include <Siv3D.hpp>

#include "Actor.h"

class Game;

class Enemy : public Actor{
public:
	enum class State{
		NORMAL,
		CATCHED,
	};
	using Super = Enemy;
	Enemy(Vec2 pos);
	void update(Game* game)override;

	Vec2 getPos() const{ return pos; }
protected:
	State state;
	Vec2 pos;
	double rad, size;
	int hp;
	int frameCount, damageCount, fireCount, catchCount;
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

//Turn Square
class STEnemy : public Enemy{
public:
	STEnemy(Vec2 pos);
	void update(Game* game)override;
	void draw(Game* game)override;
private:
};
