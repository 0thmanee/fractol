/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:34:30 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/08 17:45:15 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

void	fractol_init(t_fractal *frac)
{
	frac->mlx_ptr = mlx_init();
	if (!frac->mlx_ptr)
		return ;
	frac->win_ptr = mlx_new_window(frac->mlx_ptr, WIDTH, HEIGHT, frac->name);
	if (!frac->win_ptr)
		return ;
	frac->img.img_ptr = mlx_new_image(frac->mlx_ptr, WIDTH, HEIGHT);
	if (!frac->img.img_ptr)
		return ;
	frac->img.pxls_ptr = mlx_get_data_addr(frac->img.img_ptr, &frac->img.bpp,
			&frac->img.line_length, &frac->img.endian);
	if (!frac->img.pxls_ptr)
		return ;
	frac->iters = 240;
	frac->zoom = 1.0;
	frac->shift_x = 0.0;
	frac->shift_y = 0.0;
}

void	put_pixel(int x, int y, int color, t_image *img)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pxls_ptr + offset) = color;
}

void	type_config(t_complex *z, t_complex *c, t_fractal *frac)
{
	if (!ft_strcmp(frac->name, "mandelbrot"))
	{
		c->re = z->re;
		c->im = z->im;
	}
	else
	{
		c->re = frac->julia_x;
		c->im = frac->julia_y;
	}
}

void	render_pixel(double x, double y, t_fractal *frac)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.re = (ft_scale(x, -2, 2, HEIGHT) + frac->shift_x) * frac->zoom;
	z.im = (ft_scale(y, 2, -2, HEIGHT) + frac->shift_y) * frac->zoom;
	type_config(&z, &c, frac);
	while (i < frac->iters)
	{
		z = sum_z(pow_z(z), c);
		if ((z.re * z.re) + (z.im * z.im) > 4)
		{
			color = ft_scale(i, BLACK, WHITE, frac->iters);
			put_pixel(x, y, color, &frac->img);
			return ;
		}
		i++;
	}
	color = WHITE;
	if (!ft_strcmp(frac->name, "julia"))
		color = ft_scale(i, GOLD_1, GOLD_2, frac->iters);
	put_pixel(x, y, color, &frac->img);
}

void	render_img(t_fractal *frac)
{
	double	i;
	double	j;

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			render_pixel(i, j, frac);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(frac->mlx_ptr, frac->win_ptr,
		frac->img.img_ptr, 0, 0);
}
