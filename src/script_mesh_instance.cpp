#include "script_mesh_instance.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "script_mesh_builder.h"

using namespace godot;

void ScriptMeshInstance::_bind_methods() {
	ClassDB::bind_method(D_METHOD("build"), &ScriptMeshInstance::build);
	ClassDB::bind_method(D_METHOD("get_script_mesh"), &ScriptMeshInstance::get_script_mesh);
	ClassDB::bind_method(D_METHOD("set_script_mesh", "new_script_mesh"), &ScriptMeshInstance::set_script_mesh);
	ClassDB::add_property("ScriptMeshInstance", PropertyInfo(Variant::OBJECT, "script_mesh", PROPERTY_HINT_RESOURCE_TYPE, StringName("ScriptMesh")), "set_script_mesh", "get_script_mesh");

	ClassDB::bind_method(D_METHOD("get_physics_body_path"), &ScriptMeshInstance::get_physics_body_path);
	ClassDB::bind_method(D_METHOD("set_physics_body_path"), &ScriptMeshInstance::set_physics_body_path);
	ClassDB::add_property("ScriptMeshInstance", PropertyInfo(Variant::NODE_PATH, "physics_body_path", PROPERTY_HINT_NODE_TYPE, StringName("PhysicsBody3D")), "set_physics_body_path", "get_physics_body_path");

	ClassDB::bind_method(D_METHOD("get_physics_body"), &ScriptMeshInstance::get_physics_body);
}

ScriptMeshInstance::ScriptMeshInstance() {
	script_mesh = Variant(nullptr);
}

ScriptMeshInstance::~ScriptMeshInstance() {}

void ScriptMeshInstance::build(){
	// make sure there is no mesh if we're setting the script_mesh to null.
	// so it makes sense when somebody clears the script_mesh.
	if(script_mesh.is_null()){
		set_mesh(nullptr);
		return;
	}
	
	Ref<ScriptMeshBuilder> builder = memnew(ScriptMeshBuilder);
	builder->set_instance(this);

	// try to call "build" on the ScriptMesh
	if(script_mesh->has_method("build")){
		script_mesh->call("build", builder);
	}else{
		UtilityFunctions::print("Your ScriptMesh must override the build(ScriptMeshBuilder) method.");
		return;
	}

	// don't do anything if the script didn't provide any parts:
	if(builder->get_parts_count() <= 0){
		return;
	}

	// create or clear the ArrayMesh
	Ref<ArrayMesh> mesh = (Ref<ArrayMesh>)get_mesh();
	if(mesh.is_null()){
		mesh = (Ref<ArrayMesh>)memnew(ArrayMesh);
	}else{
		mesh->clear_surfaces();
	}

	// add all surfaces to the ArrayMesh
	int surface_count = builder->get_surface_count();
	for(int i = 0; i < surface_count; i++){
		Array surface_arrays = builder->get_arrays(i);
		mesh->add_surface_from_arrays(Mesh::PrimitiveType::PRIMITIVE_TRIANGLES, surface_arrays);
	}

	set_mesh(mesh);

	// build collision
	builder->build_shapes(get_physics_body());
}

Ref<ScriptMesh> ScriptMeshInstance::get_script_mesh() const{
	return script_mesh;
}
void ScriptMeshInstance::set_script_mesh(Ref<ScriptMesh> new_script_mesh){
	script_mesh = new_script_mesh;

	// re-build whenever the resource changes
	if(!script_mesh.is_null()){
		script_mesh->connect("changed", Callable(this, "build"));
	}

	build();
}


NodePath ScriptMeshInstance::get_physics_body_path(){
	return physics_body_path;
}
void ScriptMeshInstance::set_physics_body_path(NodePath physics_body_path){
	this->physics_body_path = physics_body_path;
	build();
}
PhysicsBody3D* ScriptMeshInstance::get_physics_body(){
	if(physics_body_path.is_empty()){
		return nullptr;
	}else{
		Node* node = get_node_or_null(physics_body_path);
		if(node == nullptr){
			return nullptr;
		}else{
			return (PhysicsBody3D*) node;
		}
	}
}