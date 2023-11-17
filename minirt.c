#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx_linux/mlx.h"
#include <stdint.h>
#include <math.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct s_vec3
{
	float x;
	float y;
	float z;
} t_vec3;


t_vec3 scale(t_vec3 a, float b)
{
	return (t_vec3){a.x * b, a.y * b, a.z * b};
}

float dot(t_vec3 a, t_vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float length(t_vec3 a)
{
	return sqrtf(a.x * a.x + a.y * a.y + a.z * a.z);
}
t_vec3 noz(t_vec3 a)
{
	return scale(a, 1.f / length(a));
}

t_vec3 vec_add(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 vec_sub(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3 vec_mul(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

t_vec3 cross(t_vec3 a, t_vec3 b)
{
	return (t_vec3){a.y * b.z - a.z * b.y,
					a.z * b.x - a.x * b.z,
					a.x * b.y - a.y * b.x};
	//new_v->x = (v1->y * v2->z) - (v1->z * v2->y);
	//new_v->y = (v1->z * v2->x) - (v1->x * v2->z);
	//new_v->z = (v1->x * v2->y) - (v1->y * v2->x);
}

t_vec3 camera;
t_vec3 cam_dir;
t_vec3 cam_w, cam_u, cam_v;

float width;
float height;

float focal_length = 1;

uint32_t *pixels;

void *mlx, *window, *image;

int init = 0;


enum {
	SPHERE,
	PLANE,
};

typedef struct s_obj
{
	int type;

	t_vec3 center;
	float radius;
	t_vec3 normal;
	float d;
	t_vec3 color;
} t_obj;

t_obj objects[] = {
	{.type = SPHERE, .center = {}, .radius = 0.5, .color = {1, 0, 0}},
	{.type = SPHERE, .center = {-1, 0, 0}, .radius = 0.5, .color = {1, 0, 0}},
	{.type = SPHERE, .center = {1, 0, 0}, .radius = 0.5, .color = {1, 0, 0}},

	{.type = PLANE, .normal = {0, 1, 0}, .d = 0.5, .color = {0.7, 0.7, 0.7}}
};

t_vec3 light_p = {2, 2, 2};
t_vec3 light_color = {1, 1, 1};

#include <float.h>

#define MIN_T 0.001

float get_closest_object(t_vec3 ray_org, t_vec3 ray_dir, int *hit_index)
{
	int object_count = sizeof(objects) / sizeof(*objects);

	*hit_index = -1;
	float closest = FLT_MAX;
	for (int i = 0; i < object_count; i++)
	{
		t_obj *e = &objects[i];

		if (e->type == SPHERE)
		{
			t_vec3 oc = vec_sub(ray_org ,e->center);
			float a = dot(ray_dir, ray_dir);
			float b = 2.0 * dot(oc, ray_dir);
			float c = dot(oc, oc) - e->radius*e->radius;
			float d = b*b - 4*a*c;
			if (d >= 0)
			{
				d = sqrtf(d);
				float t0 = (-b + d) / (2 * a);
				float t1 = (-b - d) / (2 * a);
				float t = -1;

				if (t0 > MIN_T && t0 < closest)
					t = t0;
				if (t1 > MIN_T && (t < 0 || t1 < t0))
					t = t1;
				if (t != -1)
				{
					closest = t;
					*hit_index = i;
				}
			}
		}
		else if (e->type == PLANE)
		{
			// P*N + d = 0
			// (O + t * D)*N + d = 0
			// t = (-d - O*N) / (D*N)
			float denom = dot(ray_dir, e->normal);
			if (fabsf(denom) > 0.0001f)
			{
				float t = (-e->d - dot(ray_org, e->normal)) / denom;

				if (t > MIN_T && t < closest)
				{
					closest = t;
					*hit_index = i;
				}
			}
			
		}
	}
	return closest;
}

t_vec3 raytrace(t_vec3 ray_org, t_vec3 ray_dir)
{
	int hit_index;
	float closest = get_closest_object(ray_org, ray_dir, &hit_index);
	if (hit_index == -1)
		return (t_vec3){0.5, 0.5, 0.5};
	t_vec3 p = vec_add(ray_org, scale(ray_dir, closest));

	t_vec3 normal;
	t_obj *e = &objects[hit_index];
	if (e->type == SPHERE)
		normal = vec_sub(p, e->center);
	else if (e->type == PLANE)
		normal = e->normal;

	t_vec3 to_light = noz(vec_sub(light_p, p));
	t_vec3 ambient = {0.3, 0.5, 0.6};

	float diffuse = fmaxf(dot(to_light, normal), 0);

	int hit_index2;
	float closest2 = get_closest_object(p, to_light, &hit_index2);
	if (closest2 < length(vec_sub(p, light_p)))
		diffuse = 0;

	return vec_mul(objects[hit_index].color, vec_add(ambient, scale(light_color, diffuse)));
}

int loop(void *data)
{
	if (!init)
	{
		camera = (t_vec3){0, 0, 5}; // origin
		cam_dir = (t_vec3){0, 0, 0}; // look at
		t_vec3 up = (t_vec3){0, 0, 1}; // up vector
		
		cam_dir = noz(cam_dir);
		cam_w = noz(scale(cam_dir, -1));
		cam_u = noz(cross(up, cam_w));
		cam_v = noz(cross(cam_w, cam_u));

		float fov = 45;
		width = tan(fov / 2) * 2 * focal_length;
		height = (width * HEIGHT) / (float) WIDTH;
		init = 1;
	}

	for (int y = 0; y < HEIGHT; y++)
	{
		float fy = ((float)y / HEIGHT) * 2 - 1;
		for (int x = 0; x < WIDTH; x++)
		{
			float fx = ((float)x / WIDTH) * 2 - 1;
			t_vec3 pixel_p = vec_add(scale(cam_u, fx * width * 0.5f),
									 scale(cam_v, fy * height * 0.5f));
			pixel_p = vec_add(pixel_p, scale(cam_w, -focal_length));
			pixel_p = vec_add(pixel_p, camera);
			
			t_vec3 color = raytrace(camera, vec_sub(pixel_p, camera));

			if (color.x > 1) color.x = 1;
			if (color.y > 1) color.y = 1;
			if (color.z > 1) color.z = 1;

			uint32_t color32 = ((uint32_t)(color.x * 255 + 0.5) << 16)
				| ((uint32_t)(color.y * 255 + 0.5) << 8)
				| ((uint32_t)(color.z * 255 + 0.5));
			*(pixels + (HEIGHT - y - 1) * WIDTH + x) = color32;
		}
	}
	mlx_put_image_to_window(mlx, window, image, 0, 0);
}

int main()
{
	mlx = mlx_init();

	window = mlx_new_window(mlx, WIDTH, HEIGHT, "a");

	int bits_per_pixel;
	int line_length;
	int endian;
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
    pixels = (uint32_t *)mlx_get_data_addr(image, &bits_per_pixel, &line_length,
                                        &endian);
	
	mlx_loop_hook(mlx, loop, 0);
	mlx_loop(mlx);
}