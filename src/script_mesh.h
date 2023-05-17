#ifndef SCRIPT_MESH_H
#define SCRIPT_MESH_H

#include <godot_cpp/classes/resource.hpp>

namespace godot {

	class ScriptMesh : public Resource {
		GDCLASS(ScriptMesh, Resource)

	private:

	protected:
		static void _bind_methods();

	public:
		ScriptMesh();
		~ScriptMesh();
	};
}

#endif