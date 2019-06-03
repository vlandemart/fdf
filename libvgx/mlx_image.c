/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:30:29 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/15 15:40:17 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"

void	ft_image_put_pixel(int *img_data, int x, int y, int color)
{
	int	pos;

	pos = x + y * SCREEN_W;
	if (pos > SCREEN_W * SCREEN_H || pos < 0)
		return ;
	img_data[pos] = color;
}
