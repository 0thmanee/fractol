/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:34:30 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/07 23:35:04 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
}

void	put_pixel(int x, int y, int color, t_image *img)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pxls_ptr + offset) = color;
}

void	render_pixel(double x, double y, t_fractal *frac)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.re = 0.0;
	z.im = 0.0;
	i = 0;
	c.re = ft_scale(x, -2, 2, 0, HEIGHT) * frac->zoom;
	c.im = ft_scale(y, 2, -2, 0, HEIGHT) * frac->zoom;
	while (i < frac->iters)
	{
		z = sum_z(pow_z(z), c);
		if ((z.re * z.re) + (z.im * z.im) > 4)
		{
			color = ft_scale(i, BLACK, WHITE, 0, frac->iters);
			put_pixel(x, y, color, &frac->img);
			return ;
		}
		i++;
	}
	color = WHITE;
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
	mlx_put_image_to_window(frac->mlx_ptr, frac->win_ptr, frac->img.img_ptr, 0, 0);
}
