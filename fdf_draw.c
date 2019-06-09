/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 16:30:27 by njacobso          #+#    #+#             */
/*   Updated: 2019/06/09 16:30:28 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		output_fdf(t_vector3 v1, t_vector3 v2, t_fdf *fdf)
{
	t_vector3 pos1;
	t_vector3 pos2;

	pos1 = vector3_new((int)v1.x, (int)v1.y, 0);
	pos1.color = v1.color;
	pos2 = vector3_new((int)v2.x, (int)v2.y, 0);
	pos2.color = v2.color;
	debug_v3(v1, -2);
	debug_str(" ### ", -2);
	debug_v3(v2, -2);
	debug_str("\n", -2);
	if (pos1.x < 0 || pos1.y < 0 || pos2.x < 0 || pos2.y < 0 ||
		pos1.x > SCREEN_W || pos2.x > SCREEN_W ||
		pos1.y > SCREEN_H || pos2.y > SCREEN_H)
		return ;
	output_line(pos1, pos2, fdf);
}

void		draw_vertices(t_fdf *fdf)
{
	t_vector3	v1;
	t_vector3	v2;
	int			i;
	int			j;

	i = -1;
	while (++i < fdf->map_h)
	{
		j = -1;
		while (++j < fdf->map_w)
		{
			v1 = fdf->vertices_to_draw[i * fdf->map_w + j];
			if (j + 1 < fdf->map_w)
			{
				v2 = fdf->vertices_to_draw[i * fdf->map_w + j + 1];
				output_fdf(v1, v2, fdf);
			}
			if (i + 1 < fdf->map_h)
			{
				v2 = fdf->vertices_to_draw[i * fdf->map_w + j + fdf->map_w];
				output_fdf(v1, v2, fdf);
			}
		}
	}
	free(fdf->vertices_to_draw);
}

void		iso(t_vector3 *v3)
{
	int prev_x;
	int prev_y;

	prev_x = v3->x;
	prev_y = v3->y;
	v3->x = (prev_x - prev_y) * cos(0.523599);
	v3->y = -v3->z + (prev_x + prev_y) * sin(0.523599);
}

void		project_vector(t_vector3 *v3, t_fdf *fdf)
{
	*v3 = matrix_multiply_vector(matrix_rot_z(fdf->map_rot.z), *v3);
	*v3 = matrix_multiply_vector(matrix_rot_x(fdf->map_rot.x), *v3);
	*v3 = matrix_multiply_vector(matrix_rot_y(fdf->map_rot.y), *v3);
	*v3 = vector3_add_v3(*v3, fdf->map_pos);
	*v3 = matrix_multiply_vector(calc_proj(), *v3);
	*v3 = vector3_add_v3(*v3, vector3_new(1, 1, 0));
	*v3 = vector3_multiply_v3(*v3,
		vector3_new(0.5f * (float)SCREEN_W, 0.5 * SCREEN_H, 1));
}

void		project_vertices(t_fdf *fdf)
{
	t_vector3	v3;
	t_vector3	*vertecies;
	int			i;
	int			j;

	vertecies = ft_memalloc(fdf->vertices_count * sizeof(t_vector3));
	memcpy(vertecies, fdf->vertices, fdf->vertices_count * sizeof(t_vector3));
	*vertecies = *fdf->vertices;
	fdf->vertices_to_draw = ft_memalloc(fdf->vertices_count *
										sizeof(t_vector3));
	i = -1;
	while (++i < fdf->map_h)
	{
		j = -1;
		while (++j < fdf->map_w)
		{
			v3 = vertecies[i * fdf->map_w + j];
			if (fdf->iso)
				iso(&v3);
			project_vector(&v3, fdf);
			fdf->vertices_to_draw[i * fdf->map_w + j] = v3;
		}
	}
	free(vertecies);
}
