/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 16:31:36 by njacobso          #+#    #+#             */
/*   Updated: 2019/06/09 16:31:37 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4x4	calc_proj(void)
{
	float near;
	float far;
	float fov;
	float aspect;

	near = 0.1f;
	far = 1000.0f;
	fov = 90.0f;
	aspect = (float)SCREEN_H / (float)SCREEN_W;
	return (matrix_projection(fov, aspect, near, far));
}

void		ft_clear_image(t_fdf *fdf)
{
	int i;
	int j;

	i = 0;
	while (i < SCREEN_W)
	{
		j = 0;
		while (j < SCREEN_H)
		{
			ft_image_put_pixel(fdf, i, j, 0x000000);
			j++;
		}
		i++;
	}
}
