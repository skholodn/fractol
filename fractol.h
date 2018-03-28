/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/23 16:16:48 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/23 16:17:17 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <string.h>

# define WIN_LEN    800
# define WIN_H      800
# define RAD        0.01745f

int ft_strcmp(const char *s1, const char *s2);

typedef struct	s_fract
{
	double min_re;
	double max_re;
	double min_im;
	double max_im;
	double re_factor;
	double im_factor;
	double z_re;
	double z_im;
	double z_re1;
	double z_im1;
	double c_im;
	double c_re;
	double move_x;
	double move_y;
	int i;
	int j;
	int k;
}					t_fract;

typedef struct	s_map
{
	void *mlx;
	void *win;
	void *img;
	char *data;
	int bpp;
	int size_line;
	int endian;
	t_fract *f;
	int iter;
	int jul_change;
	//double *color;
	int init;
	char **argv;
}					t_map;

t_map *map_init(t_map *map, char **argv);
void fract_switch(t_map *map, char **argv);
void mand_fract(t_map *map);
void julia_fract(t_map *map);
void burn_fract(t_map *map);
void peacock_fract(t_map *map);
void set_col(int k, int x, int y, t_map *map);

void	create_new_img(t_map *map);
void	change_jul(int x, int y, t_map *map);
void	jul_mode(int keycode, t_map *map);
void	change_iter(int keycode, t_map *map);

int mouse_func(int key, int x, int y, t_map *map);
int 	my_key_func(int keycode, t_map *map);
void	get_move(int keycode, t_map *map);

int ft_strcmp(const char *s1, const char *s2);
size_t ft_strlen(const char *s);
void print_error(char *str);


#endif