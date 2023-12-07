#include "../header.h"

float **make_channel()
{
	float **new;
	int i;
	int j;

	i = 0;
	new = malloc(sizeof(float *) * HEIGHT);
	while (i < HEIGHT)
	{
		new[i] = malloc(sizeof(float) * WIDTH);
		j = 0;
		while (j < WIDTH)
			new[i][j++] = 0.0f;
		i++;
	}
	return (new);
}

t_image *new_image()
{
	t_image *image;

	image = malloc(sizeof(t_image));
	image->red = make_channel();
	image->green = make_channel();
	image->blue = make_channel();
	return (image);
}

float max_in_channel(float **c)
{
	int i;
	int j;
	float max;

	i = 0;
	max = -1;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if (c[i][j] > max)
				max = c[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

float max_overall(t_image *image)
{
	float max;
	float red;
	float green;
	float blue;

	red = max_in_channel(image->red);
	max = red;
	green = max_in_channel(image->green);
	if (max < green)
		max = green;
	blue = max_in_channel(image->blue);
	if (max < blue)
		max = blue;
	return (max);
}

unsigned int rgb_to_int(float red, float green, float blue, float max)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned int value;

	if (red > 1)
		red = 1;
	if (green > 1)
		green = 1;
	if (blue > 1)
		blue = 1;
	(void ) max;
	r = (red) * 255.0f;
	g = (green) * 255.0f;
	b = (blue) * 255.0f;

	value = (r << 16) | (g << 8) | b;
	return (value);
}