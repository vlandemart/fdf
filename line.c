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

#include "fdf.h"
#include "libvgx/libvgx.h"

/*
** draws a line on 2d screen
** input: 2 vectors with (int)xy screen position
*/

void	output_line(t_vector3 p0, t_vector3 p1, t_fdf *fdf)
{
	t_line line;

	line.dx = ft_abs(p1.x - p0.x);
	line.dy = ft_abs(p1.y - p0.y);
	line.sx = p0.x < p1.x ? 1 : -1;
	line.sy = p0.y < p1.y ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	while (1)
	{
		ft_image_put_pixel(fdf, p0.x, p0.y, p0.color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			p0.x += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			p0.y += line.sy;
		}
	}
}
