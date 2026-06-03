/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:35:46 by zchoo             #+#    #+#             */
/*   Updated: 2026/06/03 18:36:07 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_helper.h"
#include <stdio.h>

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

void	color_map_1(t_mlx *mlx, int w, int h)
{
	int	x;
	int	y;
	int	color;

	x = w;
	while (x--)
	{
		y = h;
		while (y--)
		{
			color = (x * 255) / w + ((((w - x) * 255) / w) << 16) + (((y * 255)
						/ h) << 8);
			my_mlx_pixel_put(mlx, x, y, color);
		}
	}
}

void	color_map_2(t_mlx *mlx, unsigned char *data, int bpp, int sl, int w,
		int h, int endian, int type)
{
	int				x;
	int				y;
	int				opp;
	int				dec;
	int				color;
	int				color2;
	int				local_endian;
	unsigned char	*ptr;
	int				a;

	a = 0x11223344;
	if (((unsigned char *)&a)[0] == 0x11)
		local_endian = 1;
	else
		local_endian = 0;
	opp = bpp / 8;
	printf("(opp : %d) ", opp);
	y = h;
	while (y--)
	{
		ptr = data + y * sl;
		x = w;
		while (x--)
		{
			if (type == 2)
				color = (y * 255) / w + ((((w - x) * 255) / w) << 16) + (((y
								* 255) / h) << 8);
			else
				color = (x * 255) / w + ((((w - x) * 255) / w) << 16) + (((y
								* 255) / h) << 8);
			color2 = mlx_get_color_value(mlx->mlx, color);
			dec = opp;
			while (dec--)
				if (endian == local_endian)
				{
					if (endian)
						*(ptr + x * opp + dec) = ((unsigned char *)(&color2))[4
							- opp + dec];
					else
						*(ptr + x * opp
								+ dec) = ((unsigned char *)(&color2))[dec];
				}
				else
				{
					if (endian)
						*(ptr + x * opp
								+ dec) = ((unsigned char *)(&color2))[opp - 1
							- dec];
					else
						*(ptr + x * opp + dec) = ((unsigned char *)(&color2))[3
							- dec];
				}
		}
	}
}
