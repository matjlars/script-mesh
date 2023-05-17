@tool
extends ScriptMesh
class_name SMTree

@export var trunk_height: float = 1.0:
	set(val):
		trunk_height = val
		emit_changed()

@export var trunk_width: float = 0.2:
	set(val):
		trunk_width = val
		emit_changed()

@export var leaves_radius: float = 1.0:
	set(val):
		leaves_radius = val
		emit_changed()

func build(builder: ScriptMeshBuilder):
	var trunk = builder.cube()
	trunk.position = Vector3(0, trunk_height/2.0, 0)
	trunk.size = Vector3(trunk_width, trunk_height, trunk_width)
	
	var leaves = builder.sphere()
	leaves.position = Vector3(0, trunk_height + leaves_radius, 0)
	leaves.surface = 1
	leaves.radius = leaves_radius
