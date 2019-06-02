/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:51:25 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/16 12:51:42 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"

/*
** draws a line on 2d screen
** input: 2d position on the screen
*/

void	output_line(t_vector_2_int p0, t_vector_2_int p1,
					int *img_data, int col)
{
	int dx = ft_abs(p1.x - p0.x);
	int dy = ft_abs(p1.y - p0.y);
	int sx = p0.x < p1.x ? 1 : -1;
	int sy = p0.y < p1.y ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (1)
	{
		ft_image_put_pixel(img_data, p0.x, p0.y, col);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			p0.x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			p0.y += sy;
		}
	}
}