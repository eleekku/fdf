/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:46:49 by esalmela          #+#    #+#             */
/*   Updated: 2024/03/12 19:46:50 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_swap(int *a, int *b)
{
	int	t;

	t = *a;
	*a = *b;
	*b = t;
}

void	get_isometric(t_map *map, int z)
{
	map->iso_x0 = (map->x0 - map->y0) * cos(30 * M_PI / 180);
	map->iso_y0 = (map->x0 + map->y0) * sin(30 * M_PI / 180);
	map->iso_x1 = (map->x1 - map->y1) * cos(30 * M_PI / 180);
	map->iso_y1 = ((map->x1 + map->y1) * sin(30 * M_PI / 180)) + z;
}

void	store_data(t_map *map, int i, char **values)
{
	int	j;

	j = 0;
	while (j < map->size_x)
	{
		map->field[i][j] = ft_atoi(values[j]);
		map->colors[i][j] = determine_color(values[j], map->field[i][j]);
		j++;
	}
	j = 0;
	while (values[j] != NULL)
	{
		free(values[j]);
		j++;
	}
}

int	count_values(char *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i] && s[i] == c)
		i++;
	if (s[i])
		words++;
	while (s[i])
	{
		if (s[i] == c)
		{
			words++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (words > 1 && s[i - 2] == c)
		words--;
	return (words);
}

void	call_pixel(t_map *map, int adjust, int i, int j)
{
	int	k;

	k = map->iso_x0 + adjust;
	mlx_put_pixel(map->img, k, map->iso_y0 + (HEIGHT / 4), map->colors[i][j]);
}
