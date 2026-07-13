/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_free_scene.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ka-tan <ka-tan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:07:06 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/31 21:07:15 by ka-tan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniRT.h"

// Free every node in the scene's linked list of lights
static void	free_lights(t_light *head)
{
	t_light	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

// Free every node in the scene's linked list of objects
static void	free_objects(t_object *head)
{
	t_object	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

// Free all heap-allocated scene data (objects and lights)
void	scene_free(t_scene *scene)
{
	free_objects(scene->objects);
	free_lights(scene->lights);
}

// Opens the scene file, parses every line, and returns -1 on any error.
int	parse_scene(const char *filename, t_scene *scene)
{
	int	fd;
	int	failed;

	ft_bzero(scene, sizeof(t_scene));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Cannot open scene file\n", 2);
		return (-1);
	}
	failed = read_lines(fd, scene);
	close(fd);
	if (failed)
		return (-1);
	if (check_scene_counts(scene))
		return (-1);
	scene->camera_init = scene->camera;
	return (0);
}
