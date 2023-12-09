#include "header.h"


void init_camera(t_camera *cam)
{
	cam->origin = (t_vec3) {-10, -10.0, -2};
	cam->lookat = (t_vec3) {0, 0, 0};
	cam->up_vector = (t_vec3) {0, 0, 1};

	cam->aspect_ratio = (float) WIDTH / (float) HEIGHT;
	cam->fov = 15;
	float rad_fov = cam->fov * M_PI / 180.0;
	cam->focal_length = 1.0;
	cam->hor_size = 2.0 * cam->focal_length * tan(rad_fov / 2.0);
	cam->cam_w = normalized(vec_sub(&cam->lookat, &cam->origin));
	cam->cam_u = normalized(cross(&cam->cam_w, &cam->up_vector));
	cam->cam_v = normalized(cross(&cam->cam_u, &cam->cam_w));

	t_vec3 scaled = scale_vector(&cam->cam_w, cam->focal_length);
	cam->screen_center = vec_add(&cam->origin, &scaled);

	cam->screen_u = scale_vector(&cam->cam_u, cam->hor_size);
	cam->screen_v = scale_vector(&cam->cam_v, cam->hor_size / cam->aspect_ratio);
}

t_ray new_ray(t_vec3 point1, t_vec3 point2)
{
	t_ray ray;

	ray.point1 = point1;
	ray.point2 = point2;
	ray.dir = vec_sub(&point2, &point1);
	return (ray);
}

t_ray generate_ray(float x, float y, t_camera *cam)
{
	t_vec3 scaled_u = scale_vector(&cam->screen_u, x);
	t_vec3 scaled_v = scale_vector(&cam->screen_v, y);
	t_vec3 part1 = vec_add(&cam->screen_center, &scaled_u);
	t_vec3 part2 = vec_add(&part1, &scaled_v);

	return (new_ray(cam->origin, part2));
}

