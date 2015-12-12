#include "LD34.hpp"
#include "Player.hpp"
#include "ScrollingBackground.hpp"
#include <Engine/Factory.hpp>

int main() {
	engine::Factory::RegisterType("player", engine::Factory::CreateChildNode<Player>);
	engine::Factory::RegisterType("bg", engine::Factory::CreateChildNode<ScrollingBackground>);
	LD34 game;
	game.run();
	return 0;
}