#ifndef FACTORIES_H
#define FACTORIES_H

#include "components.hpp"
#include "entt/entt.h"
namespace godot
{
class Game;

entt::entity make_archer(entt::registry &registry, godot::Game &game, godot::Vector3 pos, godot::fraction side)
{

	const entt::entity e = registry.create();

	registry.emplace<archer>(e);

	registry.emplace<position>(e, pos);
	registry.emplace<speed>(e);
	registry.emplace<collision_cylinder>(e);
	registry.emplace<alive>(e);
	registry.emplace<health>(e);

	switch((int)side){
		case((int)godot::fraction::red) : {
			registry.emplace<red_fraction>(e);
		} break;
		case((int)godot::fraction::blue) : {
			registry.emplace<blue_fraction>(e);
		} break;
	}
/*
	Ref<PackedScene> cylinder = game.get_cylinder_scene();
	godot::Node *node = cylinder->instantiate();



	ERR_PRINT(str);

	node->set("position", pos);
*/
	godot::Node *node = game.create_cylinder(pos);
	registry.emplace<godot_node>(e, node);


	return e;
}

entt::entity make_arrow(entt::registry &registry, Game &game, Vector3 pos, Vector3 arrow_speed, fraction arrow_side)
{

	const entt::entity e = registry.create();

	registry.emplace<arrow>(e);

	registry.emplace<position>(e, pos);
	registry.emplace<speed>(e, arrow_speed);
	registry.emplace<acceleration>(e);
	registry.emplace<alive>(e);
	registry.emplace<damage>(e);

	switch((int)arrow_side){
		case((int)godot::fraction::red) : {
			registry.emplace<red_fraction>(e);
		} break;
		case((int)godot::fraction::blue) : {
			registry.emplace<blue_fraction>(e);
		} break;
	}

	godot::Node *node = game.create_arrow(pos);
	registry.emplace<godot_node>(e, node);


	return e;
}

entt::entity make_spawn_point(entt::registry &registry, Vector3 pos, godot::fraction side){
	const entt::entity e = registry.create();

	registry.emplace<spawn_point>(e);

	registry.emplace<position>(e, pos);
	registry.emplace<spawn_count>(e);

	switch((int)side){
		case((int)godot::fraction::red) : {
			registry.emplace<red_fraction>(e);
		} break;
		case((int)godot::fraction::blue) : {
			registry.emplace<blue_fraction>(e);
		} break;
	}

	return e;
}

entt::entity make_spawn_arrow(entt::registry &registry, godot::Vector3 pos, godot::Vector3 end_pos, godot::fraction side){
	const entt::entity e = registry.create();

	registry.emplace<spawn_arrow>(e);

	registry.emplace<position>(e, pos);
	registry.emplace<target_position>(e, end_pos);

	switch((int)side){
		case((int)godot::fraction::red) : {
			registry.emplace<red_fraction>(e);
		} break;
		case((int)godot::fraction::blue) : {
			registry.emplace<blue_fraction>(e);
		} break;
	}

	return e;
}

} //namespace godot

#endif
