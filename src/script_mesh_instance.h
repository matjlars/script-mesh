#ifndef SCRIPT_MESH_INSTANCE_H
#define SCRIPT_MESH_INSTANCE_H

#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/array_mesh.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/physics_body3d.hpp>
#include "script_mesh.h"

namespace godot {

	class ScriptMeshInstance : public MeshInstance3D {
		GDCLASS(ScriptMeshInstance, MeshInstance3D)

	private:
		Ref<ScriptMesh> script_mesh;
		NodePath physics_body_path;

	protected:
		static void _bind_methods();

	public:
		ScriptMeshInstance();
		~ScriptMeshInstance();
		void build();

		Ref<ScriptMesh> get_script_mesh() const;
		void set_script_mesh(Ref<ScriptMesh> script_mesh);

		NodePath get_physics_body_path();
		void set_physics_body_path(NodePath physics_body_path);
		PhysicsBody3D *get_physics_body();
	};
}

#endif