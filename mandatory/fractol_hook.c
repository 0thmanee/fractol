/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 00:39:49 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/09 02:09:46 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		exit(EXIT_SUCCESS);
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
