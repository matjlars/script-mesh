#include "register_types.h"

#include "script_mesh_part.h"
#include "script_mesh_part_cube.h"
#include "script_mesh_part_sphere.h"
#include "script_mesh_builder.h"
#include "script_mesh_instance.h"
#include "script_mesh.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_script_mesh_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<ScriptMeshPart>(true);
	ClassDB::register_class<ScriptMeshPartCube>();
	ClassDB::register_class<ScriptMeshPartSphere>();
	ClassDB::register_class<ScriptMeshBuilder>();
	ClassDB::register_class<ScriptMesh>(true);
	ClassDB::register_class<ScriptMeshInstance>();
}

void uninitialize_script_mesh_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
	// Initialization.
	GDExtensionBool GDE_EXPORT script_mesh_library_init(const GDExtensionInterface* p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization) {
		godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

		init_obj.register_initializer(initialize_script_mesh_module);
		init_obj.register_terminator(uninitialize_script_mesh_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}