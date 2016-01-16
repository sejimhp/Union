#pragma once
#include <Siv3D.hpp>
#include "Actor.h"

class Game;

class Charactor : public Actor{
public:
	enum class Figure{
		TRIANGLE,
		SQUARE,
		TSQUARE,
		CIRCLE,
	};
	using Super = Charactor;

	Charactor(Vec2 pos,int ffig);
	Charactor(Vec2 pos,Figure ffig);
	void update(Game* game)override;
	void drawChar();

	//return
	int getHp() const { return hp; }
	double getSize() const{ return size; }
	Vec2 getPos() const{ return pos; }
	Figure getFigre() const{ return fig; }
protected:
	Color color;
	Figure fig;
	Vec2 pos;
	double rad, size;
	int hp;
	int frameCount, catchCount;
};