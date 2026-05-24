/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:06:18 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/24 22:37:13 by ka-tan           ###   ########.fr       */
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

void	test(void)
{
	ft_printf("Test function called\n");
	t_vec3 vec;

	vec = vec3_init(1, 2, 3);
	ft_printf("vec3_init(1, 2, 3) = (%f, %f, %f)\n", vec.x, vec.y, vec.z);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	check_args(argc, argv);
	if (parse_scene(argv[1], &scene) == -1)
		return (1);
	render_scene(&scene);
	if (argc >= 3 && ft_strcmp(argv[2], "--save") == 0)
		save_image(argv[3], &scene);
	test();
	return (0);
}
