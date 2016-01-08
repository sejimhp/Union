#include <Siv3D.hpp>

class Game{
public:
	Game();
	void update();
	void draw();

	void drawBack();
	static const Size stageSize;
private:
	int frameCount;
};