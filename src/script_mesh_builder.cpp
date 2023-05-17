#include "script_mesh_builder.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/templates/vector.hpp>

#include "script_mesh_part.h"
#include "script_mesh_part_cube.h"
#include "script_mesh_part_sphere.h"

using namespace godot;

void ScriptMeshBuilder::_bind_methods() {
	ClassDB::bind_method(D_METHOD("cube"), &ScriptMeshBuilder::cube);
	ClassDB::bind_method(D_METHOD("sphere"), &ScriptMeshBuilder::sphere);
	ClassDB::bind_method(D_METHOD("get_parts_count"), &ScriptMeshBuilder::get_parts_count);
	ClassDB::bind_method(D_METHOD("get_surface_count"), &ScriptMeshBuilder::get_surface_count);
	ClassDB::bind_method(D_METHOD("get_arrays"), &ScriptMeshBuilder::get_arrays);

	ClassDB::bind_method(D_METHOD("get_instance"), &ScriptMeshBuilder::get_instance);
	// purposefully leaving out set_instance so it's not available in GDScript
}

ScriptMeshBuilder::ScriptMeshBuilder() {
	this->instance = (ScriptMeshInstance*)nullptr;
	parts = Array();
}

ScriptMeshBuilder::~ScriptMeshBuilder() {}

Ref<ScriptMeshPartCube> ScriptMeshBuilder::cube(){
	Ref<ScriptMeshPartCube> cube = memnew(ScriptMeshPartCube);
	parts.push_back(cube);
	return cube;
}

Ref<ScriptMeshPartSphere> ScriptMeshBuilder::sphere(){
	Ref<ScriptMeshPartSphere> sphere = memnew(ScriptMeshPartSphere);
	parts.push_back(sphere);
	return sphere;
}

int ScriptMeshBuilder::get_parts_count(){
	return parts.size();
}

// returns the number of surfaces on all parts.
int ScriptMeshBuilder::get_surface_count(){
	int max = 0;

	for(int i = 0; i < parts.size(); i++){
		Ref<ScriptMeshPart> part = parts[i];
		int surface = part->get_surface();

		if(surface > max){
			max = surface;
		}
	}

	return max+1;
}

// returns the verts, uvs, normals, and indices in an array of arrays.
// the format matches the ArrayMesh arrays.
Array ScriptMeshBuilder::get_arrays(int surface){
	// init arrays to pass to all parts on this surface.
	Array arrays = Array();
	arrays.resize(Mesh::ArrayType::ARRAY_MAX);
	arrays[Mesh::ArrayType::ARRAY_VERTEX] = PackedVector3Array();
	arrays[Mesh::ArrayType::ARRAY_TEX_UV] = PackedVector2Array();
	arrays[Mesh::ArrayType::ARRAY_NORMAL] = PackedVector3Array();
	arrays[Mesh::ArrayType::ARRAY_INDEX] = PackedInt32Array();

	// build all parts with matching surface index
	int partCount = parts.size();
	for(int i = 0; i < partCount; i++){
		Ref<ScriptMeshPart> part = parts[i];
		if(part->get_surface() == surface){
			part->build(arrays);
		}
	}

	return arrays;
}

void ScriptMeshBuilder::build_shapes(PhysicsBody3D *body){
	// don't do anything if there is no body node
	if(body == nullptr){
		return;
	}

	// get a reference to all existing child shape nodes.
	Vector<CollisionShape3D*> shape_nodes = Vector<CollisionShape3D*>();
	int child_count = body->get_child_count();
	for(int i = 0; i < child_count; i++){
		Node* child = body->get_child(i);
		if(child->is_class("CollisionShape3D")){
			shape_nodes.push_back((CollisionShape3D*)child);
		}
	}

	// we want to re-use shape nodes because remaking them all every time causes lag in the editor
	// so let's be smart and only add and remove shape nodes when we need to
	int extra_shape_nodes = shape_nodes.size() - parts.size();

	// if we have too many, delete some
	if(extra_shape_nodes > 0){
		for(int i = 0; i < extra_shape_nodes; i++){
			// ghetto pop (because Vector does not have a pop function)
			Node* extra_node = shape_nodes[shape_nodes.size()-1];
			shape_nodes.remove_at(shape_nodes.size() - 1);

			extra_node->queue_free();
		}

	// if we don't have enough, add some
	}else if(extra_shape_nodes < 0){
		// turn it into a positive number for ease
		extra_shape_nodes = -extra_shape_nodes;

		for(int i = 0; i < extra_shape_nodes; i++){
			CollisionShape3D* new_shape_node = memnew(CollisionShape3D);
			body->add_child(new_shape_node);
			new_shape_node->set_owner(body->get_owner());
			shape_nodes.push_back(new_shape_node);
		}
	}

	// I'm not that confident in the above logic so let's do this for awhile.
	// because if they're not the same, it'll crash down below.
	if(parts.size() != shape_nodes.size()){
		UtilityFunctions::print("error! there are ", parts.size(), " parts and ", shape_nodes.size(), " child shape nodes. that needs to be the same. this is a bug.");
		return;
	}

	// let each part add a shape if it wants to
	for(int i = 0; i < parts.size(); i++){
		Ref<ScriptMeshPart> part = parts[i];
		CollisionShape3D* shape_node = shape_nodes[i];
		part->build_shape(shape_node);
	}
}

void ScriptMeshBuilder::set_instance(ScriptMeshInstance* instance){
	this->instance = instance;
}
ScriptMeshInstance* ScriptMeshBuilder::get_instance() {
	return instance;
}
