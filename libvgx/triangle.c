/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 12:37:42 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/19 12:41:33 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"
#include <stdlib.h>

t_triangle	ft_triangle_new(t_vector_3 p0, t_vector_3 p1, t_vector_3 p2)
{
	t_triangle tri;

	tri.p[0] = p0;
	tri.p[1] = p1;
	tri.p[2] = p2;
	return (tri);
}

t_triangle	ft_triangle_multiply_f(t_triangle tri, float num)
{
	tri.p[0] = ft_vector_3_multiply_f(tri.p[0], num);
	tri.p[1] = ft_vector_3_multiply_f(tri.p[1], num);
	tri.p[2] = ft_vector_3_multiply_f(tri.p[2], num);
	return (tri);
}

t_triangle	ft_triangle_multiply_v3(t_triangle tri, t_vector_3 v)
{
	tri.p[0] = ft_vector_3_multiply_v3(tri.p[0], v);
	tri.p[1] = ft_vector_3_multiply_v3(tri.p[1], v);
	tri.p[2] = ft_vector_3_multiply_v3(tri.p[2], v);
	return (tri);
}

t_triangle	ft_triangle_add_f(t_triangle tri, float num)
{
	tri.p[0] = ft_vector_3_add_f(tri.p[0], num);
	tri.p[1] = ft_vector_3_add_f(tri.p[1], num);
	tri.p[2] = ft_vector_3_add_f(tri.p[2], num);
	return (tri);
}

t_triangle	ft_triangle_add_v3(t_triangle tri, t_vector_3 v)
{
	tri.p[0] = ft_vector_3_add_v3(tri.p[0], v);
	tri.p[1] = ft_vector_3_add_v3(tri.p[1], v);
	tri.p[2] = ft_vector_3_add_v3(tri.p[2], v);
	return (tri);
}

/*
** draws a line on 2d screen between all points of a triangle
** input: triangle with screen projected coordinates
*/

void		output_triangle(t_triangle tri, int *img_data, int color)
{
	t_vector_2_int pos1;
	t_vector_2_int pos2;

	pos1 = ft_vector_3_to_2_int(tri.p[0]);
	pos2 = ft_vector_3_to_2_int(tri.p[1]);
	output_line(pos1, pos2, img_data, color);
	pos1 = ft_vector_3_to_2_int(tri.p[2]);
	output_line(pos1, pos2, img_data, color);
	pos2 = ft_vector_3_to_2_int(tri.p[0]);
	output_line(pos1, pos2, img_data, color);
}

t_triangle	triangle_from_list(t_list *lst)
{
	t_triangle result;

	result.p[0] = ((t_triangle*)lst->content)->p[0];
	result.p[1] = ((t_triangle*)lst->content)->p[1];
	result.p[2] = ((t_triangle*)lst->content)->p[2];
	return (result);
}

void		output_fdf(t_triangle tri, int *img_data, int color)
{
	t_vector_2_int pos1;
	t_vector_2_int pos2;
	t_vector_2_int pos3;

	pos1 = ft_vector_3_to_2_int(tri.p[0]);
	pos2 = ft_vector_3_to_2_int(tri.p[1]);
	pos3 = ft_vector_3_to_2_int(tri.p[2]);
	output_line(pos1, pos2, img_data, color);
	output_line(pos2, pos3, img_data, color);
}
