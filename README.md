# ScriptMesh
A Godot GDExtension that lets you use GDScript to more easily generate procedural models.

## Installation
TODO. Figure out how to install a GDExtension. It might just be copying the files in demo/bin into your project's "res://bin/"



## Why?
Godot already has ArrayMesh, SurfaceTool, MeshDataTool, ImmediateMesh, ahhh!!

So why would I go and add another thing to that long list??

There are three reasons why I made this, and prefer it over the existing ones:
1. Dev Time. I made it easy to get a result very fast.
1. Iteration. You can change parameters and see it change right in your scene as you are changing it.
1. Collision. This tool can automatically generate collision shapes very easily.


## New Concept: Parts
A new concept in this extension is a "Part". A part is a subset of a surface. So multiple parts can make up a single surface. This is handy for if multiple parts can share a material.

When you make a mesh, you use the ScriptMeshBuilder to create Parts. For example, calling `builder.cube()` returns a ScriptMeshPartCube object that is Part. All the parts you make for a given mesh are automatically combined into a single mesh for you.


## Surfaces
All meshes consist of at least 1 surface. A surface corresponds to a Material slot in the Godot inspector.

If you do nothing with surfaces, this tool assumes all your Parts should be the same surface, meaning all parts share a material.

If you wish to have multiple materials, simply specify a surface of > 0. 0 is the default.

For an example of multiple surface, check out `demo/tree.gd`

The only line you need to put the leaves part on another surface is the `leaves.surface = 1`


## Usage
The simplest example, making the default cube, looks like this:

```GDScript
@tool
extends ScriptMesh
class_name SMExample1

func build(b: ScriptMeshBuilder):
	b.cube()

```

Notes: it needs `@tool`. It also needs a class name. It sort of works without a class name but selecting it in the inspector is a bit jank.

Here is a slightly more useful example that moves the cube up a bit so the cube rests on the floor.

```GDScript
@tool
extends ScriptMesh
class_name SMExample2

func build(b: ScriptMeshBuilder):
	var cube = b.cube()
	cube.position = Vector3(0, 0.5, 0)
```



Here is an even better example where you can easily control the size of the cube from the editor
```GDScript
@tool
extends ScriptMesh
class_name SMExample3

@export var size: float = 1.0

func build(b: ScriptMeshBuilder):
	var cube = b.cube()
	cube.position = Vector3(0, size/2, 0)
	cube.size = Vector3(size, size, size)
```

For slightly more sophisticated examples, see the scripts in the "demo" folder.
