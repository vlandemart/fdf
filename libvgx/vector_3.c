/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 12:54:22 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/19 12:54:26 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"
#include <math.h>

t_vector_3		ft_vector_3_new(float x, float y, float z)
{
	t_vector_3 new_vector_3;

	new_vector_3.x = x;
	new_vector_3.y = y;
	new_vector_3.z = z;
	return (new_vector_3);
}

t_vector_3		ft_vector_3_add_v3(t_vector_3 v1, t_vector_3 v2)
{
	t_vector_3 result;

	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	result = v1;
	return (result);
}

t_vector_3		ft_vector_3_subtract_v3(t_vector_3 v1, t_vector_3 v2)
{
	t_vector_3 result;

	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	result = v1;
	return (result);
}

t_vector_3		ft_vector_3_add_f(t_vector_3 v1, float num)
{
	v1.x += num;
	v1.y += num;
	v1.z += num;
	return (v1);
}

t_vector_3		ft_vector_3_multiply_f(t_vector_3 v1, float num)
{
	v1.x *= num;
	v1.y *= num;
	v1.z *= num;
	return (v1);
}

t_vector_3		ft_vector_3_multiply_v3(t_vector_3 v1, t_vector_3 v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return (v1);
}

t_vector_3		ft_vector_3_divide_f(t_vector_3 v1, float num)
{
	v1.x /= num;
	v1.y /= num;
	v1.z /= num;
	return (v1);
}

float			ft_vector_3_dot_product(t_vector_3 v1, t_vector_3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float			ft_vector_3_length(t_vector_3 v1)
{
	return (sqrtf(ft_vector_3_dot_product(v1, v1)));
}

t_vector_3		ft_vector_3_normalize(t_vector_3 v1)
{
	float l;

	l = ft_vector_3_length(v1);
	return (ft_vector_3_divide_f(v1, l));
}

t_vector_3		ft_vector_3_cross_product(t_vector_3 v1, t_vector_3 v2)
{
	t_vector_3 v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
