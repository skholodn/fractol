/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 19:08:58 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/24 19:09:22 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void get_zoom(int x, int y, t_map *map, double zoom)
{
	t_fract *xi;
	double x_crd;
	double y_crd;

	xi = map->f;
//    x_crd = ((xi->max_re - xi->min_re) * x / WIN_LEN) + xi->min_re;
//   y_crd = ((xi->max_im - xi->min_im) * y / WIN_H) + xi->min_im;
	x_crd = xi->min_re + xi->re_factor * x;
	y_crd = xi->min_im + xi->im_factor * y;
	xi->min_re = xi->min_re * zoom + x_crd * (1 - zoom);
	xi->max_re = xi->max_re * zoom + x_crd * (1 - zoom);
	xi->min_im = xi->min_im * zoom + y_crd * (1 - zoom);
	xi->max_im = xi->max_im * zoom + y_crd * (1 - zoom);
	 create_new_img(map);
//	map->img = mlx_new_image(map->mlx, WIN_LEN, WIN_H);
//	map->data = mlx_get_data_addr(map->img, &(map->bpp),
//	                              &(map->size_line), &(map->endian));
}

int mouse_func(int key, int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || x > WIN_LEN || y > WIN_H)
		return (0);
	if (key == 4)
	{
		get_zoom(x, y, map, 0.9);
		map->init = 1;
		fract_switch(map, map->argv);
	}
	else if (key == 5)
	{
		get_zoom(x, y, map, 1.1);
		map->init = 1;
		fract_switch(map, map->argv);
	}
	return (0);
}
