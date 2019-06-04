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

//# include "mlx.h"
# include "libvgx/libvgx.h"
# include "minilibx/mlx.h"
# include "math.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	void		*img_main;
	int			*img_data;
	t_vector_3	map_pos;
	t_vector_3	map_rot;
	t_vector_3	*vertices;
	int			vertices_count;
	t_vector_3	*vertices_to_draw;
	int			map_h;
	int			map_w;
}				t_fdf;


void			read_map(char *map_name, t_fdf *fdf);
void			ft_image_put_pixel(t_fdf *fdf, int x, int y, int color);
void			output_line(t_vector_2_int p0, t_vector_2_int p1,
							t_fdf *fdf, int col1, int col2);

#endif
