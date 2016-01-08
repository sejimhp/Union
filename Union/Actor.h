#pragma once
#include <Siv3D.hpp>
#include <memory>

class Game;

class Actor : private Uncopyable{
public:
	Actor() = default;
	virtual ~Actor() = default;
	virtual void update(Game* game);
	virtual void draw(Game* game);

	void kill(){ enabled = false; }
	bool IsEnabled(){ return enabled; }
private:
	bool enabled = true;
};