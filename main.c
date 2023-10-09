
#include "minirt.h"

unsigned int rgbToInteger(t_vec3 *color)
{
	int red = color->x;
	int green = color->y;
	int blue = color->z;
    unsigned int result = (red << 16) | (green << 8) | blue;
    return result;
}



int		main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	img;
	// t_scene	scene;
	t_camera *camera;
	t_image *image = new_image();

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Raytracer");
	img.img = mlx_new_image(mlx_ptr, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,&img.endian);
	camera = malloc(sizeof(t_camera));
	initialize_camera(camera);
	update_camera(camera);
	t_light *light_list = init_light();
	t_object *objects = init_objects();
	t_vec3 *hitposition = new_vector3(0,0,0);
	t_vec3 *localnormal = new_vector3(0,0,0);
	t_vec3 *localcolor = new_vector3(0,0,0);
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
			int i = 0;
			int intfound = 0;
			while (i < 2)
			{
				if (objects[i].type == PLANE && test_intersect_plane(ray, objects[i].gtfm, hitposition,
					localnormal, localcolor))
					intfound = 1;
				else if (objects[i].type == SPHERE && intersect_sphere(ray, objects[i].gtfm,
					hitposition, localnormal, localcolor))
					intfound = 1;
				i++;
			}
			if (intfound)
			{
				double intensity;
				t_vec3 *color = new_vector3(0.0, 0.0, 0.0);
				int validillum;
				validillum = compute_illumination(light_list, hitposition, color, &intensity);
				if (validillum)
				{
					t_vec3 *temp = multiply_vec3_number(objects[1].base_color, intensity);
					set_pixel(image, temp, x, y);
					free(temp);
				}
			}
			x++;
		}
		y++;
	}
	render(image, mlx_ptr, win_ptr);
	printf("done\n");
	mlx_loop(mlx_ptr);
	return (0);
}


// vectors: corss dot normileze normilized operatios : */ -+ with other vectors and numbers | lenght = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2))

// x = a2 + b2.t 

// r^2 = x^2 + y^y + z^2
// => r^2 = (a2.x + b2.x*t) +  (a2.y + b2.y*t) + (a2.z + b2.z*t);
