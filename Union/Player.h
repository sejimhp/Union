#pragma once
#include <Siv3D.hpp>
#include <deque>
#include "Actor.h"

#include "Charactor.h"

class Game;

class Player : public Charactor{
public:
	Player(Vec2 pos, int sstate, int ffig);
	Player(int sstate, int ffig);
	void init();
	void update(Game* game);
	void draw(Game* game);

	void setMember(int num);
	void setPos(Vec2 pos) { this->pos = pos; }
	State getState() const { return state; }
	void checkBulletHit(Game* game);
private:
};

class MemberManager{
public:
	MemberManager();
	virtual ~MemberManager() = default;

	void clear(){ actors.clear(); actors.resize(5); }
	int size(){ return actors.size(); }

	void update(Game* game){
		for (auto& actor : actors){
			if (actor != nullptr){
				actor->update(game);
			}
		}
		adjPos();
		//Erase_if(actors, [](std::shared_ptr<Player> actor){return !actor->isEnabled(); });
	}
	void draw(Game* game){
		for (auto& actor : actors){
			if (actor != nullptr){
				actor->draw(game);
			}
		}
	}
	//êŠ‚Ì’²®
	void adjPos(){
		if (actors[1] != nullptr){ actors[1]->setPos(actors[2]->getPos() + Vec2(-100, 0)); }
		if (actors[3] != nullptr){ actors[3]->setPos(actors[2]->getPos() + Vec2(100, 0)); }
		if (actors[0] != nullptr){ actors[0]->setPos(actors[2]->getPos() + Vec2(-200, 0)); }
		if (actors[4] != nullptr){ actors[4]->setPos(actors[2]->getPos() + Vec2(200, 0)); }
	}

	//typename std::vector<std::shared_ptr<Charactor>>::const_iterator begin(){ return actors.begin(); }
	//typename std::vector<std::shared_ptr<Charactor>>::const_iterator end(){ return actors.end(); }
	void add(std::shared_ptr<Player> actor);
	void addMain(std::shared_ptr<Player> actor){ actors[2] = actor; }
	std::shared_ptr<Player> getMainPlayer() const{ return actors[2]; }
private:
	std::vector<std::shared_ptr<Player>> actors;
};