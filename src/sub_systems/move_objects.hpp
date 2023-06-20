#ifndef MOVE_OBJECTS_H
#define MOVE_OBJECTS_H

#include "../entt/entt.h"
#include "../components.hpp"

namespace godot
{


	void move_objects(entt::registry &registry, real_t delta){
		const auto moving_objects = registry.view<position, speed>();

		for(const entt::entity obj : moving_objects){
			const Vector3 obj_speed = moving_objects.get<speed>(obj).speed;

			moving_objects.get<position>(obj).position += obj_speed * delta;
		}

	}

	void acceleration_objects(entt::registry &registry, real_t delta){
		const auto moving_objects = registry.view<speed, acceleration>();

		for(const entt::entity obj : moving_objects){
			const Vector3 obj_acceleration = moving_objects.get<acceleration>(obj).acceleration;

			moving_objects.get<speed>(obj).speed += obj_acceleration * delta;
		}
	}
}
#endif
