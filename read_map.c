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

int		ft_getnbr(char *str, t_vector3 *v3)
{
	int		i;

	i = 0;
	v3->z = ft_atoi(str);
	while (ft_isalnum(*str))
	{
		str++;
		i++;
	}
	if (*str == ',')
	{
		char	*hex;

		str++;
		hex = ft_strcut(str, 8);
		i += 9;
		v3->color = (int)hex2int(hex);
		free(hex);
	}
	else
		v3->color = 0xFFFFFF;
	
	return (i);
}

void	compose_map(char *map, t_fdf *fdf)
{
	int				i;
	int				j;
	t_vector3		*v3;


	i = 0;
	j = 0;
	print_str("\nMapping.\n", 2);
	v3 = ft_memalloc(sizeof(t_vector3));
	while (*map != '\0')
	{
		if (*map == ' ')
		{
			map++;
			continue;
		}
		if (*map == '\n' || j >= fdf->map_w)
		{
			if (*map == '\n')
			{
				print_nbr(i, -1);
				print_str(" - ", -1);
				print_nbr(j, -1);
				print_str(" new line\n", -1);
			}
			while (*map != '\n')
				map++;
			map++;
			if (i + 1 == fdf->map_h)
			{
				print_nbr(i, -1);
				print_str(" - ", -1);
				print_nbr(j, -1);
				print_str(" breaking\n", -1);
				break;
			}
			i++;
			j = 0;
			continue;
		}
		v3->x = j;
		v3->y = i;
		map += ft_getnbr(map, v3);
		//print_v3(*v3, 1);
		fdf->vertices[i * fdf->map_w + j] = *v3;
		print_v3(fdf->vertices[i * fdf->map_w + j], 1);
		print_str(" added\n", 1);
		j++;
	}
	free(v3);
	print_nbr(i * fdf->map_w + j, 2);
	print_str(" map size\n", 2);
	fdf->vertices_count = i * fdf->map_w + j;
	print_nbr(fdf->vertices_count, 2);
	print_str(" map size\n", 2);
	print_str("\nMapping was completed.\n", 2);
}

void	calculate_map_size(const char *str, t_fdf *fdf)
{
	print_str("Map size: ", 2);
	fdf->map_h = ft_wordcount(str, '\n');
	fdf->map_w = ft_strillen(str, '\n', ' ');
	fdf->vertices = (t_vector3*)malloc(fdf->map_h * fdf->map_w * sizeof(t_vector3));
	print_nbr(fdf->map_h, 2);
	print_str(" - ", 2);
	print_nbr(fdf->map_w, 2);
	print_str("\n", 2);
	print_nbr(fdf->map_h * fdf->map_w, 2);
	print_str(" allocated\n", 2);
}

void	read_map(char *map_name, t_fdf *fdf)
{
	int			*fd;
	char		*line;
	char		*result;
	int			status;

	result = ft_strnew(0);
	fd = (int*)malloc(sizeof(int));
	//map_name = "/Users/njacobso/Projects/extra_cube3d/maps/test.fdf";
	*fd = open(map_name, O_RDONLY);
	while ((status = get_next_line(*fd, &line)) > 0)
	{
		result = ft_strjoinc(result, line);
		if (status == 2)
			result = ft_strjoinc(result, "\n");
		ft_strdel(&line);
	}
	close(*fd);
	print_str("\n", 1);
	print_str("Read map: \n", 1);
	print_str(result, 1);
	print_str("\n", 1);
	calculate_map_size(result, fdf);
	compose_map(result, fdf);
	print_nbr(fdf->vertices_count, 2);
	print_str(" vertices added.\n", 2);
	ft_strdel(&result);
	free(fd);
	//ft_strdel(&map_name);
}
