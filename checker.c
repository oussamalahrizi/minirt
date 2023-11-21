#include "minirt.h"

t_matrix *get_rotation(double angle)
{
	t_matrix *rotation = create_matrix(3,3);

	set_to_indentity(rotation);

	rotation->matrix[0][0] = cos(angle);
	rotation->matrix[0][1] = sin(angle);
	rotation->matrix[1][0] = -sin(angle);
	rotation->matrix[1][1] = cos(angle);

	return (rotation);
}

t_matrix *get_scale(t_vec2 *scale)
{
	t_matrix *scale_matrix = create_matrix(3,3);

	set_to_indentity(scale_matrix);

	scale_matrix->matrix[0][0] = scale->x;
	scale_matrix->matrix[1][1] = scale->y;

	return (scale_matrix);
}

t_matrix *get_translation(t_vec2 *trans)
{
	t_matrix *translation = create_matrix (3,3);

	set_to_indentity(translation);

	translation->matrix[0][2] = trans->x;
	translation->matrix[1][2] = trans->y;

	return (translation);
}

t_matrix *set_transform_checker(t_vec2 *trans, t_vec2 *scale, double angle)
{
	t_matrix *final;

	t_matrix *translation = get_translation(trans);
	t_matrix *scale_matrix = get_scale(scale);
	t_matrix *rotation = get_rotation(angle);
	final = mt_multiplication(translation, rotation);
	final = mt_multiplication(final, scale_matrix);

	return (final);
}

t_vec2 *apply_transform_checker(t_matrix *transform, t_vec2 *input)
{
	t_matrix *m = create_matrix(3, 1);

	double *values = (double []) {input->x, input->y, 1};

	fill_mt(m, values);

	t_matrix *final = mt_multiplication(transform, m);
	t_vec2 *result = malloc(sizeof(t_vec2));
	result->x = final->matrix[0][0];
	result->y = final->matrix[1][0];
	return(result);
}

t_vec3 *get_color_checker(t_vec2 *uvcoords, t_matrix *checker_matrix)
{
	t_vec2 *inputvec = malloc(sizeof(t_vec2));

	inputvec->x = uvcoords->x;
	inputvec->y = uvcoords->y;
	t_vec2 *new_location = apply_transform_checker(checker_matrix, inputvec);

	double newU = new_location->x;
	double newV = new_location->y;

	int check = (int)(floor(newU)) + (int)(floor(newV));
	if (check % 2)
		return (new_vector3(1,1,1));
	
	return (new_vector3(0.0, 0.0, 0.0));
}


t_vec3 *get_color_texture(t_vec2 *uvcoords, t_matrix *checker_matrix, t_data *image)
{
	t_vec2 *inputvec = malloc(sizeof(t_vec2));

	inputvec->x = uvcoords->x;
	inputvec->y = uvcoords->y;

	(void) checker_matrix;
	double u = (inputvec->x + 1) / 2.0;
	double v = (inputvec->y + 1) / 2.0;
	
	int width = image->width;
	int height = image->height;
	

	int x = round(u * width);
	int y = height - round(v * height);

	x = ((x % width) + width) % width;
	y = ((y % height) + height) % height;
	
	int pixel_index = (y * image->line_length) + (x * (image->bits_per_pixel / 8));
	char *dst = image->addr + pixel_index;

	if (dst < image->addr || dst >= image->addr + image->line_length * image->height)
		return (new_vector3(0,0,0));

	unsigned int final = *((unsigned int *)dst);
	t_vec3 *color = new_vector3 ((final >> 16 & 255) / 255.f, (final >> 8 & 255) / 255.f,
		(final & 255) / 255.f);
	return (color);
}