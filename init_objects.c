#include "header.h"


t_object *init_objects()
{
	t_object *objects = malloc(sizeof(t_object) * 3);

	objects[0].type = PLANE;
	objects[0].base_color = (t_vec3) {1, 1, 1};
	objects[0].translation = (t_vec3) {0, 0, 0};
	objects[0].d_normal = (t_vec3) {0, 0, 1};
	objects[0].intersect = test_plane;
	
	objects[1].type = SPHERE;
	objects[1].base_color = (t_vec3) {0.8, 0, 0.8};
	objects[1].radius = 0.75;
	objects[1].translation = (t_vec3) {-1.5, 0, -3};
	objects[1].rotation = (t_vec3) {0, 0, 0};
	objects[1].scale = (t_vec3) {objects[1].radius, objects[1].radius, objects[1].radius};
	objects[1].gtfm = set_transform(&objects[1].translation, &objects[1].rotation, &objects[1].scale);
	objects[1].intersect = test_sphere;

	objects[2].type = CYLINDER;
	objects[2].base_color = (t_vec3) {1, 0, 0.0};
	objects[2].radius = 0.75;
	objects[2].d_normal = (t_vec3) {0, 1, 0};
	objects[2].translation = (t_vec3) {1.5, 0, -1.5};
	objects[2].rotation = get_rotation_vector(objects[2].d_normal);
	objects[2].scale = (t_vec3) {0.5, 0.5, 1.5};
	objects[2].gtfm = set_transform(&objects[2].translation, &objects[2].rotation, &objects[2].scale);
	objects[2].intersect = test_cylinder;

	return (objects);
}

t_light *init_light()
{
	t_light *lights;

	lights = malloc(sizeof(t_light) * 1);

	lights[0].position = (t_vec3) {5, -10, -5};
	lights[0].color = (t_vec3) {1, 1, 1};
	lights[0].intensity = 1;
	return (lights);
}