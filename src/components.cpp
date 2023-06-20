#include "components.hpp"
using namespace godot;

godot_node::~godot_node()
{
	if(node == nullptr)
		return;

	//node->queue_free();	// Yes it`s look at memory leak, but i hope that engine can clear up his nodes
	node == nullptr;
}
