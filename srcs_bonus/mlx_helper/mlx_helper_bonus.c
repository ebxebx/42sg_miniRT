/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 17:35:46 by zchoo             #+#    #+#             */
/*   Updated: 2026/06/03 17:35:46 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_helper_bonus.h"

// Write one pixel directly into the MLX image buffer, using the image's
// own line length and bytes-per-pixel instead of a fixed stride, since
// image memory layout is not guaranteed to be tightly packed 4-bytes/pixel
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
