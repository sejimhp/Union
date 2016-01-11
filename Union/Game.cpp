#include "Game.h"

#include "Player.h"

const Size Game::stageSize = Size(1366, 768);

Game::Game(){
	player = std::make_shared<Player>();

	FontAsset::Register(L"log", 10, L"Orbitron");
	TextureAsset::Register(L"back", L"dat/cloud.jpg");

	frameCount = 3000;
	player->init();
}

void Game::update(){
	frameCount = ++frameCount % 4096;
	
	player->update(this);
}

void Game::draw(){
	drawBack();

	player->draw(this);
}

void Game::drawBack(){
	TextureAsset(L"back").draw(0, frameCount / 2.0, Alpha(180));
	TextureAsset(L"back").flip().draw(0, frameCount / 2.0 - 2048, Alpha(180));
	FontAsset(L"log").draw(Format(frameCount), Vec2(0, 0), Palette::Lightgreen);
	//TextureAsset(L"back").mirror().flip().draw(0, frameCount, Alpha(100));
	//TextureAsset(L"back").mirror().draw(0, frameCount - 2048, Alpha(100));
}