#include "minirt.h"

void update_camera(t_camera *camera)
{
	// get the vector from the camera position to the camera look at
	// this is the normal vector of the plan constructed by  the look at and the look up vectors
	camera->alignement_vec = vec3_sub(camera->look_at, camera->position);
	camera->alignement_vec = normalized(camera->alignement_vec);
	// calculate the u and v vectors
	camera->u = cross(camera->alignement_vec, camera->camera_up);
	camera->u = normalized(camera->u);
	camera->v = cross(camera->u, camera->alignement_vec);
	camera->v = normalized(camera->v);
	// calculate the position of the center point of the screen
	// still dont understand this
	// camera screen center = camera position + (camera length * camera alignement vector) 
	camera->alignement_vec = multiply_vec3_number(camera->alignement_vec, camera->camera_length);
	camera->screen_center = vec3_add(camera->alignement_vec, camera->position);
	// change the u and v vector to match the size and aspect ratio
	// after calculating the u and v on our world coordinates we need to update
	//them based on the parmeters given in the subject such as aspect ratio and
	//the horizontal size (fov / 180)
	camera->u = multiply_vec3_number(camera->u , camera->horizontal_size);
	camera->v = multiply_vec3_number(camera->v, (double) camera->horizontal_size / camera->aspectRatio);
}

t_ray *generate_ray(double x, double y, t_camera *camera)
{
	// world_part1 = camera->screen_center + (camera->u * x)
	t_vec3 *world_part1 = vec3_add(camera->screen_center, multiply_vec3_number(camera->u, x));
	// screen_worldcoord = world_part1 + (camera->v * y)
	t_vec3 *world_coord = vec3_add(world_part1, multiply_vec3_number(camera->v, y));
	t_ray *ray = malloc(sizeof(t_ray));
	ray->origin = new_vector3(camera->position->x, camera->position->y, camera->position->z);
	ray->direction = vec3_sub(world_coord, camera->position);
	return (ray);
}

void initialize_camera(t_camera *camera)
{
	camera->position = new_vector3(0, -10, 0);
	camera->look_at = new_vector3(0, 0, 0); // 0, 0, 1 : according to the subject
	camera->camera_up = new_vector3(0, 0, 1);
	camera->camera_length = 1;
	camera->horizontal_size = 0.25; // fov ranges from 0 to 180, and the horizontal size can range from 0 to 1 
	camera->aspectRatio = (double)WIDTH / (double)HEIGHT; //
}