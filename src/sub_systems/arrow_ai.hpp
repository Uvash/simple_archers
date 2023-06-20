#ifndef ARROW_AI_H
#define ARROW_AI_H

#define ARCHER_RADIUS 0.25f
#include "../components.hpp"

namespace godot
{
	void destroy_arrow(entt::registry &registry, const entt::entity &obj){
		Node * node = registry.get<godot_node>(obj).node;
		if(node != nullptr)
			node->queue_free();
		node = nullptr;
		registry.destroy(obj);
	}

	void slap_target(entt::registry &registry, const entt::entity &hero, real_t damage)
	{
		registry.get<health>(hero).health -= damage;
	}

	bool find_and_kill_targets(entt::registry &registry, const entt::entity &arrow)
	{
		const Vector3 arrow_position = registry.get<position>(arrow).position;
		if(registry.all_of<red_fraction>(arrow))
		{
			const auto blue_archers = registry.view<archer, position, blue_fraction>();
			for(const entt::entity obj : blue_archers){
				const Vector3 obj_position = blue_archers.get<position>(obj).position;
				Vector2 XZ_obj_pos{obj_position.x, obj_position.z};
				Vector2 XZ_arrow_pos{arrow_position.x, arrow_position.z};

				if(XZ_arrow_pos.distance_to(XZ_obj_pos) <= ARCHER_RADIUS){
					real_t arrow_damage = registry.get<damage>(arrow).damage;
					slap_target(registry, obj, arrow_damage);
					return true;
				}

			}

			return false;
		}

		if(registry.all_of<blue_fraction>(arrow))
		{
			const auto red_archers = registry.view<archer, position, red_fraction>();
			for(const entt::entity obj : red_archers){
				const Vector3 obj_position = red_archers.get<position>(obj).position;
				Vector2 XZ_obj_pos{obj_position.x, obj_position.z};
				Vector2 XZ_arrow_pos{arrow_position.x, arrow_position.z};

				if(XZ_arrow_pos.distance_to(XZ_obj_pos) <= ARCHER_RADIUS){
					real_t arrow_damage = registry.get<damage>(arrow).damage;
					slap_target(registry, obj, arrow_damage);
					return true;
				}
			}

			return false;
		}

		return false;
	}

	void check_arrow(entt::registry &registry){
		const auto arrows = registry.view<arrow, position>();
		for(const entt::entity obj : arrows){
			const Vector3 obj_position = arrows.get<position>(obj).position;
			if(obj_position.y > 1.7f)
				continue;

			if(find_and_kill_targets(registry, obj))
				continue;

			if(obj_position.y <= 0.0f)
			{
				destroy_arrow(registry, obj);
			}

		}
	}
}



#endif // ARROW_AI_H
