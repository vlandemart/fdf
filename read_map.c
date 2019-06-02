/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njacobso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:39:36 by njacobso          #+#    #+#             */
/*   Updated: 2019/05/19 15:40:11 by njacobso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	map_to_mesh(int **arr, int h, int w)
{
	int			i;
	int			j;
	t_vector_3	p[3];

	print_str("\nBuilding mesh from map.\n", 2);
	i = 0;
	while (i < h)
	{
		j = 0;
		while (j < w)
		{
			if (i + 1 < h && j + 1 < w)
			{
				p[0] = ft_vector_3_new(i + 1, j, arr[i + 1][j]);
				p[1] = ft_vector_3_new(i, j, arr[i][j]);
				p[2] = ft_vector_3_new(i, j + 1, arr[i][j + 1]);
				add_triangle_to_mesh(ft_triangle_new(p[0], p[1], p[2]));
			}
			else if (i + 1 == h && j + 1 < w)
			{
				p[0] = ft_vector_3_new(i, j + 1, arr[i][j + 1]);
				p[1] = ft_vector_3_new(i, j, arr[i][j]);
				p[2] = ft_vector_3_new(i - 1, j, arr[i - 1][j]);
				add_triangle_to_mesh(ft_triangle_new(p[0], p[1], p[2]));
			}
			else if (i + 1 < h && j + 1 == w)
			{
				p[0] = ft_vector_3_new(i, j - 1, arr[i][j - 1]);
				p[1] = ft_vector_3_new(i, j, arr[i][j]);
				p[2] = ft_vector_3_new(i + 1, j, arr[i + 1][j]);
				add_triangle_to_mesh(ft_triangle_new(p[0], p[1], p[2]));
			}
			j++;
		}
		free(arr[i]);
		i++;
	}
	free(arr);
	print_str("Mesh was built.\n\n", 2);
}

uint32_t	hex2int(char *hex)
{
	uint32_t val = 0;
	while (*hex)
	{
		uint8_t byte = *hex++; 

		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <='f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <='F')
			byte = byte - 'A' + 10;
		val = (val << 4) | (byte & 0xF);
	}
	return val;
}

int		ft_getnbr(char *str, int *num)
{
	//char	*nbr;
	int		i;

	//nbr = ft_strnew(0);
	i = 0;
	*num = ft_atoi(str);
	while (ft_isalnum(*str))
	{
		//nbr = ft_strjoin(nbr, str);
		str++;
		i++;
	}
	if (*str == ',')
	{
		//char	*hex;
		//int		hex_int;

		//str++;
		//hex = ft_strcut(str, 8);
		i += 9;
		/*
		ft_putendl("READ HEX");
		ft_putendl(hex);
		hex_int = (int)hex2int(hex);
		ft_putnbr(((hex_int >> 16) & 0xFF) / 255.0);
		ft_putendl(" r");
		ft_putnbr(((hex_int >> 8) & 0xFF) / 255.0);
		ft_putendl(" g");
		ft_putnbr(((hex_int) & 0xFF) / 255.0);
		ft_putendl(" b");
		*/
	}
	//ft_strdel(&nbr);
	return (i);
}

void	compose_map(char *map, int **arr)
{
	int		i;
	int		j;
	int		w;
	int		num;

	i = 0;
	j = 0;
	w = 0;
	print_str("\nMapping.\n", 2);
	while (*map != '\0')
	{
		if (*map == ' ')
		{
			map++;
			continue;
		}
		if (*map == '\n')
		{
			i++;
			j = 0;
			map++;
			continue;
		}
		map += ft_getnbr(map, &num);
		arr[i][j] = num;
		print_array_element(arr, i, j, 1);

		j++;
		w = (j > w) ? w + 1 : w;
		//map++;
	}
	print_str("\nMapping was completed.\n", 2);
	print_str("Result:\n", 1);
	print_array(arr, i, w, 1);
	map_to_mesh(arr, i, w);
}

int		**allocate_array(const char *str)
{
	int lines;
	int len;
	int i;
	int **arr;

	print_str("\nAllocating memory for array:\n", 2);
	lines = ft_wordcount(str, '\n');
	arr = (int**)ft_memalloc(lines * sizeof(int*));
	print_nbr(lines, 2);
	print_str(" lines alloced with ", 2);
	len = ft_strillen(str, '\n', ' ');
	print_nbr(len, 2);
	print_str(" width.\n", 2);
	i = 0;
	while (i < lines)
	{
		arr[i] = (int*)ft_memalloc(len * sizeof(int));
		i++;
	}
	return (arr);
}

void	read_map(char *map_name)
{
	int			fd;
	char		*line;
	char		*result;
	int			status;
	int			**arr;

	result = ft_strnew(0);
	//map_name = ft_strjoin("maps/", "42.fdf");
	map_name = "/Users/njacobso/Projects/extra_cube3d/maps/elem-col.fdf";
	fd = open(map_name, O_RDONLY);
	while ((status = get_next_line(fd, &line)) > 0)
	{
		result = ft_strjoinc(result, line);
		if (status == 2)
			result = ft_strjoinc(result, "\n");
		ft_strdel(&line);
	}
	close(fd);
	print_str("\n", 1);
	print_str("Read map: \n", 1);
	print_str(result, 1);
	print_str("\n", 1);
	arr = allocate_array(result);
	compose_map(result, arr);
	ft_strdel(&result);
	//ft_strdel(&map_name);
}
