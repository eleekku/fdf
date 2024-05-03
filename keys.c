/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:44:47 by esalmela          #+#    #+#             */
/*   Updated: 2024/03/12 18:46:41 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	movement(t_map *map, int direction)
{
	map->key = 1;
	ft_memset(map->img->pixels, 50, WIDTH * HEIGHT * sizeof(int32_t));
	if (direction == 1)
	{
		map->movev += +10;
		map->moveh += +10;
	}
	if (direction == 2)
	{
		map->movev += -10;
		map->moveh += -10;
	}
	if (direction == 3)
	{
		map->moveh += -10;
		map->movev += +10;
	}
	if (direction == 4)
	{
		map->moveh += +10;
		map->movev += -10;
	}
	draw_map(map);
}

void	ft_zoom(t_map *map, int i)
{
	map->key = 1;
	ft_memset(map->img->pixels, 50, WIDTH * HEIGHT * sizeof(int32_t));
	if (i > 0)
	{
		if (map->diameter > 1)
		{
			map->zoom -= (map->diameter / 10);
			if (map->zoom <= 0)
				map->zoom -= 1;
		}
	}
	if (i < 0)
	{
		if (map->diameter < WIDTH)
			map->zoom += map->diameter / 10;
		if (map->zoom <= 0)
			map->zoom += 1;
	}
	draw_map(map);
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_map	*map;

	map = param;
	(void)map;
	(void)xdelta;
	if (ydelta > 0)
		ft_zoom(map, 1);
	if (ydelta < 0)
		ft_zoom(map, -1);
}

void	modify_altitude(t_map *map, int i)
{
	map->key = 1;
	ft_memset(map->img->pixels, 50, WIDTH * HEIGHT * sizeof(int32_t));
	if (i > 0)
		map->adjust += 1;
	else if (i < 0)
		map->adjust -= 1;
	draw_map(map);
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_map	*map;

	map = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(map->mlx);
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		movement(map, 1);
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		movement(map, 2);
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		movement(map, 3);
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		movement(map, 4);
	if (keydata.key == MLX_KEY_1 && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		modify_altitude(map, 1);
	if (keydata.key == MLX_KEY_2 && (keydata.action == MLX_PRESS
			|| keydata.action == MLX_REPEAT))
		modify_altitude(map, -1);
}
