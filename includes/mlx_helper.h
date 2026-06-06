/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helper.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:19:54 by zchoo             #+#    #+#             */
/*   Updated: 2026/06/06 12:52:01 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HELPER_H
# define MLX_HELPER_H

# include "../minilibx-linux/mlx.h"
#include <stdint.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_mlx;

void		my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

void		color_map_1(t_mlx *mlx, int w, int h);
void		color_map_2(t_mlx *mlx, unsigned char *data, int bpp, int sl, int w,
				int h, int endian, int type);

#endif
