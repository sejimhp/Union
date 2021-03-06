#pragma once
#include <Siv3D.hpp>
#include <memory>
#include <vector>

class Game;

class Actor : private Uncopyable{
public:
	Actor() = default;
	virtual ~Actor() = default;
	virtual void update(Game* game) = 0;
	virtual void draw(Game* game) = 0;

	void kill(){ enabled = false; }
	bool isEnabled(){ return enabled; }
private:
	bool enabled = true;
};

template<typename Type>
class ActorManager{
public:
	ActorManager() = default;
	virtual ~ActorManager() = default;

	void add(std::shared_ptr<Type> actor){ actors.emplace_back(actor);	}
	void clear(){	actors.clear();	}
	int size(){	return actors.size();	}

	virtual void update(Game* game){
		for (auto& actor : actors){
			actor->update(game);
		}
		Erase_if(actors, [](std::shared_ptr<Type> actor){return !actor->isEnabled(); });
	}
	virtual void draw(Game* game){
		for (auto& actor : actors){
			actor->draw(game);
		}
	}

	typename std::list<std::shared_ptr<Type>>::const_iterator begin(){ return actors.begin(); }
	typename std::list<std::shared_ptr<Type>>::const_iterator end(){ return actors.end(); }
private:
	std::list<std::shared_ptr<Type>> actors;
};