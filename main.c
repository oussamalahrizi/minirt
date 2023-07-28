
#include "minirt.h"

unsigned int rgbToInteger(t_color color)
{

    unsigned int result = (color.red << 16) | (color.green << 8) | color.blue;
    return result;
}


void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = rgbToInteger(color);
}

// void		ray_intersects_sphere(double radius, t_ray *ray, t_sphere sphere, t_color *pixe_color)
// {
// 	// t_vec3 *lightdir = new_vector3(-40.0,50.0,0.0);
// 	t_vec3 *lightdir = new_vector3(-1, -1, -1);
// 	double a;
// 	double b;
// 	double c;
// 	double delta;
// 	double solution;
// 	// t_vec3 *sphere_pos = new_vector3(sphere.center.x * 2 -1, sphere.center.y * 2 -1, sphere.center.z * 2 -1);
// 	t_vec3 *oc = vec3_sub(ray->origin, &sphere.center);
// 	// set quadtratic formula parameters
// 	a = dot_product(ray->direction, ray->direction);
// 	b = 2 * dot_product(oc, ray->direction);
// 	c = dot_product(oc, oc) - (radius * radius);
// 	// calculate delta
// 	delta = (b * b) - (4 * a * c);
// 	if (delta >= 0)
// 	{
// 		// we take the smallest solution because it's the first hitpoint since we cant see from our pov the other hitpoint
// 		solution = (-(b / 2) - sqrt(delta)) / a;
// 		t_vec3 *hitposition = malloc(sizeof(t_vec3));
// 		hitposition->x = oc->x + (ray->direction->x * solution);
// 		hitposition->y = oc->y +( ray->direction->y * solution);
// 		hitposition->z = oc->z + (ray->direction->z * solution);
// 		t_vec3 *normal = normalized(hitposition);
// 		lightdir = normalized(lightdir);
// 		double d = max(dot_product(normal, negative_vec3(lightdir)), 0);
// 		t_vec3 *sphere_color = new_vector3((double)sphere.color.red / 255, (double)sphere.color.green / 255, (double)sphere.color.blue / 255);
// 		t_vec3 *multi = multiply_vec3_number(sphere_color, d);
// 		pixe_color->red = (int)(multi->x * 255 + 0.5);
// 		pixe_color->green = (int)(multi->y * 255 + 0.5);
// 		pixe_color->blue = (int)(multi->z * 255 + 0.5);
// 	} 
// }

// t_color	trace_ray(t_ray *ray, t_scene scene)
// {
// 	t_color	background_color;
// 	t_color	pixel_color;

// 	background_color = (t_color){0, 0, 0}; // Background color (black)
// 	pixel_color = background_color;
// 	ray_intersects_sphere(scene.sphere.radius , ray, scene.sphere, &pixel_color);
// 	return (pixel_color);
// }


// void	render_image(t_scene scene, void *mlx_ptr, void *win_ptr, t_data *data)
// {
// 	int		x;
// 	int		y;
// 	t_ray	*ray;
// 	t_color	pixel_color;
// 	t_vec2 coord;

// 	ray = malloc(sizeof(t_ray));
// 	ray->origin = new_vector3(-50.0, 0, 20);

// 	// ray->origin = new_vector3(ray->origin->x * 2 - 1, ray->origin->y * 2 - 1, ray->origin->z * 2 - 1);
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			coord.x = (double) x / WIDTH;
// 			coord.y = (double) y / HEIGHT;
// 			coord.x = coord.x * 2 - 1;
// 			coord.y = coord.y * 2 - 1;
// 			ray->direction = new_vector3(coord.x, coord.y, -1); // orientation vector , look subject
// 			// i dont normalize cuz it affets performance hehe 
// 			pixel_color = trace_ray(ray, scene);
// 			// put_pixel_to_image(data->img, x, y, pixel_color);
// 			my_mlx_pixel_put(data, x, y, pixel_color);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(mlx_ptr, win_ptr, data->img, 0, 0);
// }

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;
	// t_scene	scene;
	t_camera *camera;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Raytracer");
	img.img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	camera = malloc(sizeof(t_camera));
	initialize_camera(camera);
	update_camera(camera);
	printf("camera screen center :\n");
	print_vector(camera->screen_center);
	printf("camera U vector:\n");
	print_vector(camera->u);
	printf("camera V vector :\n");
	print_vector(camera->v);
	t_light *light = malloc(sizeof(t_light));
	light->position = new_vector3(5, -10, -5);
	light->color = (t_color) {255, 255, 255};
	light->intensity = 1;
	t_color sphere_color = (t_color) {10,0,255};
	t_color black_color = (t_color) {0,0,0};
	t_vec3 *hitposition = NULL;
	int y = 0;
	int x;
	t_vec3 coord;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			coord.x = ((double)x / (double) WIDTH ) * 2 - 1;
			coord.y = ((double)y / (double) HEIGHT ) * 2 - 1;
			t_ray *ray = generate_ray(coord.x, coord.y, camera);
			if (intersect_sphere(ray, &hitposition))
			{
				//compute the intensity
				double intensity;
				t_color color;
				int validillum;
				validillum = compute_illumination(light, hitposition, &color, &intensity);
				if (validillum)
				{
					sphere_color.red = intensity * sphere_color.red;
					my_mlx_pixel_put(&img, x, y, sphere_color);
				}
				else
					my_mlx_pixel_put(&img, x, y, black_color);
			}
			else
				my_mlx_pixel_put(&img, x, y, black_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, img.img, 0, 0);
	mlx_loop(mlx_ptr);
	return (0);
}


// vectors: corss dot normileze normilized operatios : */ -+ with other vectors and numbers | lenght = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))

// x = a2 + b2.t 

// r^2 = x^2 + y^y + z^2
// => r^2 = (a2.x + b2.x*t) +  (a2.y + b2.y*t) + (a2.z + b2.z*t);
