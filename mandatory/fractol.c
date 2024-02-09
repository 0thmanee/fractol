/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:28:10 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/09 02:14:07 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_msg(void)
{
	write(1, "\n\tInvalid Input :?\n\n\
	> ./fractol mandelbort\n\
	> ./fractol julia < re > < im >\n\n", 76);
}

void	fractol_init(t_fractal *frac)
{
	frac->mlx_ptr = mlx_init();
	if (!frac->mlx_ptr)
		exit(EXIT_FAILURE);
	frac->win_ptr = mlx_new_window(frac->mlx_ptr, WIDTH, HEIGHT, frac->name);
	if (!frac->win_ptr)
		exit(EXIT_FAILURE);
	frac->img.img_ptr = mlx_new_image(frac->mlx_ptr, WIDTH, HEIGHT);
	if (!frac->img.img_ptr)
		exit(EXIT_FAILURE);
	frac->img.pxls_ptr = mlx_get_data_addr(frac->img.img_ptr, &frac->img.bpp,
			&frac->img.line_length, &frac->img.endian);
	if (!frac->img.pxls_ptr)
		exit(EXIT_FAILURE);
	frac->iters = 240;
	frac->zoom = 1.0;
	frac->red_mul = 5;
	frac->green_mul = 7;
	frac->blue_mul = 9;
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

int	main(int ac, char *av[])
{
	t_fractal	fractal;

	if ((ac == 2 && !ft_strcmp(av[1], "mandelbrot"))
		|| (ac == 4 && !ft_strcmp(av[1], "julia")))
	{
		if (!ft_strcmp(av[1], "julia"))
		{
			if (invalid_coords(av[2]) || invalid_coords(av[3]))
				(error_msg(), exit(EXIT_FAILURE));
			fractal.julia_x = ft_atoi_double(av[2]);
			fractal.julia_y = ft_atoi_double(av[3]);
		}
		fractal.name = av[1];
		fractol_init(&fractal);
		render_img(&fractal);
		mlx_hook(fractal.win_ptr, 2, 0, key_handler, &fractal);
		mlx_hook(fractal.win_ptr, 17, 0, close_win, &fractal);
		mlx_mouse_hook(fractal.win_ptr, mouse_handler, &fractal);
		mlx_loop(fractal.mlx_ptr);
	}
	else
		(error_msg(), exit(EXIT_FAILURE));
	exit(EXIT_SUCCESS);
}
