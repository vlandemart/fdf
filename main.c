/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 21:31:28 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/06 21:33:21 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		output_fdf(t_vector3 v1, t_vector3 v2, t_fdf *fdf)
{
	t_vector3 pos1;
	t_vector3 pos2;

	pos1 = vector3_new((int)v1.x, (int)v1.y, 0);
	pos2 = vector3_new((int)v2.x, (int)v2.y, 0);
	debug_v3(v1, -2);
	debug_str(" ### ", -2);
	debug_v3(v2, -2);
	debug_str("\n", -2);
	if (pos1.x < 0 || pos1.y < 0 || pos2.x < 0 || pos2.y < 0 ||
		pos1.x > SCREEN_W || pos2.x > SCREEN_W ||
		pos1.y > SCREEN_H || pos2.y > SCREEN_H)
		return ;
	output_line(pos1, pos2, fdf, v1.color, v2.color);
}

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

void		draw_vertices(t_fdf *fdf)
{
	t_vector3	v1;
	t_vector3	v2;
	int			i;
	int			j;

	i = -1;
	while (++i < fdf->map_h)
	{
		j = -1;
		while (++j < fdf->map_w)
		{
			v1 = fdf->vertices_to_draw[i * fdf->map_w + j];
			if (j + 1 < fdf->map_w)
			{
				v2 = fdf->vertices_to_draw[i * fdf->map_w + j + 1];
				output_fdf(v1, v2, fdf);
			}
			if (i + 1 < fdf->map_h)
			{
				v2 = fdf->vertices_to_draw[i * fdf->map_w + j + fdf->map_w];
				output_fdf(v1, v2, fdf);
			}
		}
	}
	free(fdf->vertices_to_draw);
}

void		iso(t_vector3 *v3)
{
	int prev_x;
	int prev_y;

	prev_x = v3->x;
	prev_y = v3->y;
	v3->x = (prev_x - prev_y) * cos(0.523599);
	v3->y = -v3->z + (prev_x + prev_y) * sin(0.523599);
}

void		project_vertices(t_fdf *fdf)
{
	t_vector3	v3;
	t_vector3	*vertecies;
	int			i;
	int			j;

	vertecies = ft_memalloc(fdf->vertices_count * sizeof(t_vector3));
	memcpy(vertecies, fdf->vertices, fdf->vertices_count * sizeof(t_vector3));
	*vertecies = *fdf->vertices;
	fdf->vertices_to_draw = ft_memalloc(fdf->vertices_count * sizeof(t_vector3));
	i = -1;
	while (++i < fdf->map_h)
	{
		j = -1;
		while (++j < fdf->map_w)
		{
			v3 = vertecies[i * fdf->map_w + j];
			if (fdf->iso)
				iso(&v3);
			v3 = matrix_multiply_vector(matrix_rot_z(fdf->map_rot.z), v3);
			v3 = matrix_multiply_vector(matrix_rot_x(fdf->map_rot.x), v3);
			v3 = matrix_multiply_vector(matrix_rot_y(fdf->map_rot.y), v3);
			v3 = vector3_add_v3(v3, fdf->map_pos);
			v3 = matrix_multiply_vector(calc_proj(), v3);
			v3 = vector3_add_v3(v3, vector3_new(1, 1, 0));
			v3 = vector3_multiply_v3(v3,
				vector3_new(0.5f * (float)SCREEN_W, 0.5 * SCREEN_H, 1));
			fdf->vertices_to_draw[i * fdf->map_w + j] = v3;
		}
	}
	free(vertecies);
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

void		render(t_fdf *fdf)
{
	int bpp;
	int size;
	int end;

	fdf->img_data = (int *)mlx_get_data_addr(fdf->img_main, &bpp, &size, &end);
	ft_clear_image(fdf);
	if (fdf->vertices_count == 0)
	{
		debug_str("No map to render\n", 5);
		exit(1);
	}
	else
	{
		debug_nbr(fdf->vertices_count, -1);
		debug_str(" vertices\n", -1);
		project_vertices(fdf);
		debug_str("Vertices projected.\n", -1);
		draw_vertices(fdf);
		debug_str("Vertices drawn.\n", -1);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img_main, 0, 0);
}

int			update(t_fdf *fdf)
{
	render(fdf);
	return (1);
}

int			handle_input(int key, t_fdf *fdf)
{
	int s;

	s = 1;
	if (key == 124 || key == 125 || key == 14 || key == 84 ||
		key == 88 || key == 83 || key == 85)
		s = -1;
	if (key == 123 || key == 124)
		vector3_add_v3_p(&fdf->map_pos, vector3_new(1 * s, 0, 0));
	if (key == 126 || key == 125)
		vector3_add_v3_p(&fdf->map_pos, vector3_new(0, 1 * s, 0));
	if (key == 12 || key == 14)
		vector3_add_v3_p(&fdf->map_pos, vector3_new(0, 0, 10 * s));
	if (key == 91 || key == 84)
		vector3_add_v3_p(&fdf->map_rot, vector3_new(0.03f * s, 0, 0));
	if (key == 86 || key == 88)
		vector3_add_v3_p(&fdf->map_rot, vector3_new(0, 0.03f * s, 0));
	if (key == 89 || key == 92 || key == 83 || key == 85)
		vector3_add_v3_p(&fdf->map_rot, vector3_new(0, 0, 0.03f * s));
	if (key == 49)
		fdf->iso = (fdf->iso == 0) ? 1 : 0;
	update(fdf);
	return (1);
}

int			close_window(void *param)
{
	(void)param;
	debug_str("App was closed.\n", 5);
	exit(0);
	return (0);
}

int			main(int ac, char **av)
{
	t_fdf *fdf;

	if (ac != 2)
	{
		ft_putendl("Usage: ./fdf <map_name>");
		return (0);
	}
	fdf = ft_memalloc(sizeof(t_fdf));
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, SCREEN_W, SCREEN_H, "Cube3d");
	fdf->img_main = mlx_new_image(fdf->mlx, SCREEN_W, SCREEN_H);
	fdf->map_rot = vector3_new(0, 0, 180);
	fdf->map_pos = vector3_new(0, 0, -300);
	fdf->iso = 0;
	read_map(av[1], fdf);
	debug_nbr(fdf->vertices_count, 2);
	debug_str(" vertices added.\n", 2);
	debug_str("Rendering map...\n", 5);
	mlx_hook(fdf->win, 17, 0, close_window, (void *)0);
	render(fdf);
	mlx_hook(fdf->win, 2, 0, handle_input, fdf);
	mlx_loop(fdf->mlx);
	return (1);
}
