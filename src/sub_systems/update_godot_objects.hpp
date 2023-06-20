#ifndef UPDATE_GODOT_OBJECTS_H
#define UPDATE_GODOT_OBJECTS_H

#include "../entt/entt.h"
#include "../components.hpp"

#include <godot_cpp/classes/node3d.hpp>
namespace godot
{
	void update_godot_objects(entt::registry &registry)
	{
		const auto godot_objects = registry.view<godot_node, position>();

		for(const entt::entity obj : godot_objects){
			godot::Node * node = godot_objects.get<godot_node>(obj).node;

			if(node == nullptr)
				continue;

			godot::Node3D * node3d = Object::cast_to<Node3D>(node);
			node3d->set_position(godot_objects.get<position>(obj).position);
		}
	}
}
#endif
