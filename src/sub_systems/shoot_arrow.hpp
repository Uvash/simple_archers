#ifndef SHOOT_ARROW_H
#define SHOOT_ARROW_H

#include "../entt/entt.h"
#include "../components.hpp"

#define ARROW_SPEED 40.0f
#define GRAVITY_CONSTANT 9.8f
namespace godot{

	// math get here https://habr.com/ru/articles/538952/
	//
	real_t calculate_discriminant(Vector2 target)
	{
		real_t result = Math::pow(ARROW_SPEED, 4) - GRAVITY_CONSTANT * ( GRAVITY_CONSTANT * Math::pow(target.x, 2) + 2.0f * Math::pow(ARROW_SPEED, 2) * target.y);
		return result;
	}

	real_t calculate_low_fi_angle(Vector2 target){


		real_t fi = Math::atan( ( Math::pow(ARROW_SPEED, 2.0f) - Math::sqrt(calculate_discriminant(target)) ) / ( GRAVITY_CONSTANT * target.x) );
		return fi;
	}

	real_t calculate_hight_fi_angle(Vector2 target){


		real_t fi = Math::atan( ( Math::pow(ARROW_SPEED, 2.0f) + Math::sqrt(calculate_discriminant(target)) ) / ( GRAVITY_CONSTANT * target.x) );
		return fi;
	}


	Vector3 calculate_speed (Vector3 pos, Vector3 end_pos, fraction side ){
		Vector3 from_pos_to_end = end_pos - pos;
		real_t distance = pos.distance_to(end_pos);

		if(distance == 0.0f){
			ERR_PRINT("division by zero!");
			return Vector3{0.0f, 0.0f, 0.0f}; //another we can get division by zero
		}


		real_t height = from_pos_to_end.y;

		real_t fi;
		Vector2 target_2d{distance, height};

		if(side == fraction::blue)
			fi = calculate_low_fi_angle(target_2d);
		if(side == fraction::red)
			fi = calculate_hight_fi_angle(target_2d);

		Vector2 speed_2d{ARROW_SPEED * Math::cos(fi), ARROW_SPEED * Math::sin(fi)};

		// we need to rotate 2d_X (speed in field) in X Z axis and get speed in 3d
		Vector2 XZ_base_vector {1.0f, 0.0f};
		Vector2 XZ_to_point_vector{from_pos_to_end.x , from_pos_to_end.z};


		real_t alpha = XZ_base_vector.angle_to(XZ_to_point_vector);

		Vector3 speed_3d{};
		speed_3d.x = speed_2d.x * cos(alpha);
		speed_3d.y = speed_2d.y;
		speed_3d.z = speed_2d.x * sin(alpha);

		return speed_3d;
	}

	real_t calculate_rotation(Vector3 pos, Vector3 end_pos){
		Vector3 from_pos_to_end = end_pos - pos;
		Vector2 XZ_base_vector {1.0f, 0.0f};
		Vector2 XZ_to_point_vector{from_pos_to_end.x , from_pos_to_end.z};
		return XZ_base_vector.angle_to(XZ_to_point_vector);
	}


	void shoot_arrow(entt::registry &registry, Game &game){
		const auto arrow_prototypes = registry.view<spawn_arrow, position, target_position>();

		for(const entt::entity obj : arrow_prototypes){
			Vector3 start_pos = arrow_prototypes.get<position>(obj).position;
			Vector3 end_pos = arrow_prototypes.get<target_position>(obj).position;

			fraction side;

			if(registry.all_of<red_fraction>(obj))
				side = fraction::red;

			if(registry.all_of<blue_fraction>(obj))
				side = fraction::blue;

			Vector3 speed = calculate_speed(start_pos, end_pos, side);
			auto arrow = make_arrow(registry, game, start_pos, speed, side);
			Node * node = registry.get<godot_node>(arrow).node;
			Node3D * godot_node3d = Object::cast_to<Node3D>(node);
			godot_node3d->rotate(Vector3{0.0f, 1.0f, 0.0f}, calculate_rotation(start_pos, end_pos));

			registry.destroy(obj);
		}

	}

}
#endif // SHOOT_ARROW_H
