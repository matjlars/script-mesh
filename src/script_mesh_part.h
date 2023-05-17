#ifndef SCRIPT_MESH_PART_H
#define SCRIPT_MESH_PART_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/mesh.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>

namespace godot {

	class ScriptMeshPart : public RefCounted {
		GDCLASS(ScriptMeshPart, RefCounted)

	private:
		// which surface this part is on.
		// each surface will correspond to a material in the final result
		int surface;

		// the virtual position of this part.
		// this will translate all verts
		Vector3 position;

	protected:
		static void _bind_methods();

	public:
		ScriptMeshPart();
		~ScriptMeshPart();

		// takes an array of arrays (in the ArrayMesh format)
		// and adds geometry to them
		virtual void build(Array arrays);

		int get_surface();
		void set_surface(int new_surface);

		Vector3 get_position();
		void set_position(Vector3 new_position);

		virtual void build_shape(CollisionShape3D* shape_node);
		void merge_mesh_arrays(Array array1, Array array2);
		void translate_arrays(Array arrays, Vector3 translation);
	};
}

#endif