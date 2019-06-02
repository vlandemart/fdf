/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:30:26 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/16 12:30:30 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"
#include <math.h>

t_vector_3	matrix_multiply_vector(t_mat4x4 m, t_vector_3 v)
{
	t_vector_3	result;
	float		w;

	result.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
	result.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
	result.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
	w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	if (w != 0.0f)
	{
		result = ft_vector_3_divide_f(result, w);
	}
	return (result);
}

t_mat4x4	matrix_identity(void)
{
	t_mat4x4 mat;

	ft_bzero(&mat, sizeof(t_mat4x4));
	mat.m[0][0] = 1;
	mat.m[1][1] = 1;
	mat.m[2][2] = 1;
	mat.m[3][3] = 1;
	return (mat);
}

t_mat4x4	matrix_rotation_x(float angle_rad)
{
	t_mat4x4 mat_rot;

	ft_bzero(&mat_rot, sizeof(t_mat4x4));
	mat_rot.m[0][0] = 1.0f;
	mat_rot.m[1][1] = cosf(angle_rad);
	mat_rot.m[1][2] = sinf(angle_rad);
	mat_rot.m[2][1] = -sinf(angle_rad);
	mat_rot.m[2][2] = cosf(angle_rad);
	mat_rot.m[3][3] = 1.0f;
	return (mat_rot);
}

t_mat4x4	matrix_rotation_y(float angle_rad)
{
	t_mat4x4 mat_rot;

	ft_bzero(&mat_rot, sizeof(t_mat4x4));
	mat_rot.m[0][0] = cosf(angle_rad);
	mat_rot.m[1][1] = sinf(angle_rad);
	mat_rot.m[1][2] = -sinf(angle_rad);
	mat_rot.m[2][1] = 1.0f;
	mat_rot.m[2][2] = cosf(angle_rad);
	mat_rot.m[3][3] = 1.0f;
	return (mat_rot);
}

t_mat4x4	matrix_rotation_z(float angle_rad)
{
	t_mat4x4 mat_rot;

	ft_bzero(&mat_rot, sizeof(t_mat4x4));
	mat_rot.m[0][0] = cosf(angle_rad);
	mat_rot.m[0][1] = sinf(angle_rad);
	mat_rot.m[1][0] = -sinf(angle_rad);
	mat_rot.m[1][1] = cosf(angle_rad);
	mat_rot.m[2][2] = 1;
	mat_rot.m[3][3] = 1;
	return (mat_rot);
}

t_mat4x4	matrix_make_translation(float x, float y, float z)
{
	t_mat4x4 mat;

	mat = matrix_identity();
	mat.m[3][0] = x;
	mat.m[3][1] = y;
	mat.m[3][2] = z;
	return (mat);
}

t_triangle	matrix_multiplication_tri(t_mat4x4 mat, t_triangle tri)
{
	t_triangle new_tri;

	new_tri.p[0] = matrix_multiply_vector(mat, tri.p[0]);
	new_tri.p[1] = matrix_multiply_vector(mat, tri.p[1]);
	new_tri.p[2] = matrix_multiply_vector(mat, tri.p[2]);
	return (new_tri);
}

t_mat4x4	matrix_projection(float fov, float aspect, float near, float far)
{
	float		ffov_rad;
	t_mat4x4	mat;

	ffov_rad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);
	bzero(&mat, sizeof(mat));
	mat.m[0][0] = aspect * ffov_rad;
	mat.m[1][1] = ffov_rad;
	mat.m[2][2] = far / (far - near);
	mat.m[3][2] = (-far * near) / (far - near);
	mat.m[2][3] = 1.0f;
	return (mat);
}

t_mat4x4	matrix_multiplication(t_mat4x4 mat1, t_mat4x4 mat2)
{
	int			i;
	int			j;
	int			k;
	t_mat4x4	res;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.m[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				res.m[i][j] += mat1.m[i][k] * mat2.m[i][k];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}
