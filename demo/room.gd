@tool
extends ScriptMesh
class_name SMRoom

@export var width: float = 40.0:
	set(val):
		width = val
		emit_changed()

@export var length: float = 30.0:
	set(val):
		length = val
		emit_changed()

@export var wall_width: float = 1.0:
	set(val):
		wall_width = val
		emit_changed()

@export var wall_height: float = 4.0:
	set(val):
		wall_height = val
		emit_changed()

func build(b: ScriptMeshBuilder):
	var floor = b.cube()
	floor.position = Vector3(0, -wall_width/2.0, 0)
	floor.size = Vector3(width, wall_width, length)
	
	var wall_y = wall_height/2
	
	var east_wall = b.cube()
	east_wall.position = Vector3(width/2, wall_y, 0)
	east_wall.size = Vector3(wall_width, wall_height, length)
	
	var west_wall = b.cube()
	west_wall.position = Vector3(-width/2, wall_y, 0)
	west_wall.size = Vector3(wall_width, wall_height, length)
	
	var north_wall = b.cube()
	north_wall.position = Vector3(0, wall_y, -length/2)
	north_wall.size = Vector3(width, wall_height, wall_width)
	
	var south_wall = b.cube()
	south_wall.position = Vector3(0, wall_y, length/2)
	south_wall.size = Vector3(width, wall_height, wall_width)
