#ifndef GAME_H
#define GAME_H

#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/node.hpp>
#include "entt/entt.h"
#include <memory>

namespace godot {

class Game : public Node {
	GDCLASS(Game, Node)

protected:
	entt::registry registry;
	//std::shared_ptr<entt::registry> registry;
	static void _bind_methods();

	Ref<PackedScene> cylinder_scene;
	Ref<PackedScene> arrow_scene;

public:
    Game() {//registry = std::make_shared<entt::registry>();
    }
    ~Game() override{}

    void _ready();

	void set_cylinder_scene(Ref<PackedScene> new_cylinder);
	Ref<PackedScene> get_cylinder_scene();

	void set_arrow_scene(Ref<PackedScene> new_arrow);
	Ref<PackedScene> get_arrow_scene();

	Vector3 red_spawn{10.0, 0.0, 10.0};
	Vector3 blue_spawn{90.0, 0.0, 90.0};

	void spawn_cylinder(Vector3 start_pos);
	void spawn_arrow(Vector3 start_pos, Vector3 target_pos);
	void _physics_process(const double p_delta) override;

	Node* create_cylinder(Vector3 pos);
	Node* create_arrow(Vector3 pos);
};



} //namespace godot

#endif
