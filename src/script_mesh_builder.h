#ifndef SCRIPT_MESH_BUILDER_H
#define SCRIPT_MESH_BUILDER_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/physics_body3d.hpp>
#include "script_mesh_part_cube.h"
#include "script_mesh_part_sphere.h"
#include "script_mesh_instance.h"

namespace godot {

	class ScriptMeshBuilder : public RefCounted {
		GDCLASS(ScriptMeshBuilder, RefCounted)

	private:
		Array parts;
		ScriptMeshInstance* instance;

	protected:
		static void _bind_methods();

	public:
		ScriptMeshBuilder();
		~ScriptMeshBuilder();

		// shortcuts to use in _build()
		Ref<ScriptMeshPartCube> cube();
		Ref<ScriptMeshPartSphere> sphere();

		int get_parts_count();
		int get_surface_count();

		// returns the corresponding ScriptMeshInstance node
		ScriptMeshInstance* get_instance();
		void set_instance(ScriptMeshInstance* instance);

		// returns the verts, uvs, normals, and indices in an array of arrays.
		// the format matches the ArrayMesh arrays.
		Array get_arrays(int surface);

		void build_shapes(PhysicsBody3D* body);
	};
}

#endif