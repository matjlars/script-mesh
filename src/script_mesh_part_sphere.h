#ifndef SCRIPT_MESH_PART_SPHERE_H
#define SCRIPT_MESH_PART_SPHERE_H

#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>
#include "script_mesh_part.h"

namespace godot {

	class ScriptMeshPartSphere : public ScriptMeshPart {
		GDCLASS(ScriptMeshPartSphere, ScriptMeshPart)

	private:
		double radius;
		int stacks;
		int slices;

		void build_uv_sphere(Array arrays);
		void build_built_in_sphere(Array arrays);

	protected:
		static void _bind_methods();

	public:
		ScriptMeshPartSphere();
		~ScriptMeshPartSphere();

		virtual void build(Array arrays);

		void set_radius(double radius);
		double get_radius();

		void set_stacks(int stacks);
		int get_stacks();

		void set_slices(int slices);
		int get_slices();

		void build_shape(CollisionShape3D* shape_node);
	};
}

#endif