/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:28:10 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/08 22:31:49 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_msg(void)
{
	write(1, "\n\tInvalid Input :?\n\n\
	> ./fractol mandelbort\n\
	> ./fractol julia < re > < im >\n\n", 76);
}

int	close_win(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	exit(EXIT_SUCCESS);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == 53)
	{
		close_win(fractal);
		exit(0);
	}
	else if (keysym == 69)
		fractal->iters += 10;
	else if (keysym == 78)
		fractal->iters -= 10;
	else
		return (0);
	render_img(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == 4)
		fractal->zoom *= 1.05;
	else if (button == 5)
		fractal->zoom *= 0.95;
	else
		return (0);
	render_img(fractal);
	return (0);
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
