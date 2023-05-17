#ifndef SCRIPT_MESH_PART_CUBE_H
#define SCRIPT_MESH_PART_CUBE_H

#include "script_mesh_part.h"

namespace godot {

	class ScriptMeshPartCube : public ScriptMeshPart {
		GDCLASS(ScriptMeshPartCube, ScriptMeshPart)

	private:
		Vector3 size;
		void front_face(Array arrays, Vector3 p, Vector3 ps);
		//back_face(arrays, p, ps);
		//left_face(arrays, p, ps);
		//right_face(arrays, p, ps);
		//top_face(arrays, p, ps);
		//bottom_face(arrays, p, ps);

	protected:
		static void _bind_methods();

	public:
		ScriptMeshPartCube();
		~ScriptMeshPartCube();

		virtual void build(Array arrays);
		virtual void build_shape(CollisionShape3D* shape_node);

		void set_size(Vector3 size);
		Vector3 get_size() const;
	};
}

#endif