/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:28:10 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/04 14:36:42 by obouchta         ###   ########.fr       */
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
	{
		free(frac->mlx_ptr);
		return ;
	}
	frac->img->img_ptr = mlx_new_image(frac->mlx_ptr, WIDTH, HEIGHT);
	if (!frac->img->img_ptr)
	{
		(free(frac->mlx_ptr), free(frac->win_ptr));
		return ;
	}
	frac->img->pxls_ptr = mlx_get_data_addr(frac->img->img_ptr, &frac->img->bpp,
	&frac->img->line_length, &frac->img->endian);
	if (!frac->img->pxls_ptr)
	{
		(free(frac->mlx_ptr), free(frac->win_ptr), free(frac->img->img_ptr));
		return ;
	}
}

double	ft_scale(int val, int min_n, int max_n, int min_o, int max_o)
{
	return (max_n - min_n) * (val - min_o) / (max_o - min_o) + min_n;
}

t_complex	sum_z(t_complex z1, t_complex z2)
{
	t_complex	res;

	res.re = z1.re + z2.im;
	res.im = z1.im + z2.im;
	return (res);
}

t_complex	pow_z(t_complex z)
{
	t_complex	res;

	res.re = (z.re * z.re) - (z.im * z.im);
	res.im = 2 * z.re * z.im;
	return (res);
}

void	put_pixel(double x, double y, int color, t_image *img)
{
	int	offset;

	offset = (y * img->line_length) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pxls_ptr + offset) = color; 
}

void	render_pixel(int x, int y, t_fractal *frac)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.re = 0.0;
	z.im = 0.0;
	i = 0;
	c.re = ft_scale(x, -2, 2, 0, HEIGHT);
	c.im = ft_scale(y, 2, -2, 0, HEIGHT);
	while (i < 50)
	{
		z = sum_z(pow_z(z), c);
		if ((z.re * z.re) * (z.im * z.im) > 4)
		{
			color = ft_scale(i, 0x00000000, 0x00000000, 0, 50);
			put_pixel(x, y, color, frac->img);
			return ;
		}
		i++;
	}
	color = ft_scale(i, 0xffffffff, 0xffffffff, 0, 50);
	put_pixel(x, y, color, frac->img);
}

void	render_img(t_fractal *frac)
{
	int	i;
	int	j;

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
	mlx_put_image_to_window(frac->mlx_ptr, frac->win_ptr, frac->img->img_ptr, WIDTH, HEIGHT);
}

int main(int ac, char *av[])
{
	t_fractal	*fractal;
	
	if ((ac == 2 && ft_strcmp(av[1], "mandelbrot"))
	|| (ac == 4 && ft_strcmp(av[1], "julia")))
	{
		fractal = malloc(sizeof(fractal));
		if (!fractal)
			exit(EXIT_FAILURE);
		fractal->name = av[1];
		fractol_init(fractal);
		render_img(fractal);
	}
}