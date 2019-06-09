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
	uint32_t	val;
	uint8_t		byte;

	val = 0;
	while (*hex)
	{
		byte = *hex++;
		if (byte >= '0' && byte <= '9')
			byte = byte - '0';
		else if (byte >= 'a' && byte <= 'f')
			byte = byte - 'a' + 10;
		else if (byte >= 'A' && byte <= 'F')
			byte = byte - 'A' + 10;
		val = (val << 4) | (byte & 0xF);
	}
	return (val);
}

int			ft_getnbr(char *str, t_vector3 *v3)
{
	int		i;
	char	*hex;
	int		*l;

	i = 0;
	l = ft_memalloc(sizeof(int));
	v3->z = ft_atoi(str);
	while (ft_isalnum(*str))
	{
		str++;
		i++;
	}
	if (*str == ',')
	{
		str++;
		hex = ft_strcutc(str, 8, l);
		i += *l + 1;
		v3->color = (int)hex2int(hex);
		free(hex);
	}
	else
		v3->color = 0xFFFFFF;
	return (i);
}

void		compose_map(char *map, t_fdf *fdf)
{
	int				i;
	int				j;
	t_vector3		*v3;

	i = 0;
	j = 0;
	v3 = ft_memalloc(sizeof(t_vector3));
	while (*map != '\0')
	{
		while (*map == ' ')
		{
			map++;
		}
		if (*map == '\n' || j >= fdf->map_w)
		{
			while (*map != '\n')
				map++;
			map++;
			if (i + 1 == fdf->map_h)
				break ;
			i++;
			j = 0;
			continue;
		}
		v3->x = j;
		v3->y = i;
		map += ft_getnbr(map, v3);
		fdf->vertices[i * fdf->map_w + j] = *v3;
		j++;
	}
	free(v3);
	fdf->vertices_count = i * fdf->map_w + j;
}

void		calculate_map_size(const char *str, t_fdf *fdf)
{
	debug_str("Map size: ", 2);
	fdf->map_h = ft_wordcount(str, '\n');
	fdf->map_w = ft_strillen(str, '\n', ' ');
	fdf->vertices = (t_vector3*)malloc(fdf->map_h *
					fdf->map_w * sizeof(t_vector3));
	debug_nbr(fdf->map_h, 2);
	debug_str(" - ", 2);
	debug_nbr(fdf->map_w, 2);
	debug_str("\n", 2);
	debug_nbr(fdf->map_h * fdf->map_w, 2);
	debug_str(" allocated\n", 2);
}

void		read_map(char *map_name, t_fdf *fdf)
{
	int			*fd;
	char		*line;
	char		*result;
	int			status;

	result = ft_strnew(0);
	fd = (int*)malloc(sizeof(int));
	*fd = open(map_name, O_RDONLY);
	while ((status = get_next_line(*fd, &line)) > 0)
	{
		result = ft_strjoinc(result, line);
		if (status == 2)
			result = ft_strjoinc(result, "\n");
		ft_strdel(&line);
	}
	close(*fd);
	debug_str("\n", 1);
	debug_str("Read map: \n", 1);
	debug_str(result, 1);
	debug_str("\n", 1);
	calculate_map_size(result, fdf);
	compose_map(result, fdf);
	debug_str("\nMapping was completed.\n", 2);
	ft_strdel(&result);
	free(fd);
}
