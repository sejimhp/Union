#include "Player.h"

#include "Game.h"
#include "Bullet.h"

Shot::Shot(Vec2 pos, double rad) :
pos(pos), rad(rad), size(5.0){}

void Shot::update(Game* game){
	if (pos.x > Game::stageSize.x || pos.x < 0 || pos.y > Game::stageSize.y || pos.y < 0){
		kill();
	}

	const Vec2 vec = Vec2(Cos(rad), Sin(rad)) * 15;
	pos += vec;
}

void Shot::draw(Game* game){
	Triangle({ -5, 5 }, { 0, -15 }, { 5, 5 }).setCentroid(pos).draw(Color(255, 165, 30));
}

namespace{
	static const int HP_MAX = 100;
}

Player::Player() :
state(State::NORMAL),
pos(100.0, 100.0),
hp(0), fireCount(0)
{
	shotManager = std::make_shared<ShotManager>();
}

void Player::init(){
	pos = Vec2(100, 100);
	state = State::NORMAL;
	hp = HP_MAX;
	shotManager->clear();
}

void Player::update(Game* game){
	if (Input::KeyUp.pressed && pos.y >= 0) pos.y -= 5;
	if (Input::KeyDown.pressed && pos.y < Game::stageSize.y)	pos.y += 5;
	if (Input::KeyRight.pressed && pos.x < Game::stageSize.x)	pos.x += 5;
	if (Input::KeyLeft.pressed && pos.x >= 0) pos.x -= 5;

	//fire
	for (int i : {-1, 1, 0}) {
		const double shotRad = Radians(5 * i);
		if (fireCount % 5 == 0) {
			auto shot = std::make_shared<Shot>(pos, shotRad-HalfPi);
			shotManager->add(shot);
		}
	}
	checkBulletHit(game);
	shotManager->update(game);
	fireCount++;
}

void Player::draw(Game* game){
	shotManager->draw(game);
	Triangle(pos, 30.0).draw(Color(150, 150, 255, 122)).drawFrame();
	Circle(pos, 2).draw(Color(150, 0, 0, 122));
}

void Player::checkBulletHit(Game* game){
	auto bulletManager = game->getBulletManager();
	for (auto& bullet : *bulletManager){
		if (Circle(pos, 2).intersects(Circle(bullet->getPos(), bullet->getSize()))){
			hp--;
			bullet->kill();
		}
	}
}