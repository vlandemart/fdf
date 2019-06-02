/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 20:46:42 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/06 20:57:50 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"

int	ft_boxcollision(t_gameobject_2 col, t_gameobject_2 obj)
{
	t_vector_2 col_min;
	t_vector_2 col_max;

	col_min.x = col.position.x - col.size.x;
	col_min.y = col.position.y - col.size.y;
	col_max.x = col.position.x + col.size.x;
	col_max.y = col.position.y + col.size.y;
	if ((obj.position.x > col_min.x && obj.position.x < col_max.x) &&
		(obj.position.y > col_min.y && obj.position.y < col_max.y))
		return (1);
	return (0);
}
