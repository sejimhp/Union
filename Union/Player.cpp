#include "Player.h"

#include "Game.h"
#include "Charactor.h"
#include "Enemy.h"
#include "Bullet.h"

namespace{
	static const int HP_MAX = 200;
}

Player::Player(Vec2 pos, int ffig) : Super(pos, ffig){}
Player::Player(Figure ffig) : Super(Vec2(0, 0), ffig){}
Player::Player(int ffig) : Super(Vec2(0, 0), ffig){}

void Player::init(){
	pos = Vec2(500, 700);
	hp = HP_MAX;
}

void Player::update(Game* game){
	if (Input::KeyUp.pressed && pos.y >= 0) pos.y -= 5;
	if (Input::KeyDown.pressed && pos.y < Game::stageSize.y)	pos.y += 5;
	if (Input::KeyRight.pressed && pos.x < Game::stageSize.x)	pos.x += 5;
	if (Input::KeyLeft.pressed && pos.x >= 0) pos.x -= 5;

	//fire
	auto bulletManager = game->getMyBulletManager();
	switch (fig){
	case Figure::TRIANGLE:
		for (int i : {-1, 1, 0}) {
			const double shotRad = Radians(5 * i);
			if (System::FrameCount() % 10 == 0) {
				auto shot = std::make_shared<Bullet>(pos, Palette::Aqua, shotRad - HalfPi, 1, 1);
				bulletManager->add(shot);
			}
		}
		break;
	case Figure::SQUARE:
		break;
	case Figure::TSQUARE:
		rad += 2;
		if (System::FrameCount() % 10 == 0){
			for (auto i : step_to(-4, 4, 1)){
				double shotRad = rad + TwoPi / 8 * i;
				auto bullet = std::make_shared<Bullet>(pos, Palette::Aqua, shotRad, 5.0, 0.0);
				bulletManager->add(bullet);
			}
		}
		break;
	case Figure::CIRCLE:
		if (System::FrameCount() % 70 == 0){
			for (int i : step(50)){
				rad = TwoPi / 100 * Random(1, 100);
				auto bullet = std::make_shared<Bullet>(pos, Palette::Aqua, rad, Random(1.0, 15.0), 0.0);
				bulletManager->add(bullet);
			}
		}
		break;
	};

	//catcher
	if (Input::KeyZ.clicked && fig == Figure::TRIANGLE){
		frameCount = System::FrameCount();
		state = State::CATCHER;
	}
	else if (state == State::CATCHER && (System::FrameCount() - frameCount) > 100){
		state = State::NORMAL;
	}

	checktHit(game);
}

void Player::draw(Game* game){
	if (state == State::CATCHER){
		Circle(pos, 120).draw(Color(100, 100, 0, 100));
		Circle(pos, 120).drawArc(0.0, TwoPi * (static_cast<double>(System::FrameCount() - frameCount) / 100), 0.0, 2.0, Color(255, 150, 150, 122));
	}
	drawChar();
	if (fig != Figure::SQUARE){ Circle(pos, 2).draw(Color(150, 0, 0, 122)); }
	Circle(pos, 25.0).drawArc(0.0, TwoPi * (static_cast<double>(hp) / HP_MAX), 0.0, 2.0, Color(255, 150, 150, 122));
}

void Player::checktHit(Game* game){
	//Bullet
	auto bulletManager = game->getBulletManager();
	for (auto& bullet : *bulletManager){
		if (fig == Figure::SQUARE &&
			RectF(size * 2).setCenter(pos).intersects(Circle(bullet->getPos(), bullet->getSize()))){
			bullet->kill();
		}
		if (Circle(pos, 2).intersects(Circle(bullet->getPos(), bullet->getSize()))){
			hp--;
			bullet->kill();
		}
	}
	if (hp <= 0){
		state = State::GAMEOVER;
	}

	//Enemy
	if (fig == Figure::SQUARE){
		auto enemyManager = game->getEnemyManager();
		for (auto& enemy : *enemyManager){
			switch (enemy->getFigre()){
			case Figure::CIRCLE:
			case Figure::TSQUARE:
				if (Circle(pos, size).intersects(Circle(enemy->getPos(), enemy->getSize()))){
					hp -= 50;
					enemy->kill();
				}
				break;
			case Figure::SQUARE:
				if (RectF(size * 2).setCenter(pos).intersects(Circle(enemy->getPos(), enemy->getSize()))){
					hp -= 50;
					enemy->kill();
				}
				break;
			};
		}
	}
}

MemberManager::MemberManager(){
	actors.resize(5, nullptr);
}

void MemberManager::add(std::shared_ptr<Player> actor){
	if (actors[1] == nullptr){ actors[1] = actor; }
	else if (actors[3] == nullptr){ actors[3] = actor; }
	else if (actors[0] == nullptr){ actors[0] = actor; }
	else if (actors[4] == nullptr){ actors[4] = actor; }
}

bool MemberManager::IsSquare(){
	for (int i : step(5)){
		if (actors[i] != nullptr && actors[i]->IsSquare()){
			return true;
		}
	}
	return false;
}

Vec2 MemberManager::getSquarePos(){
	for (auto& actor : actors){
		if (actor != nullptr && actor->IsSquare()){
			return actor->getPos();
		}
	}
	return Vec2(0, 0);
}
