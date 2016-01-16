#include "Charactor.h"

void Charactor::update(Game* game){
}

void Charactor::drawChar(){
	switch (fig){
	case Figure::TRIANGLE:
		Triangle(pos, size).draw(color).drawFrame();
		break;
	case Figure::CIRCLE:
		Circle(pos, size).draw(color).drawFrame();
		break;
	case Figure::SQUARE:
		RectF(size * 2).setCenter(pos).draw(color).drawFrame();
		break;
	case Figure::TSQUARE:
		RectF(size * 2).setCenter(pos).rotated(rad * 10).draw(color).drawFrame();
		break;
	};
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
	//�e���f��
	switch (fig){
	case Figure::TRIANGLE:
		hp = 100;
		size = 25.0;
		color = Color(150, 150, 255, 122);
		break;
	case Figure::SQUARE:
		hp = 10;
		size = 15.0;
		color = Color(Palette::Yellow, 122);
		break;
	case Figure::TSQUARE:
		hp = 10;
		size = 15.0;
		color = Color(Palette::Rosybrown, 122);
		break;
	case Figure::CIRCLE:
		hp = 10;
		size = 15.0;
		color = Color(Palette::Goldenrod, 122);
		break;
	}
}