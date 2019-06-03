/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:59:07 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/06 20:00:53 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"

t_vector_2		ft_vector_2_new(float x, float y)
{
	t_vector_2 new_vector_2;

	new_vector_2.x = x;
	new_vector_2.y = y;
	new_vector_2.color = 0;
	return (new_vector_2);
}

t_vector_2_int	ft_vector_2_int_new(int x, int y)
{
	t_vector_2_int new_vector_2;

	new_vector_2.x = x;
	new_vector_2.y = y;
	new_vector_2.color = 0;
	return (new_vector_2);
}

t_vector_2_int	ft_vector_3_to_2_int(t_vector_3 v3)
{
	t_vector_2_int v2;

	v2.x = (int)v3.x;
	v2.y = (int)v3.y;
	v2.color = v3.color;
	return (v2);
}
