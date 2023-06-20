#ifndef HEALTH_CHEK_H
#define HEALTH_CHEK

#include "../components.hpp"
namespace godot{
	class Game;

	void health_check(entt::registry &registry)
	{
		const auto healty_objects = registry.view<health>();

		for(const entt::entity obj : healty_objects){
			real_t health_obj = healty_objects.get<health>(obj).health;

			if(health_obj <= 0.0f)
			{
				if(registry.all_of<godot_node>(obj))
				{
					Node * node = registry.get<godot_node>(obj).node;
					if(node != nullptr)
						node->queue_free();
					node = nullptr;
				}
				registry.destroy(obj);
			}
		}
	}
}
#endif // HEALTH_CHEK_H
