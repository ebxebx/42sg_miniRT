/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zchoo <zchoo@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 22:00:00 by zchoo             #+#    #+#             */
/*   Updated: 2026/07/15 22:00:00 by zchoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUADRATIC_H
# define QUADRATIC_H

typedef struct s_quadratic
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
}	t_quadratic;

#endif
