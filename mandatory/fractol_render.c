/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:34:30 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/09 02:14:20 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_color(int iter, t_fractal *frac)
{
	int	red;
	int	green;
	int	blue;

	red = (iter * frac->red_mul) % 256;
	green = (iter * frac->green_mul) % 256;
	blue = (iter * frac->blue_mul) % 256;
	return ((red << 16) | (green << 8) | blue);
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
	z.re = ft_scale(x, -2, 2, HEIGHT) * frac->zoom;
	z.im = ft_scale(y, 2, -2, HEIGHT) * frac->zoom;
	type_config(&z, &c, frac);
	while (i < frac->iters)
	{
		z = sum_z(pow_z(z), c);
		if ((z.re * z.re) + (z.im * z.im) > 4)
		{
			color = create_color(i, frac);
			put_pixel(x, y, color, &frac->img);
			return ;
		}
		i++;
	}
	color = 0;
	if (!ft_strcmp(frac->name, "julia"))
		color = create_color(i, frac);
	put_pixel(x, y, color, &frac->img);
}
