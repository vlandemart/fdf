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
	t_vector3	map_pos;
	t_vector3	map_rot;
	t_vector3	*vertices;
	int			vertices_count;
	t_vector3	*vertices_to_draw;
	int			map_h;
	int			map_w;
	int			iso;
}				t_fdf;

typedef struct	s_line
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;
}				t_line;

void			read_map(char *map_name, t_fdf *fdf);
void			ft_image_put_pixel(t_fdf *fdf, int x, int y, int color);
void			output_line(t_vector3 p0, t_vector3 p1, t_fdf *fdf);
t_mat4x4		calc_proj(void);
void			ft_clear_image(t_fdf *fdf);
void			project_vertices(t_fdf *fdf);
void			project_vector(t_vector3 *v3, t_fdf *fdf);
void			iso(t_vector3 *v3);
void			draw_vertices(t_fdf *fdf);
void			output_fdf(t_vector3 v1, t_vector3 v2, t_fdf *fdf);

#endif
