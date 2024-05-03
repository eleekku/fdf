/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:27:09 by esalmela          #+#    #+#             */
/*   Updated: 2024/03/12 19:43:35 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "lib/Libft/libft.h"
# include "lib/MLX42/include/MLX42/MLX42.h"

# define WIDTH 1250
# define HEIGHT 1250

typedef struct s_map
{
	unsigned int	**colors;
	int				**field;
	int				size_x;
	int				size_y;
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				iso_x0;
	int				iso_y0;
	int				iso_x1;
	int				iso_y1;
	int				difx;
	int				dify;
	int				dirx;
	int				diry;
	int				err;
	int				column;
	int				multiplier;
	int				diameter;
	float			relative;
	int				adjust;
	int				movev;
	int				moveh;
	int				zoom;
	int				key;
	mlx_image_t		*img;
	mlx_t			*mlx;
}	t_map;

t_map			parse_map(char *file);
void			free_map(t_map *map, int error);
void			read_map(char *file, t_map *map);
void			store_data(t_map *map, int i, char **values);
int				count_values(char *s, char c);
void			draw_map(t_map *map);
void			drawline(t_map *map, int row, int slot);
t_map			get_params(t_map	*map);
void			drawgrid(t_map map);
unsigned int	ft_atoi_base(const char *str, int str_base);
void			draw_x(t_map *map, int j);
void			draw_y(t_map *map, int j);
void			get_isometric(t_map *map, int z);
void			ft_swap(int *a, int *b);
void			ft_hook(mlx_key_data_t keydata, void *param);
int				adjust_altitude(t_map *map);
unsigned int	determine_color(char *str, int z);
unsigned int	check_colors(char *str);
void			my_scrollhook(double xdelta, double ydelta, void *param);
void			ft_zoom(t_map *map, int i);
void			movement(t_map *map, int direction);
void			call_pixel(t_map *map, int adjust, int i, int j);
#endif
