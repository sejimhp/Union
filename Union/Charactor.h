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
	Charactor(Vec2 pos, int sstate, int ffig);
	void update(Game* game)override;
	void draw(Game* game) override;

	//return
	int getHp() const { return hp; }
	double getSize() const{ return size; }
	Vec2 getPos() const{ return pos; }
	State getState() const{ return state; }
	Figure getFigre() const{ return fig; }
protected:
	State state;
	Figure fig;
	Vec2 pos;
	double rad, size;
	int hp;
	int frameCount, catchCount;
};