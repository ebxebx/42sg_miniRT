/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:06:18 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/27 20:19:23 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	check_args(int argc, char **argv)
{
	char	*ext;

	if (argc < 2)
	{
		ft_putstr_fd("Error: Usage: ./miniRT <scene_file.rt>\n", 2);
		exit(1);
	}
	ext = ft_strrchr(argv[1], '.');
	if (!ext || ext == argv[1] || ext[-1] == '/' || ft_strcmp(ext, ".rt") != 0)
	{
		ft_putstr_fd("Error: Expected .rt file\n", 2);
		exit(1);
	}
}

void	render_scene(t_scene *scene)
{
	(void)scene;
}

void	save_image(const char *filename, t_scene *scene)
{
	(void)scene;
	ft_printf("Saving rendered image to \"%s\"\n", filename);
}

/* void	test(void)
{
	t_vec3	vec;

	ft_printf("Test function called\n");
	vec = vec3_init(1, 2, 3);
	ft_printf("vec3_init(1, 2, 3) = (%f, %f, %f)\n", vec.x, vec.y, vec.z);
	//test_vec3();
} */

void	test(void)
{
	t_scene	scene;
	char	*tokens[4];

	/* Happy path */
	tokens[0] = "A";
	tokens[1] = "0.2";
	tokens[2] = "255,128,0";
	tokens[3] = NULL;
	parse_ambient(tokens, &scene);
}


static void	dump_objects(t_object *obj)
{
	while (obj)
	{
		if (obj->type == SPHERE)
			ft_printf("  sp centre=(%f,%f,%f) r=%f\n",
				obj->shape.sp.centre.x, obj->shape.sp.centre.y,
				obj->shape.sp.centre.z, obj->shape.sp.radius);
		else if (obj->type == PLANE)
			ft_printf("  pl point=(%f,%f,%f)\n",
				obj->shape.pl.point.x, obj->shape.pl.point.y,
				obj->shape.pl.point.z);
		else
			ft_printf("  cy (stub)\n");
		obj = obj->next;
	}
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	check_args(argc, argv);
	if (parse_scene(argv[1], &scene) == -1)
	{
		scene_free(&scene);
		return (1);
	}
	ft_printf("objects:\n");
	dump_objects(scene.objects);
	render_scene(&scene);
	scene_free(&scene);
	return (0);
}
