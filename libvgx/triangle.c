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

t_triangle	ft_triangle_new(t_vector3 p0, t_vector3 p1, t_vector3 p2)
{
	t_triangle tri;

	tri.p[0] = p0;
	tri.p[1] = p1;
	tri.p[2] = p2;
	return (tri);
}

t_triangle	ft_triangle_multiply_f(t_triangle tri, float num)
{
	tri.p[0] = vector3_multiply_f(tri.p[0], num);
	tri.p[1] = vector3_multiply_f(tri.p[1], num);
	tri.p[2] = vector3_multiply_f(tri.p[2], num);
	return (tri);
}

t_triangle	ft_triangle_multiply_v3(t_triangle tri, t_vector3 v)
{
	tri.p[0] = vector3_multiply_v3(tri.p[0], v);
	tri.p[1] = vector3_multiply_v3(tri.p[1], v);
	tri.p[2] = vector3_multiply_v3(tri.p[2], v);
	return (tri);
}

t_triangle	ft_triangle_add_f(t_triangle tri, float num)
{
	tri.p[0] = vector3_add_f(tri.p[0], num);
	tri.p[1] = vector3_add_f(tri.p[1], num);
	tri.p[2] = vector3_add_f(tri.p[2], num);
	return (tri);
}

t_triangle	ft_triangle_add_v3(t_triangle tri, t_vector3 v)
{
	tri.p[0] = vector3_add_v3(tri.p[0], v);
	tri.p[1] = vector3_add_v3(tri.p[1], v);
	tri.p[2] = vector3_add_v3(tri.p[2], v);
	return (tri);
}

t_triangle	triangle_from_list(t_list *lst)
{
	t_triangle result;

	result.p[0] = ((t_triangle*)lst->content)->p[0];
	result.p[1] = ((t_triangle*)lst->content)->p[1];
	result.p[2] = ((t_triangle*)lst->content)->p[2];
	return (result);
}
