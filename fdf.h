/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 17:22:51 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/19 17:22:54 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libvgx/libvgx.h"
# include "math.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

void	add_triangle_to_mesh(t_triangle tri);
void	read_map(char *map_name);

#endif
