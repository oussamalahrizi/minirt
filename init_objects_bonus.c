#include "header.h"

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
