#include "Enemy.h"

#include "Game.h"
#include "Bullet.h"
#include "Player.h"

Enemy::Enemy(Vec2 pos, int ffig) : Super(pos, ffig){}

void Enemy::update(Game* game){
	frameCount++;
	pos += Vec2(0.0, 2.0);

	bulletUpdate(game);

	if (hp <= 0 || pos.x > Game::stageSize.x || pos.x < 0 || pos.y > Game::stageSize.y || pos.y < 0){
		kill();
	}

	auto shotManager = game->getMyBulletManager();
	for (auto& shot : *shotManager){
		if (Circle(pos, size).intersects(Circle(shot->getPos(), shot->getSize()))){
			hp--;
			damageCount = 0;
			shot->kill();
		}
	}

	auto player = game->getPlayerManager()->getMainPlayer();
	if (player->IsStateCATCHER() &&
		Circle(pos, size).intersects(Circle(player->getPos(), 120)))catchCount++;
	else if (catchCount != 0) catchCount = 0;
	
	if (catchCount == 50){
		kill();
	}
}

void Enemy::bulletUpdate(Game* game){
	auto bulletManager = game->getBulletManager();
	const Vec2 playerPos = game->getPlayerManager()->getMainPlayer()->getPos();
	const double rad2 = Atan2(playerPos.y - pos.y, playerPos.x - pos.x);

	rad += Radians(2.0);
	switch (fig){
	case Figure::CIRCLE:
		if (System::FrameCount() % 4 == 0 && frameCount > 60){
			for (auto i : step_to(-1, 1, 1)){
				double shotRad = rad + TwoPi / 3 * i;
				auto bullet = std::make_shared<Bullet>(pos, Color(255, 100, 100), shotRad, 5.0, 0.0);
				bulletManager->add(bullet);
			}
		}
		break;
	case Figure::SQUARE:
		if (System::FrameCount() % 1 == 0 && frameCount > 60){
			double shotRad = rad2 + TwoPi / (Random(-2.0, 2.0) * 20);
			auto bullet = std::make_shared<Bullet>(pos, Color(255, 100, 100), shotRad, 5.0, 0.0);
			bulletManager->add(bullet);
		}
		break;
	case Figure::TSQUARE:
		if (System::FrameCount() % 4 == 0 && frameCount > 60){
			for (auto i : step_to(-4, 4, 1)){
				double shotRad = rad + TwoPi / 8 * i;
				auto bullet = std::make_shared<Bullet>(pos, Color(255, 100, 100), shotRad, 5.0, 0.0);
				bulletManager->add(bullet);
			}
		}
		break;
	};
}

void Enemy::draw(Game* game){
	//Color color = damageCount < 10 ? Color(255, 200) : Color(Palette::Yellow).setAlpha(123);
	drawChar();
	Circle(pos, size + 10).drawArc(0.0, TwoPi * (static_cast<double>(catchCount) / 50), 0.0, 2.0, Color(150, 255, 150, 122));
}