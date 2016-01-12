#include "Enemy.h"

#include "Game.h"
#include "Bullet.h"
#include "Player.h"

Enemy::Enemy(Vec2 pos) :
pos(pos),
rad(0.0), size(0.0),
hp(0),
frameCount(0), damageCount(0), fireCount(0),
state(State::NORMAL)
{}

void Enemy::update(Game* game){
	frameCount++;
	fireCount++;
	pos += Vec2(0.0, 2.0);

	if (pos.x > Game::stageSize.x || pos.x < 0 || pos.y > Game::stageSize.y || pos.y < 0){
		kill();
	}

	auto shotManager = game->getPlayer()->getShotManager();
	for (auto& shot : *shotManager){
		if (Circle(pos, size).intersects(Circle(shot->getPos(), shot->getSize()))){
			hp--;
			damageCount = 0;
			shot->kill();
		}
	}

	if (hp <= 0){
		kill();
	}

	auto player = game->getPlayer();
	if (player->boolCatcherState() && 
		Circle(pos, size).intersects(Circle(player->getPos(), 150)))catchCount++;
	else if (catchCount != 0) catchCount = 0;

	if (catchCount == 50){
		kill();
		state = State::CATCHED;
	}

}

CEnemy::CEnemy(Vec2 pos) : Super(pos){
	hp = 10;
	size = 15.0;
}

void CEnemy::update(Game* game){
	Super::update(game);
	rad += Radians(2.0);

	auto bulletManager = game->getBulletManager();
	const Vec2 playerPos = game->getPlayer()->getPos();
	if (fireCount % 4 == 0 && frameCount > 60){
		for (auto i : step_to(-1, 1, 1)){
			double shotRad = rad + TwoPi / 3 * i;
			auto bullet = std::make_shared<Bullet>(pos, Color(255, 100, 100), shotRad, 5.0, 0.0);
			bulletManager->add(bullet);
		}
	}

}

void CEnemy::draw(Game* game){
	Color color = damageCount < 10 ? Color(255, 200) : Color(Palette::Yellow).setAlpha(123);
	Circle(pos, size).draw(color).drawFrame();
}

SEnemy::SEnemy(Vec2 pos) : Super(pos){
	hp = 10;
	size = 15.0;
}

void SEnemy::update(Game* game){
	Super::update(game);
	rad += Radians(2.0);

	auto bulletManager = game->getBulletManager();
	const Vec2 playerPos = game->getPlayer()->getPos();
	if (fireCount % 1 == 0 && frameCount > 60){
		for (auto i : step_to(-4, 4, 1)){
			double shotRad = rad + TwoPi / 8 * i;
			auto bullet = std::make_shared<Bullet>(pos, Color(255, 100, 100), shotRad, 5.0, 0.0);
			bulletManager->add(bullet);
		}
	}
}

void SEnemy::draw(Game* game){
	Color color = damageCount < 10 ? Color(255, 200) : Color(Palette::Yellow).setAlpha(123);
	RectF(size * 2).setCenter(pos).rotated(rad * 10).draw(color).drawFrame();
}