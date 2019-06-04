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

void		output_fdf(t_vector_3 v1, t_vector_3 v2, t_fdf *fdf)
{
	t_vector_2_int pos1;
	t_vector_2_int pos2;

	pos1 = ft_vector_3_to_2_int(v1);
	pos2 = ft_vector_3_to_2_int(v2);

	print_nbr(v1.x, -2);
	print_str(" : ", -2);
	print_nbr(v1.y, -2);
	print_str(" : ", -2);
	print_nbr(v1.color, -2);
	print_str(" ### ", -2);
	print_nbr(v2.x, -2);
	print_str(" : ", -2);
	print_nbr(v2.y, -2);
	print_str(" : ", -2);
	print_nbr(v2.color, -2);
	print_str("\n", -2);

	output_line(pos1, pos2, fdf, v1.color, v2.color);
}

t_mat4x4	calculate_projection(void)
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
	t_vector_3	v1;
	t_vector_3	v2;
	int i;
	int j;

	i = 0;
	while (i < fdf->map_h)
	{
		j = 0;
		while (j < fdf->map_w)
		{
			if (fdf->vertices_to_draw->next != NULL)
			{
				v1 = ft_vector_3_from_list(fdf->vertices_to_draw);
				if (j + 1 != fdf->map_w)
				{
					v2 = ft_vector_3_from_list(fdf->vertices_to_draw->next);
					output_fdf(v1, v2, fdf);
				}
				if (ft_lstget(fdf->vertices_to_draw, fdf->map_w) != NULL)
				{
					v2 = ft_vector_3_from_list(ft_lstget(fdf->vertices_to_draw, fdf->map_w));
					output_fdf(v1, v2, fdf);
				}
				ft_lstremove(&fdf->vertices_to_draw);
			}
			j++;
		}
		i++;
	}
	ft_lstclear(&fdf->vertices_to_draw);
}

void		project_vertices(t_fdf *fdf)
{
	t_vector_3	v3;
	t_mat4x4	mat_proj;
	t_mat4x4	mat_rot_z;
	t_mat4x4	mat_rot_x;
	t_list		*vertecies;

	vertecies = fdf->vertices;
	mat_proj = calculate_projection();
	mat_rot_x = matrix_rotation_x(fdf->map_rot.x * .5f);
	mat_rot_z = matrix_rotation_z(fdf->map_rot.z);
	while (vertecies != NULL)
	{
		v3 = ft_vector_3_from_list(vertecies);
		v3 = matrix_multiply_vector(mat_rot_z, v3);
		v3 = matrix_multiply_vector(mat_rot_x, v3);
		v3 = ft_vector_3_add_v3(v3, ft_vector_3_new(0, 0, 300));
		v3 = matrix_multiply_vector(mat_proj, v3);
		v3 = ft_vector_3_add_v3(v3, ft_vector_3_new(1, 1, 0));
		v3 = ft_vector_3_multiply_v3(v3,
			ft_vector_3_new(0.5f * (float)SCREEN_W, 0.5 * SCREEN_H, 1));
		print_v3(v3, -2);
		print_str(" vertex ", -2);
		ft_lstadd(&fdf->vertices_to_draw, ft_lstnew(&v3, sizeof(t_vector_3)));
		print_nbr(((t_vector_3*)fdf->vertices_to_draw->content)->x, -2);
		print_str(" x was written.\n", -2);
		vertecies = vertecies->next;
	}
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
	if (ft_lstcount(fdf->vertices) == 0)
	{
		print_str("No map to render\n", 5);
		exit (1);
	}
	else
	{
		print_nbr(ft_lstcount(fdf->vertices), -1);
		print_str(" vertices\n", -1);
		project_vertices(fdf);
		print_str("Vertices projected.\n", -1);
		draw_vertices(fdf);
		print_str("Vertices drawn.\n", -1);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img_main, 0, 0);
}

int			update(int key, t_fdf *fdf)
{
	key = 0;
	fdf->map_rot = ft_vector_3_add_f(fdf->map_rot, 0.03f);
	render(fdf);
	return (1);
}

int			close_window(void *param)
{
	(void)param;
	print_str("App was closed.\n", 5);
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
	fdf->map_rot = ft_vector_3_new(1, 1, 1);

	read_map(av[1], fdf);
	print_nbr(ft_lstcount(fdf->vertices), 2);
	print_str(" vertices added.\n", 2);
	print_str("Rendering map...\n", 5);
	mlx_hook(fdf->win, 17, 0, close_window, (void *)0);
	//mlx_loop_hook(fdf->mlx, update, fdf);
	render(fdf);
	mlx_hook(fdf->win, 2, 0, update, fdf);
	mlx_loop(fdf->mlx);
	return (1);
}
