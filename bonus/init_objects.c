#include "header.h"


// t_object get_floor(t_vars *vars)
// {
// 	t_object plane;
//
// 	plane.type = PLANE;
// 	plane.base_color = (t_vec3) {0.5, 0.3, 0.5};
// 	plane.d_normal = (t_vec3) {0, 0, 1};
// 	plane.has_material = 0;
// 	plane.has_texture = 1;
// 	plane.has_bump = 1;
// 	plane.reflectivity = 0;
// 	plane.shininess = 10;
// 	plane.intersect = test_plane;
// 	plane.translation = (t_vec3) {0, 0, 0};
// 	plane.imgnormal.img = mlx_xpm_file_to_image(vars->mlx_ptr, "assets/normals/brick_bump.xpm", &plane.imgnormal.width, &plane.imgnormal.height);
// 	plane.imgnormal.addr = mlx_get_data_addr(plane.imgnormal.img, &plane.imgnormal.bits_per_pixel, &plane.imgnormal.line_length,
// 								&plane.imgnormal.endian);
// 	t_vec2 m = (t_vec2) {1, 1};
// 	plane.checker_matrix = set_transform_checker(&m);
// 	return (plane);
// }
//
// t_object get_right()
// {
// 	t_object plane;
//
// 	plane.type = PLANE;
// 	plane.base_color = (t_vec3) {0.4, 0.22, 0.53};
// 	plane.d_normal = (t_vec3) {-1, 0, 0};
// 	plane.has_material = 0;
// 	plane.has_texture = 0;
// 	plane.has_bump = 0;
// 	plane.reflectivity = 0;
// 	plane.shininess = 10;
// 	plane.intersect = test_plane;
// 	plane.translation = (t_vec3) {1, 0, 0};
// 	return (plane);
// }
//
// t_object get_left()
// {
// 	t_object plane;
//
// 	plane.type = PLANE;
// 	plane.base_color = (t_vec3) {0.490, 0.24, 0.31};
// 	plane.d_normal = (t_vec3) {1, 0, 0};
// 	plane.has_material = 0;
// 	plane.has_texture = 0;
// 	plane.has_bump = 0;
// 	plane.reflectivity = 0;
// 	plane.shininess = 10;
// 	plane.intersect = test_plane;
// 	plane.translation = (t_vec3) {-1, 0, 0};
// 	return (plane);
// }
//
// t_object get_up()
// {
// 	t_object plane;
//
// 	plane.type = PLANE;
// 	plane.base_color = (t_vec3) {1, 1, 1};
// 	plane.d_normal = (t_vec3) {0, 0, 1};
// 	plane.has_material = 0;
// 	plane.has_texture = 0;
// 	plane.has_bump = 0;
// 	plane.reflectivity = 0;
// 	plane.shininess = 10;
// 	plane.intersect = test_plane;
// 	plane.translation = (t_vec3) {0, 0, -2};
// 	return (plane);
// }
//
// t_object get_front()
// {
// 	t_object plane;
//
// 	plane.type = PLANE;
// 	plane.base_color = (t_vec3) {0.42, 0.42, 0.22};
// 	plane.d_normal = (t_vec3) {0, -1, 0};
// 	plane.has_material = 0;
// 	plane.has_texture = 0;
// 	plane.has_bump = 0;
// 	plane.reflectivity = 0;
// 	plane.shininess = 10;
// 	plane.intersect = test_plane;
// 	plane.translation = (t_vec3) {0, 0.5, 0};
// 	return (plane);
// }
//
// t_object get_sphere1()
// {
// 	t_object sphere;
//
// 	sphere.type = SPHERE;
// 	sphere.base_color = (t_vec3) {1, 0, 0.8};
// 	sphere.has_material = 1;
// 	sphere.reflectivity = 0.89;
// 	sphere.has_texture = 0;
// 	sphere.has_bump = 0;
// 	sphere.shininess = 20;
// 	sphere.intersect = test_sphere;
// 	sphere.radius = 0.25;
// 	sphere.scale = (t_vec3) {sphere.radius, sphere.radius, sphere.radius};
// 	sphere.rotation = (t_vec3) {0, 0, 0};
// 	sphere.translation = (t_vec3) {0, 0, -1};
// 	sphere.gtfm = set_transform(&sphere.translation, &sphere.rotation, &sphere.scale);
// 	return (sphere);
// }
//
// t_object get_sphere2(t_vars *vars)
// {
// 	t_object sphere;
//
// 	sphere.type = SPHERE;
// 	sphere.base_color = (t_vec3) {0.75, 0, 0.75};
// 	sphere.has_material = 1;
// 	sphere.has_texture = 0;
// 	sphere.reflectivity = 1;
// 	sphere.has_bump = 0;
// 	sphere.shininess = 50;
// 	sphere.intersect = test_sphere;
// 	sphere.radius = 0.25;
// 	sphere.d_normal = (t_vec3) {0, 0, -1};
// 	sphere.scale = (t_vec3) {sphere.radius, sphere.radius, sphere.radius};
// 	sphere.rotation = (t_vec3) {0, 0, 0};
// 	sphere.translation = (t_vec3) {-0.5, 0, -0.5};
// 	sphere.gtfm = set_transform(&sphere.translation, &sphere.rotation, &sphere.scale);
// 	sphere.imgnormal.img = mlx_xpm_file_to_image(vars->mlx_ptr, "assets/normals/earthnormal.xpm", &sphere.imgnormal.width, &sphere.imgnormal.height);
// 	sphere.imgnormal.addr = mlx_get_data_addr(sphere.imgnormal.img, &sphere.imgnormal.bits_per_pixel, &sphere.imgnormal.line_length,
// 								&sphere.imgnormal.endian);
// 	sphere.image.img = mlx_xpm_file_to_image(vars->mlx_ptr, "assets/textures/earth.xpm", &sphere.image.width, &sphere.image.height);
// 	sphere.image.addr = mlx_get_data_addr(sphere.image.img, &sphere.image.bits_per_pixel, &sphere.image.line_length,
// 								&sphere.image.endian);
// 	t_vec2 m = (t_vec2) {10, 10};
// 	sphere.checker_matrix = set_transform_checker(&m);
// 	return (sphere);
// }
//
//
// t_object *init_objects(t_vars *vars)
// {
// 	t_object *objects = calloc(1, sizeof(t_object) * OBJ_COUNT);
// 	objects[0] = get_floor(vars);
// 	objects[1] = get_left();
// 	objects[2] = get_right();
// 	objects[3] = get_up();
// 	objects[4] = get_sphere1();
// 	objects[5] = get_sphere2(vars);
// 	objects[6] = get_front();
//
// 	return (objects);
// }
//
// t_light *init_light()
// {
// 	t_light *lights;
//
// 	lights = malloc(sizeof(t_light) * 1);
//
// 	lights[0].position = (t_vec3) {0.75, -2, -1.5};
// 	lights[0].color = (t_vec3) {1, 1, 1};
// 	lights[0].intensity = 1;
//
// 	return (lights);
// }
static void	handle_cy(t_object *obj)
{
	obj->d_normal = normalized(obj->d_normal);
	obj->rotation = get_rotation_vector(obj->d_normal);
	obj->gtfm = set_transform(&obj->translation, &obj->rotation, &obj->scale);
	obj->intersect = test_cylinder;
}

static void handle_cone(t_object *obj)
{
  obj->d_normal = normalized(obj->d_normal);
	obj->rotation = get_rotation_vector(obj->d_normal);
	obj->gtfm = set_transform(&obj->translation, &obj->rotation, &obj->scale);
  obj->intersect = test_cone;
}

void prepare_props(t_object *e, t_vars *vars)
{
  if (e->has_texture == 1)
  {
    e->checker_matrix = set_transform_checker(&e->c_scale);
  }
  else if (e->has_texture == 2)
  {
    e->image.img = mlx_xpm_file_to_image(vars->mlx_ptr, e->texture_path, &e->image.width, &e->image.height);
    if (!e->image.img)
    {
      printf("error loading the file : %s\n", e->texture_path);
      exit(1);
    }
    e->image.addr = mlx_get_data_addr(e->image.img, &e->image.bits_per_pixel, &e->image.line_length,
								&e->image.endian);
  }
  if (e->has_bump == 1)
  {
    e->imgnormal.img = mlx_xpm_file_to_image(vars->mlx_ptr, e->bump_path, &e->imgnormal.width, &e->imgnormal.height);
    if (!e->imgnormal.img)
    {
      printf("error loading the file : %s\n", e->bump_path);
      exit(1);
    }
    e->imgnormal.addr = mlx_get_data_addr(e->imgnormal.img, &e->imgnormal.bits_per_pixel, &e->imgnormal.line_length,
          &e->imgnormal.endian);
  }
}

void	prepare_objects(t_vars *vars)
{
	int			i;
	t_object	*obj;

	i = 0;
	obj = vars->objects;
	while (i < vars->obj_count)
	{
		if (obj[i].type == SPHERE)
		{
			obj[i].rotation = (t_vec3){0, 0, 0};
			obj[i].scale = (t_vec3){obj[i].radius,
				obj[i].radius, obj[i].radius};
			obj[i].gtfm = set_transform(&obj[i].translation,
					&obj[i].rotation, &obj[i].scale);
			obj[i].intersect = test_sphere;
		}
		else if (obj[i].type == CYLINDER)
			handle_cy(&obj[i]);
    else if (obj[i].type == CONE)
      handle_cone(&obj[i]);
		else if (obj[i].type == PLANE)
		{
			obj[i].d_normal = normalized(obj[i].d_normal);
			obj[i].intersect = test_plane;
		}   
    prepare_props(&obj[i], vars);
		i++;
	}
}
