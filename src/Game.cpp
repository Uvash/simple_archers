#include "Game.hpp"

//#include "factories.hpp"
#include "sub_systems/spawn_archer.hpp"
#include "sub_systems/archer_ai.hpp"
#include "sub_systems/move_objects.hpp"
#include "sub_systems/update_godot_objects.hpp"
#include "sub_systems/shoot_arrow.hpp"
#include "sub_systems/arrow_ai.hpp"
#include "sub_systems/health_check.hpp"

#include <godot_cpp/classes/engine.hpp>

#define GAME_TICK 0.05f
using namespace godot;

void Game::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_cylinder_scene", "ref_scene"), &Game::set_cylinder_scene);
    ClassDB::bind_method(D_METHOD("get_cylinder_scene"), &Game::get_cylinder_scene);
    ClassDB::add_property("Game", PropertyInfo(Variant::OBJECT, "cylinder_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_cylinder_scene", "get_cylinder_scene");

    ClassDB::bind_method(D_METHOD("set_arrow_scene", "ref_scene"), &Game::set_arrow_scene);
    ClassDB::bind_method(D_METHOD("get_arrow_scene"), &Game::get_arrow_scene);
    ClassDB::add_property("Game", PropertyInfo(Variant::OBJECT, "arrow_scene", PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), "set_arrow_scene", "get_arrow_scene");
}

void Game::set_cylinder_scene(Ref<PackedScene> new_cylinder)
{
    cylinder_scene = new_cylinder;
}

 Ref<PackedScene> Game::get_cylinder_scene()
 {
     return cylinder_scene;
 }

void Game::set_arrow_scene(Ref<PackedScene> new_arrow)
{
    arrow_scene = new_arrow;
}

 Ref<PackedScene> Game::get_arrow_scene()
 {
     return arrow_scene;
 }

void Game::_physics_process(const double p_delta)
{
	// If scene run in editor ignore
	Engine * engine = Engine::get_singleton();
	//if(engine->is_editor_hint())
		//return
/*
	godot::Node *node = cylinder_scene->instantiate();



	//game.add_child(node);

	add_child(node);
*/

	spawn_archer(registry, *this);
	archer_ai(registry);
	shoot_arrow(registry, *this);
	acceleration_objects(registry, GAME_TICK);
	move_objects(registry, GAME_TICK);
	update_godot_objects(registry);
	check_arrow(registry);
	health_check(registry);
}
void Game::_ready()
{
	//registry = registry.create();

	make_spawn_point(registry, Vector3{10.0, 0.0, 10.0}, godot::fraction::red);
	make_spawn_point(registry, Vector3{90.0, 0.0, 90.0}, godot::fraction::blue);
}

Node* Game::create_cylinder(Vector3 pos)
{
	godot::Node *node = cylinder_scene->instantiate();
	node->set("position", pos);
	add_child(node);

	return node;
}

Node* Game::create_arrow(Vector3 pos)
{
	godot::Node *node = arrow_scene->instantiate();
	node->set("position", pos);
	add_child(node);

	return node;
}
