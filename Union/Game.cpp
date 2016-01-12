#include "Game.h"

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

const Size Game::stageSize = Size(1366, 768);

Game::Game(){
	state = State::TITLE;
	player = std::make_shared<Player>();
	enemyManager = std::make_shared<EnemyManager>();
	bulletManager = std::make_shared<BulletManager>();

	FontAsset::Register(L"log", 10, L"Orbitron");
	FontAsset::Register(L"title", 50, L"Orbitron");
	TextureAsset::Register(L"back", L"dat/cloud.jpg");

	frameCount = 3000;
	player->init();
}

void Game::update(){
	frameCount = ++frameCount % 4096;

	switch (state){
	case State::TITLE:
		if (Input::KeySpace.clicked) gameStart();
		enemyManager->update(this);
		bulletManager->update(this);
		break;
	case State::PLAY:
		player->update(this);
		enemyManager->update(this);
		bulletManager->update(this);
		break;
	case State::GAMEOVER:
		break;
	};

	creatActors();
}

void Game::draw(){
	drawBack();

	switch (state){
	case State::TITLE:
		enemyManager->draw(this);
		bulletManager->draw(this);
		FontAsset(L"title").draw(L"Union", Vec2(200, 300), Palette::Black);
		break;
	case State::PLAY:
		player->draw(this);
		enemyManager->draw(this);
		bulletManager->draw(this);
		break;
	case State::GAMEOVER:
		enemyManager->draw(this);
		bulletManager->draw(this);
		FontAsset(L"title").draw(L"GameOver", Vec2(200, 300), Palette::Lightgreen);
		break;
	};
}

void Game::creatActors(){
	if (System::FrameCount() % 100 == 0){
		auto Cpos = RandomVec2(stageSize.x, 0);
		auto Cenemy = std::make_shared<CEnemy>(Cpos);
		auto Spos = RandomVec2(stageSize.x, 0);
		auto Senemy = std::make_shared<SEnemy>(Spos);
		switch (Random(1, 2)){
		case 1:
			enemyManager->add(Cenemy);
			break;
		case 2:
			enemyManager->add(Senemy);
			break;
		};
	}
}

void Game::drawBack(){
	//TextureAsset(L"back").draw(0, frameCount / 2.0, Alpha(180));
	//TextureAsset(L"back").flip().draw(0, frameCount / 2.0 - 2048, Alpha(180));
	FontAsset(L"log").draw(Format(frameCount), Vec2(0, 0), Palette::Lightgreen);
	FontAsset(L"log").draw(Format(player->getHp()), Vec2(0, 20), Palette::Lightgreen);
	//TextureAsset(L"back").mirror().flip().draw(0, frameCount, Alpha(100));
	//TextureAsset(L"back").mirror().draw(0, frameCount - 2048, Alpha(100));
}

void Game::gameStart(){
	state = State::PLAY;
	player->init();
	bulletManager->clear();
	enemyManager->clear();
}