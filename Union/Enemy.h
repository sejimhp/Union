#pragma once
#include <Siv3D.hpp>

#include "Actor.h"
#include "Charactor.h"

class Game;

class Enemy : public Charactor{
public:
	Enemy(Vec2 pos, int ffig);
	void update(Game* game)override;
	void draw(Game* game)override;

	void bulletUpdate(Game* game);
private:
	int damageCount;
};