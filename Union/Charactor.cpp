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

Charactor::Charactor(Vec2 pos, Figure fig) :
pos(pos), rad(0), fig(fig){
	switch (fig){
	case Figure::SQUARE:
		hp = 30;
		size = 30.0;
		color = Color(Palette::Yellow, 222);
		break;
	case Figure::TSQUARE:
		hp = 30;
		size = 15.0;
		color = Color(Palette::Purple, 222);
		break;
	case Figure::CIRCLE:
		hp = 30;
		size = 15.0;
		color = Color(Palette::Lightgreen, 222);
		break;
	};
}

Charactor::Charactor(Vec2 pos, int ffig) :
pos(pos), rad(0),
frameCount(0), catchCount(0)
{
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
	//Šeƒ‚ƒfƒ‹
	switch (fig){
	case Figure::TRIANGLE:
		hp = 200;
		size = 25.0;
		color = Color(150, 150, 255, 122);
		break;
	case Figure::SQUARE:
		hp = 10;
		size = 30.0;
		color = Color(Palette::Yellow, 222);
		break;
	case Figure::TSQUARE:
		hp = 10;
		size = 15.0;
		color = Color(Palette::Purple, 222);
		break;
	case Figure::CIRCLE:
		hp = 10;
		size = 15.0;
		color = Color(Palette::Lightgreen, 222);
		break;
	}
}