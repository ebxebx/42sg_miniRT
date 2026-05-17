/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 19:06:18 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/17 19:37:52 by ka-tan           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
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
	return (0);
}
