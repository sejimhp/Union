#include "Game.h"

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

const Size Game::stageSize = Size(1366, 768);

Game::Game(){
	state = State::TITLE;
	playerManager = std::make_shared<PlayerManager>();
	enemyManager = std::make_shared<EnemyManager>();
	myBulletManager = std::make_shared<BulletManager>();
	bulletManager = std::make_shared<BulletManager>();

	FontAsset::Register(L"log", 10, L"Orbitron");
	FontAsset::Register(L"title", 50, L"Orbitron");
	TextureAsset::Register(L"back", L"dat/cloud.jpg");
	init();
}


void Game::update(){
	switch (state){
	case State::TITLE:
		if (Input::KeySpace.clicked) gameStart();
		creatActors();
		enemyManager->update(this);
		bulletManager->update(this);
		break;
	case State::PLAY:
		creatActors();
		playerManager->update(this);
		enemyManager->update(this);
		bulletManager->update(this);
		myBulletManager->update(this);
		//if (playerManager->getHp() <= 0){ state = State::GAMEOVER; }
		break;
	case State::GAMEOVER:
		if (Input::KeySpace.clicked){
			state = State::TITLE;
			init();
		}
		break;
	};
}

void Game::draw(){
	drawBack();

	switch (state){
	case State::TITLE:
		bulletManager->draw(this);
		enemyManager->draw(this);
		FontAsset(L"title").draw(L"Union", Vec2(200, 300), Palette::Black);
		break;
	case State::PLAY:
		playerManager->draw(this);
		myBulletManager->draw(this);
		bulletManager->draw(this);
		enemyManager->draw(this);
		break;
	case State::GAMEOVER:
		bulletManager->draw(this);
		myBulletManager->draw(this);
		enemyManager->draw(this);
		FontAsset(L"title").draw(L"GameOver", Vec2(200, 300), Palette::Lightgreen);
		break;
	};
}

void Game::creatActors(){
	if (System::FrameCount() % 100 == 0){
		auto pos = RandomVec2(stageSize.x, 0);

		auto Cenemy = std::make_shared<Enemy>(pos, 1, 4);
		auto Senemy = std::make_shared<Enemy>(pos, 1, 2);
		auto STenemy = std::make_shared<Enemy>(pos, 1, 3);
		switch (Random(1, 3)){
		case 1:
			enemyManager->add(Cenemy);
			break;
		case 2:
			enemyManager->add(Senemy);
			break;
		case 3:
			enemyManager->add(STenemy);
			break;
		};
	}
}

void Game::drawBack(){
	//TextureAsset(L"back").draw(0, frameCount / 2.0, Alpha(180));
	//TextureAsset(L"back").flip().draw(0, frameCount / 2.0 - 2048, Alpha(180));
	FontAsset(L"log").draw(Format(System::FrameCount()), Vec2(0, 0), Palette::Lightgreen);
	//FontAsset(L"log").draw(Format(player->getHp()), Vec2(0, 20), Palette::Lightgreen);
	//TextureAsset(L"back").mirror().flip().draw(0, frameCount, Alpha(100));
	//TextureAsset(L"back").mirror().draw(0, frameCount - 2048, Alpha(100));
}

void Game::gameStart(){
	state = State::PLAY;
	init();
	//main‚ÌŽ©‹@
	playerManager->add(std::make_shared<Player>(1, 2));
	playerManager->add(std::make_shared<Player>(1, 3));
	playerManager->add(std::make_shared<Player>(1, 4));
	playerManager->add(std::make_shared<Player>(1, 1));
}

void Game::init(){
	playerManager->clear();
	enemyManager->clear();
	bulletManager->clear();
	myBulletManager->clear();
	playerManager->addMain(std::make_shared<Player>(Vec2(300, 700), 1, 1));
}