
#include "minirt.h"

unsigned int rgbToInteger(t_color color)
{
	unsigned int intRed = (unsigned int)(color.red);
    unsigned int intGreen = (unsigned int)(color.green);
    unsigned int intBlue = (unsigned int)(color.blue);
    unsigned int intAlpha = 0;

    unsigned int result = (intAlpha << 24) | (intRed << 16) | (intGreen << 8) | intBlue;
    return result;
}


void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = rgbToInteger(color);
}



void		ray_intersects_sphere(double radius, t_ray *ray, t_sphere sphere, t_color *pixe_color)
{
	// t_vec3 *lightdir = new_vector3(-40.0,50.0,0.0);
	t_vec3 *lightdir = new_vector3(-1, -1, -1);
	double a;
	double b;
	double c;
	double delta;
	double solution;
	t_vec3 *oc = vec3_sub(ray->origin, &sphere.center);
	// set quadtratic formula parameters
	a = dot_product(ray->direction, ray->direction);
	b = 2 * dot_product(oc, ray->direction);
	c = dot_product(oc, oc) - (radius * radius);
	// calculate delta
	delta = (b * b) - (4 * a * c);
	if (delta >= 0)
	{
		// we take the smallest solution because it's the first hitpoint since we cant see from our pov the other hitpoint
		solution = (-b - sqrt(delta))/ 2 * a;
		t_vec3 *hitposition = malloc(sizeof(t_vec3));
		hitposition->x = ray->origin->x + (ray->direction->x * solution);
		hitposition->y = ray->origin->y +( ray->direction->y * solution);
		hitposition->z = ray->origin->z + (ray->direction->z * solution);
		t_vec3 *normal = normalized(lightdir);
		double light = max(dot_product(normal, negative_vec3(lightdir)), 0);
		t_vec3 *sphere_color = new_vector3(sphere.color.red, sphere.color.green, sphere.color.blue);
		t_vec3 *multi = multiply_vec3_number(sphere_color, light);
		// pixe_color->red = ((int)(multi->x * 0.5 + 0.5)) * 255;
		// pixe_color->green = ((int)(multi->y * 0.5 + 0.5)) * 255;
		// pixe_color->blue = ((int)(multi->z * 0.5 + 0.5)) * 255;
		// pixe_color->red = (normal->x * 0.5 + 0.5) * 255;
		// pixe_color->green = (normal->y * 0.5 + 0.5) * 255;
		// pixe_color->blue = (normal->z * 0.5 + 0.5) * 255;
		hitposition = normalized(hitposition);
		pixe_color->red = ((hitposition->x * 0.5 + 0.5)) * 255;
		pixe_color->green = ((hitposition->y * 0.5 + 0.5)) * 255;
		pixe_color->blue = ((hitposition->z * 0.5 + 0.5)) * 255;
		} 
}

t_color	trace_ray(t_ray *ray, t_scene scene)
{
	t_color	background_color;
	t_color	pixel_color;

	background_color = (t_color){0, 0, 0}; // Background color (black)
	pixel_color = background_color;
	ray_intersects_sphere(scene.sphere.radius , ray, scene.sphere, &pixel_color);
	return (pixel_color);
}

double degrees_to_radians(double degrees)
{
    return degrees * M_PI / 180.0;
}

void	render_image(t_scene scene, void *mlx_ptr, void *win_ptr, t_data *data)
{
	int		x;
	int		y;
	t_ray	*ray;
	t_color	pixel_color;
	t_vec2 coord;

	y = 0;
	ray = malloc(sizeof(t_ray));
	double fov = 70;
	ray->origin = new_vector3(0 , 0 , -1);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			// this calculations to make the ray hit the center of the pixel 
			coord.x = (double) x / WIDTH;
			coord.y = (double) y / WIDTH;
			coord.x = coord.x * 2 - 1;
			coord.y = coord.y * 2 - 1;
			// coord.x = (double)x / (double)(WIDTH - 1);
            // coord.y = (double)y / (double)(HEIGHT - 1);
			ray->direction = new_vector3(coord.x, coord.y, -1); // orientation vector , look subject
			// i dont normalize cuz it affets performance hehe
			pixel_color = trace_ray(ray, scene);
			// put_pixel_to_image(data->img, x, y, pixel_color);
			my_mlx_pixel_put(data, x, y, pixel_color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx_ptr, win_ptr, data->img, 0, 0);
}

int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	t_data	img;
	t_scene	scene;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Raytracer");
	img.img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	scene.sphere.center = (t_vec3){0, 0, 0}; // Sphere position
	scene.sphere.radius = 0.5; // Sphere radius
	scene.sphere.color = (t_color){10,0,255}; // Sphere color according to subject
	render_image(scene, mlx_ptr, win_ptr, &img);
	mlx_loop(mlx_ptr);
	return (0);
}


// vectors: corss dot normileze normilized operatios : */ -+ with other vectors and numbers | lenght = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))

// x = a2 + b2.t 

// r^2 = x^2 + y^y + z^2
// => r^2 = (a2.x + b2.x*t) +  (a2.y + b2.y*t) + (a2.z + b2.z*t);
