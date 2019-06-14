/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 21:31:28 by njacobso          #+#    #+#             */
/*   Updated: 2019/06/13 14:36:53 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

int			close_window(void *param)
{
	(void)param;
	debug_str("App was closed.\n", 5);
	exit(0);
	return (0);
}

int			handle_input(int key, t_fdf *fdf)
{
	int s;

	s = 1;
	if (key == 124 || key == 125 || key == 14 || key == 84 ||
		key == 88 || key == 83 || key == 85 || key == 78)
		s = -1;
	if (key == 123 || key == 124)
		vector3_add_v3_p(&fdf->map_pos, vector3_new(5 * s, 0, 0));
	if (key == 126 || key == 125)
		vector3_add_v3_p(&fdf->map_pos, vector3_new(0, 5 * s, 0));
	if (key == 12 || key == 14)
		vector3_add_v3_p(&fdf->map_pos, vector3_new(0, 0, 5 * s));
	if (key == 91 || key == 84)
		vector3_add_v3_p(&fdf->map_rot, vector3_new(0.03f * s, 0, 0));
	if (key == 86 || key == 88)
		vector3_add_v3_p(&fdf->map_rot, vector3_new(0, 0.03f * s, 0));
	if (key == 89 || key == 92 || key == 83 || key == 85)
		vector3_add_v3_p(&fdf->map_rot, vector3_new(0, 0, 0.03f * s));
	if (key == 49)
		fdf->iso = (fdf->iso == 0) ? 1 : 0;
	if (key == 69 || key == 78)
		fdf->z_zoom += 0.2f * s;
	if (key == 53)
		close_window(0);
	return (update(fdf));
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
	fdf->map_rot = vector3_new(180, 90, 180);
	fdf->map_pos = vector3_new(0, 0, -300);
	fdf->iso = 0;
	fdf->z_zoom = 5;
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
