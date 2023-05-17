#include "script_mesh_part.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void ScriptMeshPart::_bind_methods() {
	ClassDB::bind_method(D_METHOD("build"), &ScriptMeshPart::build);

	ClassDB::bind_method(D_METHOD("get_surface"), &ScriptMeshPart::get_surface);
	ClassDB::bind_method(D_METHOD("set_surface"), &ScriptMeshPart::set_surface);
	ClassDB::add_property("ScriptMeshPart", PropertyInfo(Variant::INT, "surface"), "set_surface", "get_surface");

	ClassDB::bind_method(D_METHOD("get_position"), &ScriptMeshPart::get_position);
	ClassDB::bind_method(D_METHOD("set_position"), &ScriptMeshPart::set_position);
	ClassDB::add_property("ScriptMeshPart", PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");
}

ScriptMeshPart::ScriptMeshPart() {
	surface = 0;
	position = Vector3();
}

ScriptMeshPart::~ScriptMeshPart() {}

void ScriptMeshPart::build(Array arrays) {
	UtilityFunctions::print("must override ScriptMeshPart.build()");
}
void ScriptMeshPart::build_shape(CollisionShape3D* shape_node) {
	UtilityFunctions::print("probably want to override build_shape()");
}


int ScriptMeshPart::get_surface(){
	return surface;
}
void ScriptMeshPart::set_surface(int new_surface){
	surface = new_surface;
}

Vector3 ScriptMeshPart::get_position(){
	return position;
}
void ScriptMeshPart::set_position(Vector3 new_position){
	position = new_position;
}

void ScriptMeshPart::merge_mesh_arrays(Array array1, Array array2){
	PackedVector3Array verts = array1[Mesh::ArrayType::ARRAY_VERTEX];
	PackedVector3Array normals = array1[Mesh::ArrayType::ARRAY_NORMAL];
	PackedVector2Array uvs = array1[Mesh::ArrayType::ARRAY_TEX_UV];
	PackedInt32Array indices = array1[Mesh::ArrayType::ARRAY_INDEX];
	int idx = verts.size();

	verts.append_array(array2[Mesh::ArrayType::ARRAY_VERTEX]);
	normals.append_array(array2[Mesh::ArrayType::ARRAY_NORMAL]);
	uvs.append_array(array2[Mesh::ArrayType::ARRAY_TEX_UV]);

	// add idx to all indices to make them match up with the new indices in verts array
	PackedInt32Array indices2 = array2[Mesh::ArrayType::ARRAY_INDEX];
	for(int i = 0; i < indices2.size(); i++){
		indices2[i] += idx;
	}
	indices.append_array(indices2);

	array1[Mesh::ArrayType::ARRAY_VERTEX] = verts;
	array1[Mesh::ArrayType::ARRAY_NORMAL] = normals;
	array1[Mesh::ArrayType::ARRAY_TEX_UV] = uvs;
	array1[Mesh::ArrayType::ARRAY_INDEX] = indices;
}

void ScriptMeshPart::translate_arrays(Array arrays, Vector3 translation){
	PackedVector3Array verts = arrays[Mesh::ArrayType::ARRAY_VERTEX];

	for(int i = 0; i < verts.size(); i++){
		verts[i] += translation;
	}

	arrays[Mesh::ArrayType::ARRAY_VERTEX] = verts;
}