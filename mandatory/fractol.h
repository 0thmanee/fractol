/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:28:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/09 00:41:03 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <mlx.h>

typedef struct s_image
{
	void	*img_ptr;
	char	*pxls_ptr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_fractal
{
	char		*name;
	void		*mlx_ptr;
	void		*win_ptr;
	int			iters;
	t_image		img;
	double		zoom;
	double		julia_x;
	double		julia_y;
	int			red_mul;
	int			green_mul;
	int			blue_mul;
}	t_fractal;

# define WIDTH 800
# define HEIGHT 800

int			ft_strcmp(const char *s1, const char *s2);
double		ft_atoi_double(char *s);
int			invalid_coords(char *coord);
int			close_win(t_fractal *fractal);
int			key_handler(int keysym, t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
void		fractol_init(t_fractal *frac);
void		put_pixel(int x, int y, int color, t_image *img);
void		render_pixel(double x, double y, t_fractal *frac);
void		render_img(t_fractal *frac);
double		ft_scale(double v, double mn_n, double mx_n, double max_o);
t_complex	sum_z(t_complex z1, t_complex z2);
t_complex	pow_z(t_complex z);

#endif