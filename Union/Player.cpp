#include "Player.h"

#include "Game.h"
#include "Charactor.h"
#include "Bullet.h"

namespace{
	static const int HP_MAX = 100;
}

Player::Player(Vec2 pos, int sstate, int ffig) : Super(pos, sstate, ffig){}

void Player::init(){
	pos = Vec2(500, 700);
	state = State::NORMAL;
	hp = HP_MAX;
}

void Player::update(Game* game){
	if (Input::KeyUp.pressed && pos.y >= 0) pos.y -= 5;
	if (Input::KeyDown.pressed && pos.y < Game::stageSize.y)	pos.y += 5;
	if (Input::KeyRight.pressed && pos.x < Game::stageSize.x)	pos.x += 5;
	if (Input::KeyLeft.pressed && pos.x >= 0) pos.x -= 5;

	//fire
	auto bulletManager = game->getMyBulletManager();
	for (int i : {-1, 1, 0}) {
		const double shotRad = Radians(5 * i);
		if (System::FrameCount() % 10 == 0) {
			auto shot = std::make_shared<Bullet>(pos, Palette::Aqua, shotRad - HalfPi, 1, 1);
			bulletManager->add(shot);
		}
	}

	//catcher
	if (Input::KeyZ.clicked){
		frameCount = System::FrameCount();
		state = State::CATCHER;
	}
	else if (state == State::CATCHER && (System::FrameCount() - frameCount) > 100){
		state = State::NORMAL;
	}

	checkBulletHit(game);
}

void Player::draw(Game* game){
	if (state == State::CATCHER){
		Circle(pos, 120).draw(Color(100, 100, 0, 100));
		Circle(pos, 120).drawArc(0.0, TwoPi * (static_cast<double>(System::FrameCount() - frameCount) / 100), 0.0, 2.0, Color(255, 150, 150, 122));
	}
	Triangle(pos, size).draw(Color(150, 150, 255, 122)).drawFrame();
	Circle(pos, 2).draw(Color(150, 0, 0, 122));
	Circle(pos, 25.0).drawArc(0.0, TwoPi * (static_cast<double>(hp) / HP_MAX), 0.0, 2.0, Color(255, 150, 150, 122));
}

void Player::checkBulletHit(Game* game){
	auto bulletManager = game->getBulletManager();
	for (auto& bullet : *bulletManager){
		if (Circle(pos, 2).intersects(Circle(bullet->getPos(), bullet->getSize()))){
			hp--;
			bullet->kill();
		}
	}
	if (hp <= 0){
		state = State::GAMEOVER;
	}
}

MemberManager::MemberManager(){
	actors.resize(5, nullptr);
}

void MemberManager::add(std::shared_ptr<Player> actor){
	if (actors[1] == nullptr)
		actors[1] = actor;
	else if (actors[3] == nullptr)
		actors[3] = actor;
	else if (actors[0] == nullptr)
		actors[0] = actor;
	else if (actors[4] == nullptr)
		actors[4] = actor;
}