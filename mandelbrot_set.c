/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 13:26:40 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/24 13:26:42 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void set_col(int k, int x, int y, t_map *map)
{
	if (k == map->iter)
	{
		map->data[y * map->size_line + x * 4] = 0;
		map->data[y * map->size_line + x * 4 + 1] = 0;
		map->data[y * map->size_line + x * 4 + 2] = 0;
	} else
	{
		map->data[y * map->size_line + x * 4] = 50 * (1 - k * 50);
		map->data[y * map->size_line + x * 4 + 1] = 155 * (1 - k * 50);
		map->data[y * map->size_line + x * 4 + 2] = 150 * (1 - k * 50);

//		map->data[y * map->size_line + x * 4] = (unsigned char)(k * 10);
//		map->data[y * map->size_line + x * 4 + 1] = (unsigned char)(k << 8);
//		map->data[y * map->size_line + x * 4 + 2] = (unsigned char)(k * 5 << 16);

//	 map->data[y * map->size_line + x * 4] = (unsigned char)(powf(k, 0.2) * 255 + 0.5);
//	 map->data[y * map->size_line + x * 4 + 1] = (unsigned char)(powf(k, 0.5) * 255 + 0.5);
//	 map->data[y * map->size_line + x * 4 + 2] = (unsigned char)(powf(k, 0.7) * 255 + 0.5);

//		map->data[k * 4] = (unsigned char)(powf(k, 0.2) * 255 + 0.5);
//		map->data[k * 4 + 1] = (unsigned char)(powf(k, 0.4) * 255 + 0.5);
//		map->data[k * 4 + 2] = (unsigned char)(powf(k, 0.8) * 255 + 0.5);
	}
}

t_fract *man_init(void)
{
	 t_fract *x;

	x = malloc(sizeof(t_fract));
	x->min_re = -2.0;
	x->max_re = 1.0;
	x->min_im = -1.5;
	x->max_im = 1.5;
	x->z_re = 0.0;
	x->z_im = 0.0;
	x->z_re1 = 0.0;
	x->z_im1 = 0.0;
	x->c_im = 0.0;
	x->c_re = 0.0;
	x->move_x = 0;
	x->move_y = 0;
	x->i = 0;
	x->j = 0;
	x->k = 0;
	return (x);
}

void mand_fract(t_map *map)
{
	!map->init ? map->f = man_init() : 0;
	map->f->i = 0;
	map->f->re_factor = (map->f->max_re - map->f->min_re) / (WIN_LEN - 1);
	map->f->im_factor = (map->f->max_im - map->f->min_im) / (WIN_H - 1);
	while (map->f->i < WIN_H) // 800
	{
		map->f->c_im = map->f->min_im +  map->f->i * map->f->im_factor;
		map->f->j = -1;
		while (++map->f->j < WIN_LEN) // 800
		{
			map->f->c_re = map->f->min_re + map->f->j * map->f->re_factor;
			map->f->z_im = 0;
			map->f->z_re = 0;
			map->f->k = -1;
			while (++map->f->k < map->iter) // iterations
			{
				if (fabs(map->f->z_im * map->f->z_im + map->f->z_re * map->f->z_re) > 4)
					break;
				map->f->z_im1 = 2 * map->f->z_re * map->f->z_im + map->f->c_im;
				map->f->z_re1 = map->f->z_re * map->f->z_re - map->f->z_im * map->f->z_im + map->f->c_re;
				map->f->z_re = map->f->z_re1;
				map->f->z_im = map->f->z_im1;
			}
			set_col(map->f->k, map->f->j, map->f->i, map);
		}
		map->f->i++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
}