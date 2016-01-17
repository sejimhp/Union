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


Bullet::Bullet(Vec2 pos, Color color, double rad):
pos(pos),
color(color),
rad(rad),
speed(10.0),
accel(0),
size(5.0),
type(BulletKind::HANABI),
frameCount(0)
{}

void Bullet::update(Game* game){
	if (pos.x > Game::stageSize.x || pos.x < 0 || pos.y > Game::stageSize.y || pos.y < 0){
		kill();
	}
		Vec2 vec = Vec2(Cos(rad), Sin(rad)) * speed;
	switch (type){
	case BulletKind::HANABI:
		frameCount++;
		pos += vec;
		if (frameCount == 50){
			color = Palette::Lightgreen;
			type = BulletKind::CIRCLE;
			rad = TwoPi / 100 * Random(1,100);
			speed = Random(1.0, 15.0);
		}
		break;
	case BulletKind::CIRCLE:
		speed += accel;
		speed = Clamp(speed, 2.0, 15.0);
		pos += vec;
		break;
	};
}

void Bullet::draw(Game* game){
	switch(type){
	case BulletKind::CIRCLE:
	case BulletKind::HANABI:
		Circle(pos, size).draw(color);
		break;
	case BulletKind::TRIANGLE:
		Triangle({ -5, 5 }, { 0, -15 }, { 5, 5 }).setCentroid(pos).draw(Color(255, 165, 30));
		break;
	case BulletKind::SQUARE:
		RectF(size * 2).setCenter(pos).draw(Palette::Aliceblue).drawFrame();
		break;
	};
}