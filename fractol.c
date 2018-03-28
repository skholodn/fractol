/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:16:17 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/23 16:16:40 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ft_strcmp(const char *s1, const char *s2)
{
	int i;
	unsigned char *ts1;
	unsigned char *ts2;

	i = 0;
	ts1 = (unsigned char *) s1;
	ts2 = (unsigned char *) s2;
	while (ts1[i] && ts2[i] && ts1[i] == ts2[i])
		i++;
	if (ts1[i] != ts2[i])
		return (ts1[i] - ts2[i]);
	return (0);
}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void print_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(-1);
}

void	fract_switch(t_map *map, char **argv)
{
	if (!ft_strcmp(argv[1], "julia"))
		 julia_fract(map);
	else if (!ft_strcmp(argv[1], "mandelbrot"))
		 mand_fract(map);
	else if (!ft_strcmp(argv[1], "burning_ship"))
		 burn_fract(map);
}

t_map *map_init(t_map *map, char **argv)
{
	if (!(map = malloc(sizeof(t_map))))
		print_error("Can't create window!");
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, WIN_LEN, WIN_H, "Fractol");
	create_new_img(map);
	map->init = 0;
	map->argv = argv;
	map->iter = 50;
	map->jul_change = 0;
	fract_switch(map, map->argv);
	return (map);
}

int main(int argc, char **argv)
{
	t_map *map;

	map = NULL;
	if (argc != 2)
		print_error("Need: <fractal name>\n");
	if (!(!ft_strcmp(argv[1], "julia") || !ft_strcmp(argv[1], "mandelbrot")
	      || !ft_strcmp(argv[1], "burning_ship")))
		print_error("Wrong fractol!\nNeed to print:\njulia,\nor mandelbrot,\nor burning_ship.\n");
	map = map_init(map, argv);
	mlx_hook(map->win, 2, 5, my_key_func, map);
	mlx_mouse_hook(map->win, mouse_func, map);
	mlx_hook(map->win, 6, 5, change_jul, map);
	mlx_loop(map->mlx);
	return (0);
}
