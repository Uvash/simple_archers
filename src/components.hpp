#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <godot_cpp/classes/node.hpp>
namespace godot
{

	struct position{
		Vector3 position;
	};

	struct speed{
		Vector3 speed = Vector3{ 0.0f , 0.0f, 0.0f};
	};

	struct acceleration{
		Vector3 acceleration = Vector3{ 0.0f , -9.7f, 0.0f};
	};

	struct target_position{
		Vector3 position;
	};

	struct collision_cylinder{
		real_t radius = 0.125f;
		real_t height = 1.7f;
	};

	struct godot_node{
		Node * node = nullptr;

		~godot_node();
	};

	struct alive{
		bool alive = true;
	};

	struct health{
		real_t health = 100.0;
	};

	struct damage{
		real_t damage = 20.0;
	};

	struct spawn_count{
		int spawn_count = 20;
	};


	struct arrow{
	};

	struct archer{
	};

	struct spawn_point{
	};

	struct spawn_arrow{
	};

	enum fraction {
		red = 0,
		blue = 1
	};

	struct red_fraction{
	};

	struct blue_fraction{
	};

} //namespace godot

#endif
