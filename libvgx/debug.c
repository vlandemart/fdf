/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 13:07:40 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/28 13:07:57 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvgx.h"

void	print_v3(t_vector_3 v3, int debug_lvl)
{
	if (debug_lvl < DEBUG_LEVEL)
		return ;
	ft_putstr("(");
	ft_putnbr(v3.x);
	ft_putstr(":");
	ft_putnbr(v3.y);
	ft_putstr(":");
	ft_putnbr(v3.z);
	ft_putstr(") ");
	ft_putnbr(v3.color);
	ft_putstr(".");
}

void	print_triangle(t_triangle tri, int debug_lvl)
{
	if (debug_lvl < DEBUG_LEVEL)
		return ;
	print_v3(tri.p[0], debug_lvl);
	print_v3(tri.p[1], debug_lvl);
	print_v3(tri.p[2], debug_lvl);
}

void	print_matrix(t_mat4x4 m, int debug_lvl)
{
	int i;
	int j;

	if (debug_lvl < DEBUG_LEVEL)
		return ;
	i = 0;
	while (i < 4)
	{
		ft_putstr("( ");
		j = 0;
		while (j < 4)
		{
			ft_putnbr(m.m[i][j]);
			ft_putstr(" ");
			j++;
		}
		ft_putendl(")");
		i++;
	}
	ft_putendl("");
}

void	print_triangle_v2int(t_vector_2_int pos1, t_vector_2_int pos2,
								t_vector_2_int pos3, int debug_lvl)
{
	if (debug_lvl < DEBUG_LEVEL)
		return ;
	ft_putstr("(");
	ft_putnbr(pos1.x);
	ft_putstr(":");
	ft_putnbr(pos1.y);
	ft_putstr(") ");
	ft_putstr("(");
	ft_putnbr(pos2.x);
	ft_putstr(":");
	ft_putnbr(pos2.y);
	ft_putstr(") ");
	ft_putstr("(");
	ft_putnbr(pos3.x);
	ft_putstr(":");
	ft_putnbr(pos3.y);
	ft_putstr(") ");
	ft_putendl(" #");
}

void	print_array(int **arr, int h, int w, int debug_lvl)
{
	int i;
	int j;

	if (debug_lvl < DEBUG_LEVEL)
		return ;
	ft_putendl("");
	ft_putendl("Parsed map:");
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			ft_putnbr(arr[i][j]);
			ft_putchar(' ');
			j++;
		}
		i++;
		ft_putendl("");
	}
}

void	print_array_element(int **arr, int i, int j, int debug_lvl)
{
	if (debug_lvl < DEBUG_LEVEL)
		return ;
	ft_putstr("(");
	ft_putnbr(i);
	ft_putstr(":");
	ft_putnbr(j);
	ft_putstr(")");
	ft_putstr(" = ");
	ft_putnbr(arr[i][j]);
	ft_putendl("");
}

void	print_str(char *str, int debug_lvl)
{
	if (debug_lvl < DEBUG_LEVEL)
		return ;
	ft_putstr(str);
}

void	print_nbr(int nbr, int debug_lvl)
{
	if (debug_lvl < DEBUG_LEVEL)
		return ;
	ft_putnbr(nbr);
}