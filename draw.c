/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:45:59 by esalmela          #+#    #+#             */
/*   Updated: 2024/02/19 17:50:47 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	get_params(t_map *map)
{
	map->difx = map->iso_x1 - map->iso_x0;
	map->dify = map->iso_y1 - map->iso_y0;
	if (map->difx < 0)
		map->difx *= -1;
	if (map->dify < 0)
		map->dify *= -1;
	if (map->iso_x0 < map->iso_x1)
		map->dirx = 1;
	else
		map->dirx = -1;
	if (map->iso_y0 < map->iso_y1)
		map->diry = 1;
	else
		map->diry = -1;
	map->err = map->difx - map->dify;
	return (*map);
}

void	drawline(t_map *map, int row, int slot)
{
	int	adjust;

	if (map->column == 1)
		ft_swap(&row, &slot);
	*map = get_params(map);
	adjust = WIDTH / (map->relative + 1);
	while (map->iso_x0 != map->iso_x1 || map->iso_y0 != map->iso_y1)
	{
		if (map->iso_x0 + adjust < WIDTH
			&& (map->iso_y0 + (HEIGHT / 4)) < HEIGHT
			&& map->iso_x0 + adjust > 0
			&& (map->iso_y0 + (HEIGHT / 4)) > 0)
			call_pixel(map, adjust, row, slot);
		if (-map->dify < (map->err * 2) && map->iso_x0 != map->iso_x1)
		{
			map->err -= map->dify;
			map->iso_x0 += map->dirx;
		}
		if (map->difx > (map->err * 2) && map->iso_y0 != map->iso_y1)
		{
			map->err += map->difx;
			map->iso_y0 += map->diry;
		}
	}
}

void	draw_map(t_map *map)
{
	int	j;

	j = -1;
	map->column = 0;
	map->relative = (float)map->size_x / (float)map->size_y;
	if (map->key == 0)
	{
		map->zoom = 0;
		map->movev = 0;
		map->moveh = 0;
		map->adjust = 1;
	}
	map->diameter = ((map->size_x) * cos(30 * M_PI / 180));
	map->diameter += ((map->size_y) * cos(30 * M_PI / 180)) + map->zoom;
	map->multiplier = (WIDTH / (map->diameter));
	while (++j < map->size_y)
		draw_x(map, j);
	j = -1;
	while (++j < map->size_x)
		draw_y(map, j);
}

void	draw_x(t_map *map, int j)
{
	int	z;
	int	i;

	i = 0;
	map->y0 = j * map->multiplier + map->movev;
	map->y1 = map->y0;
	map->x0 = 0 + map->moveh;
	map->x1 = map->multiplier + map->moveh;
	z = map->field[j][i] * map->adjust;
	get_isometric(map, z);
	map->iso_y0 -= z;
	while (++i < map->size_x)
	{
		map->x1 = i * map->multiplier + map->moveh;
		map->y1 = j * map->multiplier + map->movev;
		z = map->field[j][i] * map->adjust;
		map->iso_x1 = (map->x1 - map->y1) * cos(30 * M_PI / 180);
		map->iso_y1 = ((map->x1 + map->y1) * sin(30 * M_PI / 180)) - z;
		drawline(map, j, i);
	}
}

void	draw_y(t_map *map, int j)
{
	int	z;
	int	i;

	i = 0;
	map->x0 = j * map->multiplier + map->moveh;
	map->x1 = map->x0 + map->moveh;
	map->y0 = 0 + map->movev;
	map->y1 = map->multiplier + map->movev;
	map->column = 1;
	z = map->field[i][j] * map->adjust;
	get_isometric(map, z);
	map->iso_y0 -= z;
	while (++i < map->size_y)
	{
		map->y1 = i * map->multiplier + map->movev;
		map->x1 = j * map->multiplier + map->moveh;
		z = map->field[i][j] * map->adjust;
		map->iso_x1 = (map->x1 - map->y1) * cos(30 * M_PI / 180);
		map->iso_y1 = ((map->x1 + map->y1) * sin(30 * M_PI / 180)) - z;
		drawline(map, j, i);
	}
}
