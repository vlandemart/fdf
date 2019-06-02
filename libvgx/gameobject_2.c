/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameobject_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 20:01:16 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/06 20:03:31 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"

t_gameobject_2	ft_gameobject_2_new(float x, float y, float width, float height)
{
	t_gameobject_2 new_gameobject_2;

	new_gameobject_2.position.x = x;
	new_gameobject_2.position.y = y;
	new_gameobject_2.size.x = width;
	new_gameobject_2.size.y = height;
	return (new_gameobject_2);
}
