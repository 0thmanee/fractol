/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:28:10 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/07 23:54:12 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_msg(void)
{
	write(1, "\n\tInvalid Input :?\n\n\
	> ./fractol mandelbort\n\
	> ./fractol julia < re > < im >\n\n", 72);
}

int	close_win(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	exit(0);
	return (0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == 53)
	{
		close_win(fractal);
		exit(0);
	}
	if (keysym == 69)
		fractal->iters += 10;
	if (keysym == 78)
		fractal->iters -= 10;
	render_img(fractal);
	return (0);
}

int	mouse_handler(int button, t_fractal *fractal)
{
	if (button == 4)
		fractal->zoom *= 1.05;
	if (button == 5)
		fractal->zoom *= 0.95;
	render_img(fractal);
	return (0);
}

int	main(int ac, char *av[])
{
	t_fractal	fractal;

	if ((ac == 2 && !ft_strcmp(av[1], "mandelbrot"))
		|| (ac == 4 && !ft_strcmp(av[1], "julia")))
	{
		fractal.name = av[1];
		fractol_init(&fractal);
		render_img(&fractal);
		mlx_hook(fractal.win_ptr, 2, 0, &key_handler, &fractal);
		mlx_hook(fractal.win_ptr, 17, 0, &close_win, &fractal);
		// mlx_hook(fractal.win_ptr, 4, 0, &mouse_handler, &fractal);
		mlx_loop(fractal.mlx_ptr);
	}
	else
		error_msg();
	exit(EXIT_SUCCESS);
}
