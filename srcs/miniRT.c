/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:06:18 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/24 18:52:32 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Parse the scene file and populate the scene structure
// If successful, return 0
// If an error occurs, return -1
int	parse_scene(const char *filename, t_scene *scene)
{
	(void)filename;
	(void)scene;
	return (0);
}

// Render the scene using the parsed data
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

	if (argc < 2)
	{
		ft_putstr_fd("Usage: ./miniRT <scene_file.rt>\n", 2);
		return (1);
	}
	ft_printf("Parsing scene file \"%s\"\n", argv[1]);
	if (parse_scene(argv[1], &scene) == -1)
	{
		ft_putstr_fd("Error: Failed to parse scene file\n", 2);
		return (1);
	}
	render_scene(&scene);
	if (argc >= 3 && ft_strcmp(argv[2], "--save") == 0)
		save_image(argv[3], &scene);
	test();
	return (0);
}
