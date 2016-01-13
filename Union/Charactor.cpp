#include "Charactor.h"

void Charactor::update(Game* game){
}

void Charactor::draw(Game* game){
}

Charactor::Charactor(Vec2 pos, int sstate, int ffig) :
pos(pos), rad(0),
frameCount(0), catchCount(0)
{
	switch (sstate){
	case 1:
		state = State::NORMAL;
		break;
	case 2:
		state = State::CATCHED;
		break;
	};
	switch (ffig){
	case 1:
		fig = Figure::TRIANGLE;
		break;
	case 2:
		fig = Figure::SQUARE;
		break;
	case 3:
		fig = Figure::TSQUARE;
		break;
	case 4:
		fig = Figure::CIRCLE;
		break;
	};
	switch (fig){
	case Figure::TRIANGLE:
		hp = 100;
		size = 25.0;
		break;
	case Figure::SQUARE:
		hp = 10;
		size = 15.0;
		break;
	case Figure::TSQUARE:
		hp = 10;
		size = 15.0;
		break;
	case Figure::CIRCLE:
		hp = 10;
		size = 15.0;
		break;
	}
}