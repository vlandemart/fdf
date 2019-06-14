/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_rotations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 14:30:50 by njacobso          #+#    #+#             */
/*   Updated: 2019/06/13 14:30:52 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		v3_rotate_x(t_vector3 *v3, t_fdf fdf)
{
	int y;
	int z;

	y = (v3->y * cosf(fdf.map_rot.x)) + (v3->z * sinf(fdf.map_rot.x));
	z = (-v3->y * sinf(fdf.map_rot.x)) + (v3->z * cosf(fdf.map_rot.x));
	v3->y = y;
	v3->z = z;
}

void		v3_rotate_y(t_vector3 *v3, t_fdf fdf)
{
	int x;
	int z;

	x = (v3->x * cosf(fdf.map_rot.y)) + (v3->z * sinf(fdf.map_rot.y));
	z = (-v3->x * sinf(fdf.map_rot.y)) + (v3->z * cosf(fdf.map_rot.y));
	v3->x = x;
	v3->z = z;
}

void		v3_rotate_z(t_vector3 *v3, t_fdf fdf)
{
	int x;
	int y;

	x = (v3->x * cosf(fdf.map_rot.z)) - (v3->y * sinf(fdf.map_rot.z));
	y = (v3->x * sinf(fdf.map_rot.z)) + (v3->y * cosf(fdf.map_rot.z));
	v3->x = x;
	v3->y = y;
}
