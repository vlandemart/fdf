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

void		*g_mlx;
void		*g_win;
void		*g_img_main;
int			*g_img_data;
t_mat4x4	g_mat_proj;
float		g_frametime;
float		g_rot;
t_list		*g_mesh;
t_vector_3	g_camera;
t_list		*g_tri_to_draw;

void		calculate_projection(void)
{
	float near;
	float far;
	float fov;
	float aspect;

	near = 0.1f;
	far = 1000.0f;
	fov = 90.0f;
	aspect = (float)SCREEN_H / (float)SCREEN_W;
	g_mat_proj = matrix_projection(fov, aspect, near, far);
}

void		draw_triangles(void)
{
	t_triangle	tri;

	print_str("Drawing triangles\n", -1);
	while (g_tri_to_draw != NULL)
	{
		if (g_tri_to_draw == NULL || g_tri_to_draw->content == NULL)
		{
			print_str("g_triangles are null", 2);
			return ;
		}
		print_str("Tri is not null\n", -2);
		tri.p[0] = ((t_triangle*)g_tri_to_draw->content)->p[0];
		tri.p[1] = ((t_triangle*)g_tri_to_draw->content)->p[1];
		tri.p[2] = ((t_triangle*)g_tri_to_draw->content)->p[2];
		print_triangle(tri, -2);
		print_str("Points allocated\n", -2);
		output_fdf(tri, g_img_data, 0xffffff);
		print_str("Output called\n", -2);
		ft_lstremove(&g_tri_to_draw);
		print_str("Element removed\n", -2);
	}
	print_str("Clearing list.\n", -1);
	ft_lstclear(&g_tri_to_draw);
}

t_triangle	iso(t_triangle tri)
{
	t_vector_3 v;
	int prev_x;
	int prev_y;
	int i;

	i = 0;
	while (i < 3)
	{
		v = tri.p[i];
		prev_x = v.x;
		prev_y = v.y;
		v.x = (prev_x - prev_y) * cos(0.523599);
		v.y = -v.z + (prev_x + prev_y) * sin (0.523599);
		tri.p[i] = v;
		i++;
	}
	return (tri);
}

void		project_mesh(t_list *mesh)
{
	t_triangle	tri;
	t_triangle	tri_trans;
	t_triangle	tri_proj;
	t_mat4x4	mat_rot_z;
	t_mat4x4	mat_rot_x;

	mat_rot_x = matrix_rotation_x(g_rot * .5f);
	mat_rot_z = matrix_rotation_z(g_rot);
	while (mesh != NULL)
	{
		tri = triangle_from_list(mesh);
		tri_trans = matrix_multiplication_tri(mat_rot_z, tri);
		tri_trans = matrix_multiplication_tri(mat_rot_x, tri_trans);
		tri_trans = ft_triangle_add_v3(tri_trans, ft_vector_3_new(0, 0, 30));
		tri_proj = matrix_multiplication_tri(g_mat_proj, tri_trans);
		tri_proj = ft_triangle_add_v3(tri_proj, ft_vector_3_new(1, 1, 0));
		tri_proj = ft_triangle_multiply_v3(tri_proj,
			ft_vector_3_new(0.5f * (float)SCREEN_W, 0.5 * SCREEN_H, 1));
		ft_lstadd(&g_tri_to_draw, ft_lstnew(&tri_proj, sizeof(tri_proj)));
		mesh = mesh->next;
	}
}

void		add_triangle_to_mesh(t_triangle tri)
{
	ft_lstadd(&g_mesh, ft_lstnew(&tri, sizeof(tri)));
	print_str("Adding triangle at ", 1);
	print_triangle(tri, 1);
	print_nbr(sizeof(tri), 2);
	print_str(" tri\n", 2);
	print_nbr(sizeof(t_vector_3), 2);
	print_str(" v3\n", 2);
	print_nbr(sizeof(float), 2);
	print_str(" f\n", 2);
}

void		ft_clear_image(void)
{
	int i;
	int j;

	i = 0;
	while (i < SCREEN_W)
	{
		j = 0;
		while (j < SCREEN_H)
		{
			ft_image_put_pixel(g_img_data, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void		render(void)
{
	int bpp;
	int size;
	int end;

	g_img_data = (int *)mlx_get_data_addr(g_img_main, &bpp, &size, &end);
	ft_clear_image();
	if (ft_lstcount(g_mesh) == 0)
	{
		print_str("No mesh to render\n", 5);
		return ;
	}
	else
	{
		print_nbr(ft_lstcount(g_mesh), -1);
		print_str(" triangles\n", -1);
		calculate_projection();
		print_str("Projection calculated.\n", -1);
		project_mesh(g_mesh);
		print_str("Mesh projected.\n", -1);
		print_nbr(ft_lstcount(g_tri_to_draw), -1);
		print_str(" triangles to draw.\n", -1);
		draw_triangles();
	}
	mlx_put_image_to_window(g_mlx, g_win, g_img_main, 0, 0);
}

int			update(void)
{
	if (g_frametime < 0)
	{
		g_frametime += 0.001;
		return (0);
	}
	g_rot += 0.03f;
	render();
	g_frametime = 0;
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
	if (ac != 2)
	{
		ft_putendl("Usage: ./fdf <map_name>");
		return (0);
	}
	g_mlx = mlx_init();
	g_win = mlx_new_window(g_mlx, SCREEN_W, SCREEN_H, "Cube3d");
	g_img_main = mlx_new_image(g_mlx, SCREEN_W, SCREEN_H);
	read_map(av[1]);
	print_str("Rendering map...\n", 5);
	mlx_hook(g_win, 17, 0, close_window, (void *)0);
	mlx_loop_hook(g_mlx, update, (void *)0);
	mlx_loop(g_mlx);
	return (1);
}
