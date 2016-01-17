#pragma once
#include <Siv3D.hpp>
#include "Actor.h"

class Game;

class Bullet : public Actor{
public:
	enum BulletKind{
		CIRCLE,
		HANABI,
		TRIANGLE,
		SQUARE,
	};
	Bullet(Vec2 pos, Color color, double rad, double speed, double accel);
	Bullet(Vec2 pos, Color color, double rad);
	void update(Game* game) override;
	void draw(Game* game) override;

	Vec2 getPos() const { return pos; }
	double getSize() const{ return size; }
private:
	BulletKind type;
	Vec2 pos;
	Color color;
	double size, rad, speed, accel;
	int frameCount;
};