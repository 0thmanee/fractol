/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:28:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/08 17:45:06 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

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
	double		shift_x;
	double		shift_y;
	double		julia_x;
	double		julia_y;
}	t_fractal;

# define WIDTH 800
# define HEIGHT 800

// Colors

# define BLACK 0x000000
# define WHITE 0xFFFFFF

# define GOLD_1 0xFFCC00
# define GOLD_2 0xFFD700

# define PINK_1 0xFF1493
# define PINK_2 0xFF69B4

# define TEAL_1 0x008080
# define TEAL_2 0x008B8B

# define ORANGE_1 0xFFA500
# define ORANGE_2 0xFF8C00

# define BLUE_1 0xFFA07A
# define BLUE_2 0x4682B4

# define GREEN_1 0x20B2AA
# define GREEN_2 0xFF6347

int			ft_strcmp(const char *s1, const char *s2);
double		ft_atoi_double(char *s);
int			invalid_coords(char *coord);
void		fractol_init(t_fractal *frac);
void		put_pixel(int x, int y, int color, t_image *img);
void		render_pixel(double x, double y, t_fractal *frac);
void		render_img(t_fractal *frac);
double		ft_scale(double v, double mn_n, double mx_n, double max_o);
t_complex	sum_z(t_complex z1, t_complex z2);
t_complex	pow_z(t_complex z);

#endif