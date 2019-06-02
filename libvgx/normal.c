/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:07:30 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/24 17:07:32 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"
#include <math.h>

t_vector_3	calculate_normal(t_triangle tri)
{
	t_vector_3	n;
	t_vector_3	line1;
	t_vector_3	line2;
	float		l;

	line1 = ft_vector_3_subtract_v3(tri.p[1], tri.p[0]);
	line2 = ft_vector_3_subtract_v3(tri.p[2], tri.p[0]);
	n.x = line1.y * line2.z - line1.z * line2.y;
	n.y = line1.z * line2.x - line1.x * line2.z;
	n.z = line1.x * line2.y - line1.y * line2.x;
	l = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);
	n = ft_vector_3_multiply_f(n, 1 / l);
	return (n);
}
