#include "minirt.h"

t_object *init_objects()
{
    t_object *objects;

    objects = malloc(sizeof(t_object) * 4);
    // plane
    objects[1].type = PLANE;
    objects[1].id = 1;
    objects[1].base_color = new_vector3(0.5, 0.5, 0.5);
    objects[1].mat_color = new_vector3(1.0, 1.0, 1.0);
    objects[1].translation = new_vector3(0.0, 0.0, 0.75);
    objects[1].rotation = new_vector3(0.0, 0.0, 0.0);
    objects[1].scale = new_vector3(4.0, 4.0, 1.0);
    objects[1].has_material = 1;
    objects[1].shininess = 0.0;
    objects[1].reflectivity = 0.5;
    objects[1].gtfm = set_transform(objects[1].translation, objects[1].rotation, objects[1].scale);

    // sphere
    objects[0].type = SPHERE;
    objects[0].id = 0;
    objects[0].base_color = new_vector3(0.25, 0.5, 0.8);
    objects[0].mat_color = new_vector3(1.0, 0.8, 0.0);
    objects[0].translation = new_vector3(1, 0.0, -50.0);
    objects[0].rotation = new_vector3(0.0, 0.0, 0.0);
    objects[0].scale = new_vector3(0.75, 0.75, 0.75);
    objects[0].has_material = 1;
    objects[0].shininess = 10.0;
    objects[0].reflectivity = 0.25;
    objects[0].gtfm = set_transform(objects[0].translation, objects[0].rotation, objects[0].scale);

    objects[3].type = CONE;
    objects[3].id = 2;
    objects[3].base_color = new_vector3(1 , 0, 0);
    objects[3].mat_color = new_vector3(1,0, 0);
    objects[3].translation = new_vector3(0, 0.0, 0);
    objects[3].rotation = new_vector3(M_PI / 4, 0.0, 0.0);
    objects[3].scale = new_vector3(1, 1, 1.5);
    objects[3].has_material = 1;
    objects[3].shininess = 10;
    objects[3].reflectivity = 0.25;
    objects[3].gtfm = set_transform(objects[3].translation, objects[3].rotation, objects[3].scale);

    // objects[3].type = SPHERE;
    // objects[3].id = 3;
    // objects[3].base_color = new_vector3(1.0, 0.8, 0.0);
    // objects[3].mat_color = new_vector3(0.25, 0.5, 0.8);
    // objects[3].translation = new_vector3(0, 0.0, 0.0);
    // objects[3].rotation = new_vector3(0.0, 0.0, 0.0);
    // objects[3].scale = new_vector3(0.5, 0.5, 0.5);
    // objects[3].has_material = 1;
    // objects[3].shininess = 10.0;
    // objects[3].reflectivity = 0.75;
    // objects[3].gtfm = set_transform(objects[3].translation, objects[3].rotation, objects[3].scale);

    objects[2].type = CYLINDER;
    objects[2].id = 3;
    objects[2].base_color = new_vector3(1.0, 0.8, 0.0);
    objects[2].mat_color = new_vector3(0.25, 0.5, 0.8);
    objects[2].translation = new_vector3(-1.5, 0.0, 0.0);
    objects[2].rotation = new_vector3(0, 0.0, 0.0);
    objects[2].scale = new_vector3(0.75, 0.75, 1);
    objects[2].has_material = 1;
    objects[2].shininess = 10;
    objects[2].reflectivity = 0.5;
    objects[2].gtfm = set_transform(objects[2].translation, objects[2].rotation, objects[2].scale);

    return (objects);
}

t_light *init_light()
{
    t_light *light_list = malloc(sizeof(t_light) * 3);

    light_list[0].color = new_vector3(1, 1, 1);
    light_list[0].position = new_vector3(5, -10, -5);
    light_list[0].intensity = 1.0;

    light_list[1].color = new_vector3(1, 1, 1);
    light_list[1].position = new_vector3(0, -10, -5);
    light_list[1].intensity = 1.0;

    light_list[2].color = new_vector3(1, 1, 1);
    light_list[2].position = new_vector3(-5, -10, -5);
    light_list[2].intensity = 1.0;

    return (light_list);
}