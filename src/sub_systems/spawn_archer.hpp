#ifndef SPAWN_ARCHERS_H
#define SPAWN_ARCHERS_H

//#include "../Game.hpp"
#include "../components.hpp"
#include "../factories.hpp"
#include "../entt/entt.h"

//void spawn_archer(entt::registry &registry, godot::Game & game);
namespace godot
{

	class Game;


	void spawn_archer(entt::registry &registry, Game & game)
	{

		const auto spawn_objects = registry.view<spawn_point, position, spawn_count>();

		for(const entt::entity obj : spawn_objects){
			const int spawn_remainder = spawn_objects.get<spawn_count>(obj).spawn_count;
			if(spawn_remainder <= 0)
				continue;

			const godot::Vector3 pos = spawn_objects.get<position>(obj).position;
			godot::fraction fraction;

			if(registry.all_of<red_fraction>(obj))
				fraction = godot::fraction::red;

			if(registry.all_of<blue_fraction>(obj))
				fraction = godot::fraction::blue;

			make_archer(registry, game, pos, fraction);

			spawn_objects.get<spawn_count>(obj).spawn_count--;

		}

	}

	int pr34 = 42;
	void dumpy_func();
	void easy_func(){ pr34--; }
}
#endif // SPAWN_ARCHERS_H
