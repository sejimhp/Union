#include "Bullet.h"

#include "Game.h"

Bullet::Bullet(Vec2 pos, Color color, double rad, double speed, double accel):
pos(pos),
color(color),
rad(rad),
speed(speed),
accel(accel),
size(5.0),
type(BulletKind::CIRCLE)
{}

void Bullet::update(Game* game){
	if (pos.x > Game::stageSize.x || pos.x < 0 || pos.y > Game::stageSize.y || pos.y < 0){
		kill();
	}

	speed += accel;
	speed = Clamp(speed, 2.0, 15.0);
	Vec2 vec = Vec2(Cos(rad), Sin(rad)) * speed;
	pos += vec;
}

void Bullet::draw(Game* game){
	switch(type){
	case BulletKind::CIRCLE:
		Circle(pos, size).draw(color.setAlpha(200));
		break;
	case BulletKind::TRIANGLE:
		Triangle({ -5, 5 }, { 0, -15 }, { 5, 5 }).setCentroid(pos).draw(Color(255, 165, 30));
		break;
	case BulletKind::SQUARE:
		RectF(size * 2).setCenter(pos).draw(Palette::Aliceblue).drawFrame();
		break;
	};
}