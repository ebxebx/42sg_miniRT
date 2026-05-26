/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 23:21:57 by ka-tan            #+#    #+#             */
/*   Updated: 2026/05/26 20:28:27 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//parse_ambient, parse_camera, parse_light

int	parse_ambient(char **tokens, t_scene *scene)
{
	t_vec3	rgb;

	if (tokens[1] == NULL || tokens[2] == NULL || tokens[3] != NULL)
	{
		ft_putstr_fd("Error: Usage: ./miniRT <scene_file.rt>\n", 2);
		return (1);
	}
	//parse_rgb TBC
	// temporary, just to compile
	(void)rgb;
	(void)scene;
	return (0); 
}