/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 13:25:59 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/24 13:26:04 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fract	*jul_init(void)
{
	 t_fract	*x;

	 x = malloc(sizeof(t_fract));
	 x->min_re = -1.4;
	 x->max_re = 1.4;
	 x->min_im = -1.4;
	 x->max_im = 1.4;
	 x->z_re = 0.0;
	 x->z_im = 0.0;
	 x->z_re1 = 0.0;
	 x->z_im1 = 0.0;
	 x->c_im = 0.27015;
	 x->c_re = -0.7;
	 x->move_x = 0;
	 x->move_y = 0;
	 x->i = 0;
	 x->j = 0;
	 x->k = 0;
	 return (x);
}

void    julia_fract(t_map *map)
{
	!map->init ? map->f = jul_init() : 0;
	map->f->i = 0;
	map->f->re_factor = (map->f->max_re - map->f->min_re) / (WIN_LEN - 1);
	map->f->im_factor = (map->f->max_im - map->f->min_im) / (WIN_H - 1);
	while (map->f->i < WIN_H) // 800
	{
		map->f->j = -1;
		while (++map->f->j < WIN_LEN) // 800
		{
			map->f->z_re = map->f->j * (map->f->max_re - map->f->min_re) / WIN_LEN + map->f->min_re;
			map->f->z_im = map->f->i * (map->f->max_re - map->f->min_re) / WIN_H + map->f->min_im;
			map->f->k = -1;
			while (++map->f->k < map->iter) // iterations
			{
				if (fabs(map->f->z_im * map->f->z_im + map->f->z_re * map->f->z_re) > 4)
					break;
				map->f->z_re1 = map->f->z_re;
				map->f->z_im1 = map->f->z_im;
				map->f->z_re = map->f->z_re1 * map->f->z_re1 - map->f->z_im1 * map->f->z_im1 + map->f->c_re;
				map->f->z_im = 2.0 * map->f->z_re1 * map->f->z_im1 + map->f->c_im;
			}
			set_col(map->f->k, map->f->j, map->f->i, map);
		}
		map->f->i++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
}

void	change_jul(int x, int y, t_map *map)
{
	 if (x > 0 && x < WIN_LEN && y > 0 && y < WIN_H && map->jul_change)
	 {
		map->f->c_re = -((double)x / WIN_LEN);
		map->f->c_im = ((double)y / WIN_H);
		map->init = 1;
		create_new_img(map);
		fract_switch(map, map->argv);
	 }
}