#pragma once
#include <Siv3D.hpp>
#include "Actor.h"

class Game;

class Charactor : public Actor{
public:
	enum class State{
		NORMAL,
		CATCHED,
		CATCHER,
		GAMEOVER,
	};
	enum class Figure{
		TRIANGLE,
		SQUARE,
		TSQUARE,
		CIRCLE,
	};
	using Super = Charactor;

	Charactor(Vec2 pos, int sstate, int ffig);
	void update(Game* game)override;
	void drawChar();

	//return
	int getHp() const { return hp; }
	double getSize() const{ return size; }
	Vec2 getPos() const{ return pos; }
	State getState() const{ return state; }
	Figure getFigre() const{ return fig; }
protected:
	Color color;
	State state;
	Figure fig;
	Vec2 pos;
	double rad, size;
	int hp;
	int frameCount, catchCount;
};