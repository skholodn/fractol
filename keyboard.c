/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 12:22:07 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/27 12:22:25 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int 	my_key_func(int keycode, t_map *map)
{
	 get_move(keycode, map);
	 if (keycode == 53)
		  exit(0);
	 jul_mode(keycode, map);
	 change_iter(keycode, map);
	 //make_change(map);
	 return (0);
}

void	jul_mode(int keycode, t_map *map)
{
	if (keycode == 24)
		 map->jul_change = 1;
	else if (keycode == 27)
		 map->jul_change = 0;
}

void	change_iter(int keycode, t_map *map)
{
	 if (keycode == 69)
	 {
		  map->iter < 600 ? map->iter += 10 : 0;
		  create_new_img(map);
		  map->init = 1;
		  fract_switch(map, map->argv);
	 }
	 else if (keycode == 78)
	 {
		  map->iter > 50 ? map->iter -= 10 : 0;
		  create_new_img(map);
		  map->init = 1;
		  fract_switch(map, map->argv);
	 }
}

void	create_new_img(t_map *map)
{
	 map->img = mlx_new_image(map->mlx, WIN_LEN, WIN_H);
	 map->data = mlx_get_data_addr(map->img, &(map->bpp),
											 &(map->size_line), &(map->endian));
}

void	get_move(int keycode, t_map *map)
{
	map->f->move_x = 0.0;
	map->f->move_y = 0.0;
	if (keycode == 126)
		 map->f->move_y = -0.2 * (map->f->max_im - map->f->min_im);
	else if (keycode == 125)
		 map->f->move_y = 0.2 * (map->f->max_im - map->f->min_im);
	else if (keycode == 123)
		 map->f->move_x = -0.2 * (map->f->max_re - map->f->min_re);
	else if (keycode == 124)
		 map->f->move_x = 0.2 * (map->f->max_re - map->f->min_re);
	 if (keycode == 126 || keycode == 125 || keycode == 123 || keycode == 124)
	 {
		  map->f->min_re += map->f->move_x;
		  map->f->max_re += map->f->move_x;
		  map->f->min_im += map->f->move_y;
		  map->f->max_im += map->f->move_y;
		  create_new_img(map);
		  map->init = 1;
		  fract_switch(map, map->argv);
	 }
}