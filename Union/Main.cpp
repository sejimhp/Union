
# include <Siv3D.hpp>
#include <memory>
#include "Game.h"

void Main()
{
	//Window::Resize(1280, 720);
	Window::SetVirtualFullscreen({ 1366, 768 });
	auto game = std::make_unique<Game>();

	while (System::Update())
	{
		game->update();
		game->draw();
	}
}
