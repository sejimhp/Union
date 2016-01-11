#pragma once
#include <Siv3D.hpp>
#include "Actor.h"

class Player;

class Game{
public:
	Game();
	void update();
	void draw();

	void drawBack();
	static const Size stageSize;
private:
	std::shared_ptr<Player> player;

	int frameCount;
};