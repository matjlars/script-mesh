@tool
extends ScriptMesh
class_name SMSnowman

@export var top_radius: float = 0.4:
	set(val):
		top_radius = val
		emit_changed()

@export var mid_radius: float = 0.6:
	set(val):
		mid_radius = val
		emit_changed()

@export var bottom_radius: float = 1.0:
	set(val):
		bottom_radius = val
		emit_changed()

func build(b: ScriptMeshBuilder):
	var bottom = b.sphere()
	bottom.position = Vector3(0, bottom_radius, 0)
	bottom.radius = bottom_radius
	
	var mid = b.sphere()
	mid.position = Vector3(0, (bottom_radius*2) + mid_radius, 0)
	mid.radius = mid_radius
	
	var top = b.sphere()
	top.position = Vector3(0, (bottom_radius*2) + (mid_radius*2) + top_radius, 0)
	top.radius = top_radius
