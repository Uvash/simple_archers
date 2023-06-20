#ifndef ARCHER_AI_H
#define ARCHER_AI_H

#include "../components.hpp"
#include "../entt/entt.h"

#define DISTANCE_TO_SHOOT 1600.0f
#define MAX_DISTANCE_ON_FIELD 17000.0f // more that ~ (sqrt(2) * 100) ^ 2   100 - is side of a square)
namespace godot
{
	void shoot_to_target(entt::registry &registry, entt::entity hero, Vector3 end_pos, fraction fract){

		registry.get<speed>(hero).speed = Vector3{0.0f , 0.0f, 0.0f};

		const auto arrows = registry.view<arrow>();
		if(arrows.size() > 100)
			return;

		Vector3 hero_position = registry.get<position>(hero).position;
		//ERR_PRINT("make_spawn_arrow");
		make_spawn_arrow(registry, hero_position, end_pos, fract);
	}

	void move_to_target(entt::registry &registry, entt::entity hero, Vector3 position_target){
		const Vector3 hero_position = registry.get<position>(hero).position;
		Vector3 move_vector = position_target - hero_position;
		move_vector.normalize();


		registry.get<speed>(hero).speed = move_vector;
	}
/*
	entt::entity get_target(entt::registry &registry, entt::entity hero){
		godot::fraction fraction;

		if(registry.all_of<red_fraction>(hero))
			fraction = godot::fraction::red;

		if(registry.all_of<blue_fraction>(hero))
			fraction = godot::fraction::blue;


	}
*/
	void make_action_for_blue(entt::registry &registry, entt::entity hero)
	{
		Vector3 hero_position = registry.get<position>(hero).position;
		const auto target_objects = registry.view<archer, position, red_fraction>();

		real_t min_distance_to_target{MAX_DISTANCE_ON_FIELD};
		Vector3 position_target{0.0f, 0.0f, 0.0f};

		for(const entt::entity obj : target_objects){
			const Vector3 enemy_position = target_objects.get<position>(obj).position;

			real_t distance_candidat = hero_position.distance_squared_to(enemy_position);
			if(min_distance_to_target > distance_candidat)
			{
				min_distance_to_target = distance_candidat;
				position_target = enemy_position;
			}
		}

		if(min_distance_to_target <= DISTANCE_TO_SHOOT)
			shoot_to_target(registry, hero, position_target, fraction::blue);
		else
			move_to_target(registry, hero, position_target);
	}

	void make_action_for_red(entt::registry &registry, entt::entity hero)
	{
		Vector3 hero_position = registry.get<position>(hero).position;
		const auto target_objects = registry.view<archer, position, blue_fraction>();

		real_t min_distance_to_target{MAX_DISTANCE_ON_FIELD};
		Vector3 position_target{0.0f, 0.0f, 0.0f};

		for(const entt::entity obj : target_objects){
			const Vector3 enemy_position = target_objects.get<position>(obj).position;

			real_t distance_candidat = hero_position.distance_squared_to(enemy_position);
			if(min_distance_to_target > distance_candidat)
			{
				min_distance_to_target = distance_candidat;
				position_target = enemy_position;
			}
		}

		if(min_distance_to_target <= DISTANCE_TO_SHOOT)
			shoot_to_target(registry, hero, position_target, fraction::red);
		else
			move_to_target(registry, hero, position_target);
	}

	void archer_ai(entt::registry &registry){
		const auto red_team = registry.view<archer, red_fraction>();
		const auto blue_team = registry.view<archer, blue_fraction>();

		for(const entt::entity obj : red_team){
			make_action_for_red(registry, obj);
		}

		for(const entt::entity obj : blue_team){
			make_action_for_blue(registry, obj);
		}
	}
}
#undef MAX_DISTANCE_ON_FIELD
#undef DISTANCE_TO_SHOOT
#endif // ARCHER_AI_H
