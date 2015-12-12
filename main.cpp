#include "LD34.hpp"
#include "Player.hpp"
#include <Engine/Factory.hpp>

int main() {
	engine::Factory::RegisterType("player", engine::Factory::CreateChildNode<Player>);
	LD34 game;
	game.run();
	return 0;
}