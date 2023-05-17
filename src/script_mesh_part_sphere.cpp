#include "script_mesh_part_sphere.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/sphere_shape3d.hpp>
#include <godot_cpp/classes/sphere_mesh.hpp>

using namespace godot;

void ScriptMeshPartSphere::_bind_methods() {
	ClassDB::bind_method(D_METHOD("build"), &ScriptMeshPartSphere::build);

	ClassDB::bind_method(D_METHOD("set_radius"), &ScriptMeshPartSphere::set_radius);
	ClassDB::bind_method(D_METHOD("get_radius"), &ScriptMeshPartSphere::get_radius);
	ClassDB::add_property("ScriptMeshPartSphere", PropertyInfo(Variant::FLOAT, "radius"), "set_radius", "get_radius");

	ClassDB::bind_method(D_METHOD("set_stacks"), &ScriptMeshPartSphere::set_stacks);
	ClassDB::bind_method(D_METHOD("get_stacks"), &ScriptMeshPartSphere::get_stacks);
	ClassDB::add_property("ScriptMeshPartSphere", PropertyInfo(Variant::INT, "stacks"), "set_stacks", "get_stacks");

	ClassDB::bind_method(D_METHOD("set_slices"), &ScriptMeshPartSphere::set_slices);
	ClassDB::bind_method(D_METHOD("get_slices"), &ScriptMeshPartSphere::get_slices);
	ClassDB::add_property("ScriptMeshPartSphere", PropertyInfo(Variant::INT, "slices"), "set_slices", "get_slices");
}

ScriptMeshPartSphere::ScriptMeshPartSphere() {
	radius = 0.5;
	stacks = 6;
	slices = 12;
}
ScriptMeshPartSphere::~ScriptMeshPartSphere() {}

void ScriptMeshPartSphere::build(Array arrays) {
	build_uv_sphere(arrays);
	//build_built_in_sphere(arrays);
}

// algo learned at https://www.danielsieger.com/blog/2021/03/27/generating-spheres.html
void ScriptMeshPartSphere::build_uv_sphere(Array arrays){
	PackedVector3Array verts = arrays[Mesh::ArrayType::ARRAY_VERTEX];
	PackedVector3Array normals = arrays[Mesh::ArrayType::ARRAY_NORMAL];
	PackedVector2Array uvs = arrays[Mesh::ArrayType::ARRAY_TEX_UV];
	PackedInt32Array indices = arrays[Mesh::ArrayType::ARRAY_INDEX];
	int idx = verts.size();

	// top vert
	verts.append(get_position() + Vector3(0, radius, 0));
	normals.append(Vector3(0,1,0));
	uvs.append(Vector2(0,0));

	// middle verts
	for(int i = 0; i < stacks-1; i++){
		float phi = Math_PI * float(i+1) / float(stacks);
		for(int j = 0; j < slices; j++){
			float theta = Math_TAU * float(j) / float(slices);
			
			Vector3 vert = Vector3(
				sin(phi) * cos(theta),
				cos(phi),
				sin(phi) * sin(theta)
			);
			vert *= radius;
			verts.append(vert + get_position());
			normals.append(vert.normalized());
			uvs.append(Vector2(0,0));
		}
	}

	// bottom vert
	verts.append(get_position() + Vector3(0, -radius, 0));
	normals.append(Vector3(0,-1,0));
	uvs.append(Vector2(0,0));

	// add top/bottom tris:
	for(int i = 0; i < slices; i++){
		// top
		int i0 = i + 1;
		int i1 = ((i+1) % slices) + 1;
		indices.append(idx);
		indices.append(idx+i0);
		indices.append(idx+i1);
		
		// bottom
		i0 = i + (slices * (stacks - 2)) + 1;
		i1 = ((i+1) % slices) + (slices * (stacks - 2)) + 1;
		int last_idx = idx + (slices * (stacks-1)) + 1;
		indices.append(last_idx);
		indices.append(idx+i1);
		indices.append(idx+i0);
	}

	// add quads for stacks/slices
	for(int j = 0; j < stacks-2; j++){
		int j0 = j * slices + 1;
		int j1 = (j + 1) * slices + 1;
		for(int i = 0; i < slices; i++){
			int i0 = j0 + i;
			int i1 = j0 + ((i+1) % slices);
			int i2 = j1 + ((i+1) % slices);
			int i3 = j1 + i;
			indices.append(idx + i0);
			indices.append(idx + i3);
			indices.append(idx + i2);
			indices.append(idx + i0);
			indices.append(idx + i2);
			indices.append(idx + i1);
		}
	}

	arrays[Mesh::ArrayType::ARRAY_VERTEX] = verts;
	arrays[Mesh::ArrayType::ARRAY_NORMAL] = normals;
	arrays[Mesh::ArrayType::ARRAY_TEX_UV] = uvs;
	arrays[Mesh::ArrayType::ARRAY_INDEX] = indices;
}



void ScriptMeshPartSphere::set_radius(double new_radius){
	radius = new_radius;
}
double ScriptMeshPartSphere::get_radius(){
	return radius;
}

void ScriptMeshPartSphere::set_stacks(int new_stacks){
	stacks = new_stacks;
}
int ScriptMeshPartSphere::get_stacks(){
	return stacks;
}

void ScriptMeshPartSphere::set_slices(int new_slices){
	slices = new_slices;
}
int ScriptMeshPartSphere::get_slices(){
	return slices;
}

void ScriptMeshPartSphere::build_shape(CollisionShape3D* shape_node){
	SphereShape3D* shape = memnew(SphereShape3D);
	shape->set_radius(radius);

	shape_node->set_position(get_position());
	shape_node->set_shape(shape);
}

void ScriptMeshPartSphere::build_built_in_sphere(Array arrays){
	SphereMesh mesh = SphereMesh();
	mesh.set_height(radius * 2);
	mesh.set_radius(radius);
	mesh.set_radial_segments(slices);
	mesh.set_rings(stacks);
	
	Array sphere_arrays = mesh.get_mesh_arrays();

	translate_arrays(sphere_arrays, get_position());
	merge_mesh_arrays(arrays, sphere_arrays);
}