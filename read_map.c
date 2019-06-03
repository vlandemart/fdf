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

int		ft_getnbr(char *str, t_vector_3 *v3)
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
		/*
		ft_putendl("READ HEX");
		ft_putendl(hex);
		ft_putnbr(((v3->color >> 16) & 0xFF) / 255.0);
		ft_putendl(" r");
		ft_putnbr(((v3->color >> 8) & 0xFF) / 255.0);
		ft_putendl(" g");
		ft_putnbr(((v3->color) & 0xFF) / 255.0);
		ft_putendl(" b");
		*/
	}
	else
		v3->color = 0;
	
	return (i);
}

void	compose_map(char *map, t_fdf *fdf)
{
	int				i;
	int				j;
	t_vector_3		*v3;


	i = 0;
	j = 0;
	print_str("\nMapping.\n", 2);
	v3 = ft_memalloc(sizeof(v3));
	while (*map != '\0')
	{
		if (*map == ' ')
		{
			map++;
			continue;
		}
		if (*map == '\n' || j >= fdf->map_w)
		{
			while (*map != '\n')
				map++;
			i++;
			j = 0;
			map++;
			if (i == fdf->map_h)
				break;
			continue;
		}
		v3->x = j;
		v3->y = i;
		map += ft_getnbr(map, v3);
		print_v3(*v3, 1);
		ft_lstadd(&fdf->vertices, ft_lstnew(v3, sizeof(t_vector_3)));
		print_str(" added\n", 1);
		j++;
	}
	//free(v3);
	print_str("\nMapping was completed.\n", 2);
}

void	calculate_map_size(const char *str, t_fdf *fdf)
{
	print_str("Map size: ", 2);
	fdf->map_h = ft_wordcount(str, '\n');
	fdf->map_w = ft_strillen(str, '\n', ' ');
	print_nbr(fdf->map_h, 2);
	print_str(" - ", 2);
	print_nbr(fdf->map_w, 2);
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
	print_nbr(ft_lstcount(fdf->vertices), 2);
	print_str(" vertices added.\n", 2);
	ft_strdel(&result);
	free(fd);
	//ft_strdel(&map_name);
}
