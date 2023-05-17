#include "script_mesh_part_cube.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/box_mesh.hpp>
#include <godot_cpp/classes/box_shape3d.hpp>

using namespace godot;

void ScriptMeshPartCube::_bind_methods() {
	ClassDB::bind_method(D_METHOD("build"), &ScriptMeshPartCube::build);

	ClassDB::bind_method(D_METHOD("set_size"), &ScriptMeshPartCube::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &ScriptMeshPartCube::get_size);
	ClassDB::add_property("ScriptMeshPartCube", PropertyInfo(Variant::VECTOR3, "size"), "set_size", "get_size");
}

ScriptMeshPartCube::ScriptMeshPartCube() {
	size = Vector3();
}
ScriptMeshPartCube::~ScriptMeshPartCube() {}

void ScriptMeshPartCube::build(Array arrays) {
	BoxMesh box = BoxMesh();
	box.set_size(size);
	Array box_arrays = box.get_mesh_arrays();

	translate_arrays(box_arrays, get_position());
	merge_mesh_arrays(arrays, box_arrays);
	/*
	Vector3 p = get_position();
	Vector3 s = size;
	Vector3 ps = p + s;

	front_face(arrays, p, ps);
	// TODO the rest
	//back_face(arrays, p, ps);
	//left_face(arrays, p, ps);
	//right_face(arrays, p, ps);
	//top_face(arrays, p, ps);
	//bottom_face(arrays, p, ps);
	*/
}

void ScriptMeshPartCube::front_face(Array arrays, Vector3 p, Vector3 ps){
	Array indices = arrays[Mesh::ArrayType::ARRAY_VERTEX];
	int idx = indices.size();

	Array verts = arrays[Mesh::ArrayType::ARRAY_VERTEX];
	verts.append(p);
	verts.append(Vector3(p.x, ps.y, p.z));
	verts.append(Vector3(ps.x, ps.y, p.z));
	verts.append(Vector3(ps.x, p.y, p.z));

	Array uvs = arrays[Mesh::ArrayType::ARRAY_TEX_UV];
	uvs.append(Vector2(0, 0));
	uvs.append(Vector2(0, 1));
	uvs.append(Vector2(1, 1));
	uvs.append(Vector2(0, 1));

	Array normals = arrays[Mesh::ArrayType::ARRAY_NORMAL];
	normals.append(Vector3(0, 0, -1));
	normals.append(Vector3(0, 0, -1));
	normals.append(Vector3(0, 0, -1));
	normals.append(Vector3(0, 0, -1));

	indices.append(idx);
	indices.append(idx + 2);
	indices.append(idx + 1);
	indices.append(idx);
	indices.append(idx + 3);
	indices.append(idx + 2);
}


/* here's the rest of the GDScript
func back_face(arrays: Array, p: Vector3, ps: Vector3):
	var idx = arrays[Mesh.ARRAY_VERTEX].size()
	arrays[Mesh.ARRAY_VERTEX].append_array([
		Vector3(ps.x, p.y, ps.z),
		Vector3(ps.x, ps.y, ps.z),
		Vector3(p.x, ps.y, ps.z),
		Vector3(p.x, p.y, ps.z),
	])
	arrays[Mesh.ARRAY_TEX_UV].append_array([
		Vector2(0,0),
		Vector2(0,1),
		Vector2(1,1),
		Vector2(0,1),
	])

	arrays[Mesh.ARRAY_NORMAL].append_array([
		Vector3(0, 0, 1),
		Vector3(0, 0, 1),
		Vector3(0, 0, 1),
		Vector3(0, 0, 1),
	])

	arrays[Mesh.ARRAY_INDEX].append_array([
		idx, idx+2, idx+1,
		idx, idx+3, idx+2,
	])

func left_face(arrays: Array, p: Vector3, ps: Vector3):
	var idx = arrays[Mesh.ARRAY_VERTEX].size()
	arrays[Mesh.ARRAY_VERTEX].append_array([
		Vector3(p.x, p.y, ps.z),
		Vector3(p.x, ps.y, ps.z),
		Vector3(p.x, ps.y, p.z),
		Vector3(p.x, p.y, p.z),
	])
	arrays[Mesh.ARRAY_TEX_UV].append_array([
		Vector2(0,0),
		Vector2(0,1),
		Vector2(1,1),
		Vector2(0,1),
	])

	arrays[Mesh.ARRAY_NORMAL].append_array([
		Vector3(-1, 0, 0),
		Vector3(-1, 0, 0),
		Vector3(-1, 0, 0),
		Vector3(-1, 0, 0),
	])

	arrays[Mesh.ARRAY_INDEX].append_array([
		idx, idx+2, idx+1,
		idx, idx+3, idx+2,
	])

func right_face(arrays: Array, p: Vector3, ps: Vector3):
	var idx = arrays[Mesh.ARRAY_VERTEX].size()
	arrays[Mesh.ARRAY_VERTEX].append_array([
		Vector3(ps.x, p.y, p.z),
		Vector3(ps.x, ps.y, p.z),
		Vector3(ps.x, ps.y, ps.z),
		Vector3(ps.x, p.y, ps.z),
	])
	arrays[Mesh.ARRAY_TEX_UV].append_array([
		Vector2(0,0),
		Vector2(0,1),
		Vector2(1,1),
		Vector2(0,1),
	])

	arrays[Mesh.ARRAY_NORMAL].append_array([
		Vector3(1, 0, 0),
		Vector3(1, 0, 0),
		Vector3(1, 0, 0),
		Vector3(1, 0, 0),
	])

	arrays[Mesh.ARRAY_INDEX].append_array([
		idx, idx+2, idx+1,
		idx, idx+3, idx+2,
	])

func top_face(arrays: Array, p: Vector3, ps: Vector3):
	var idx = arrays[Mesh.ARRAY_VERTEX].size()
	arrays[Mesh.ARRAY_VERTEX].append_array([
		Vector3(p.x, ps.y, p.z),
		Vector3(p.x, ps.y, ps.z),
		Vector3(ps.x, ps.y, ps.z),
		Vector3(ps.x, ps.y, p.z),
	])
	arrays[Mesh.ARRAY_TEX_UV].append_array([
		Vector2(0,0),
		Vector2(0,1),
		Vector2(1,1),
		Vector2(0,1),
	])

	arrays[Mesh.ARRAY_NORMAL].append_array([
		Vector3(0, 1, 0),
		Vector3(0, 1, 0),
		Vector3(0, 1, 0),
		Vector3(0, 1, 0),
	])

	arrays[Mesh.ARRAY_INDEX].append_array([
		idx, idx+2, idx+1,
		idx, idx+3, idx+2,
	])


func bottom_face(arrays: Array, p: Vector3, ps: Vector3):
	var idx = arrays[Mesh.ARRAY_VERTEX].size()
	arrays[Mesh.ARRAY_VERTEX].append_array([
		Vector3(p.x, p.y, ps.z),
		Vector3(p.x, p.y, p.z),
		Vector3(ps.x, p.y, p.z),
		Vector3(ps.x, p.y, ps.z),
	])
	arrays[Mesh.ARRAY_TEX_UV].append_array([
		Vector2(0,0),
		Vector2(0,1),
		Vector2(1,1),
		Vector2(0,1),
	])

	arrays[Mesh.ARRAY_NORMAL].append_array([
		Vector3(0, -1, 0),
		Vector3(0, -1, 0),
		Vector3(0, -1, 0),
		Vector3(0, -1, 0),
	])

	arrays[Mesh.ARRAY_INDEX].append_array([
		idx, idx+2, idx+1,
		idx, idx+3, idx+2,
	])

*/



void ScriptMeshPartCube::build_shape(CollisionShape3D* shape_node){
	BoxShape3D* shape = memnew(BoxShape3D);
	shape->set_size(size);

	shape_node->set_position(get_position());
	shape_node->set_shape(shape);
}


void ScriptMeshPartCube::set_size(Vector3 size){
	this->size = size;
}
Vector3 ScriptMeshPartCube::get_size() const{
	return size;
}