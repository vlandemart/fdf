/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvgx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 19:58:31 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/06 20:16:11 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVGX_H
# define LIBVGX_H
# define SCREEN_W 800
# define SCREEN_H 600
# define DEBUG_LEVEL -1

# include "../extra_cube3d/libft/libft.h"

typedef struct	s_vector_2
{
	float x;
	float y;
}				t_vector_2;

typedef struct	s_vector_2_int
{
	int x;
	int y;
}				t_vector_2_int;

typedef struct	s_vector_3
{
	float x;
	float y;
	float z;
}				t_vector_3;

typedef struct	s_gameobject_2
{
	t_vector_2 position;
	t_vector_2 size;
}				t_gameobject_2;

typedef struct	s_mat4x4
{
	float m[4][4];
}				t_mat4x4;

typedef struct	s_triangle
{
	t_vector_3 p[3];
}				t_triangle;

/*
** game garbage
*/

t_gameobject_2	ft_gameobject_2_new(float x, float y, float width,
									float height);
int				ft_boxcollision(t_gameobject_2 col, t_gameobject_2 obj);

/*
** vectors
*/

t_vector_2		ft_vector_2_new(float x, float y);
t_vector_2_int	ft_vector_2_int_new(int x, int y);
t_vector_3		ft_vector_3_new(float x, float y, float z);
t_vector_2_int	ft_vector_3_to_2_int(t_vector_3 v3);
t_vector_3		ft_vector_3_add_f(t_vector_3 v1, float num);
t_vector_3		ft_vector_3_add_v3(t_vector_3 v1, t_vector_3 num);
t_vector_3		ft_vector_3_subtract_v3(t_vector_3 v1, t_vector_3 v2);
t_vector_3		ft_vector_3_multiply_f(t_vector_3 v1, float num);
t_vector_3		ft_vector_3_multiply_v3(t_vector_3 v1, t_vector_3 v2);
t_vector_3		ft_vector_3_divide_f(t_vector_3 v1, float num);
float			ft_vector_3_dot_product(t_vector_3 v1, t_vector_3 v2);
float			ft_vector_3_length(t_vector_3 v1);
t_vector_3		ft_vector_3_normalize(t_vector_3 v1);
t_vector_3		ft_vector_3_cross_product(t_vector_3 v1, t_vector_3 v2);

/*
** matrix
*/

t_vector_3		matrix_multiply_vector(t_mat4x4 m, t_vector_3 v);
t_mat4x4		matrix_identity();
t_mat4x4		matrix_rotation_x(float angle_rad);
t_mat4x4		matrix_rotation_y(float angle_rad);
t_mat4x4		matrix_rotation_z(float angle_rad);
t_mat4x4		matrix_make_translation(float x, float y, float z);
t_mat4x4		matrix_projection(float fov, float aspect, float near,
									float far);
t_mat4x4		matrix_multiplication(t_mat4x4 mat1, t_mat4x4 mat2);
t_triangle		matrix_multiplication_tri(t_mat4x4 mat, t_triangle tri);

/*
** mlx extentions
*/

void			ft_image_put_pixel(int *img_data, int x, int y, int color);
void			output_line(t_vector_2_int p0, t_vector_2_int p1,
							int *img_data, int col);
void			output_triangle(t_triangle tri, int *img_data, int color);
void			output_fdf(t_triangle tri, int *img_data, int color);

/*
** triangles
*/

t_triangle		ft_triangle_new(t_vector_3 p0, t_vector_3 p1,
								t_vector_3 p2);
t_triangle		ft_triangle_add_f(t_triangle tri, float num);
t_triangle		ft_triangle_add_v3(t_triangle tri, t_vector_3 v);
t_triangle		ft_triangle_multiply_f(t_triangle tri, float num);
t_triangle		ft_triangle_multiply_v3(t_triangle tri, t_vector_3 v);
t_triangle		triangle_from_list(t_list *lst);

/*
** graphics calculations
*/

t_vector_3		calculate_normal(t_triangle tri);

/*
** debug
*/

void			print_matrix(t_mat4x4 m, int debug_lvl);
void			print_triangle(t_triangle tri, int debug_lvl);
void			print_triangle_v2int(t_vector_2_int pos1,
					t_vector_2_int pos2, t_vector_2_int pos3, int debug_lvl);
void			print_array(int **arr, int h, int w, int debug_lvl);
void			print_array_element(int **arr, int i, int j, int debug_lvl);
void			print_str(char *str, int debug_lvl);
void			print_nbr(int nbr, int debug_lvl);
#endif
