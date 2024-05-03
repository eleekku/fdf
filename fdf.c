/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:13:03 by esalmela          #+#    #+#             */
/*   Updated: 2024/03/14 13:49:03 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	allocate_memory(t_map *map)
{
	int	i;

	map->field = malloc(sizeof(int *) * map->size_y);
	if (!map->field)
		free_map(map, 1);
	i = 0;
	while (i < map->size_y)
	{
		map->field[i] = malloc(sizeof(int) * map->size_x);
		if (!map->field[i])
			free_map(map, 1);
		i++;
	}
	i = 0;
	map->colors = malloc(sizeof(int *) * map->size_y);
	if (!map->colors)
		free_map(map, 1);
	while (i < map->size_y)
	{
		map->colors[i] = malloc(sizeof(int) * map->size_x);
		if (!map->colors[i])
			free_map(map, 1);
		i++;
	}
}

void	read_map(char *file, t_map *map)
{
	int		fd;
	int		i;
	int		j;
	char	**values;
	char	*valuestring;

	i = 0;
	j = 0;
	allocate_memory(map);
	fd = open(file, O_RDONLY);
	while (i < map->size_y)
	{
		valuestring = get_next_line(fd);
		values = ft_split(valuestring, ' ');
		if (!values)
		free_map(map, 1);
		free(valuestring);
		store_data(map, i, values);
		free(values);
		i++;
	}
	close(fd);
}

void	free_map(t_map *map, int error)
{
	int	i;

	if (map != NULL)
	{
		if (map->field != NULL)
		{
			i = 0;
			while (i < map->size_y)
			{
				if (map->field[i])
					free(map->field[i]);
				if (map->colors[i])
					free(map->colors[i]);
				i++;
			}
			free(map->field);
			free(map->colors);
		}
	}
	if (error > 0)
	{
		if (map->mlx)
			mlx_close_window(map->mlx);
		exit(1);
	}
}

t_map	parse_map(char *file)
{
	t_map	map;
	char	*line;
	int		fd;

	map.size_x = 0;
	map.size_y = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		exit(1);
	}
	while (line)
	{
		map.size_x = count_values(line, ' ');
		map.size_y++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	read_map(file, &map);
	return (map);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc == 2)
	{
		map = parse_map(argv[1]);
		map.mlx = mlx_init(WIDTH + 50, HEIGHT + 50, "fdf", true);
		if (!map.mlx)
			free_map(&map, 1);
		map.img = mlx_new_image(map.mlx, WIDTH, HEIGHT);
		if (!map.img)
			free_map(&map, 1);
		map.key = 0;
		if (mlx_image_to_window(map.mlx, map.img, 25, 25) == -1)
			free_map(&map, 1);
		ft_memset(map.img->pixels, 50, WIDTH * HEIGHT * sizeof(int32_t));
		draw_map(&map);
		mlx_key_hook(map.mlx, &ft_hook, &map);
		mlx_scroll_hook(map.mlx, &my_scrollhook, &map);
		mlx_loop(map.mlx);
		mlx_terminate(map.mlx);
		free_map(&map, 0);
	}
	return (0);
}
