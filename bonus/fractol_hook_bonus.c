/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_hook_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 00:37:42 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/09 00:38:28 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	close_win(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	exit(EXIT_SUCCESS);
}

void	switch_colors(t_fractal *frac)
{
	frac->red_mul = (frac->red_mul + 2) % 8;
	frac->green_mul = (frac->green_mul + 2) % 8;
	frac->blue_mul = (frac->blue_mul + 2) % 8;
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
	else if (keysym == 123)
		fractal->shift_x -= 0.5;
	else if (keysym == 124)
		fractal->shift_x += 0.5;
	else if (keysym == 125)
		fractal->shift_y -= 0.5;
	else if (keysym == 126)
		fractal->shift_y += 0.5;
	else if (keysym == 49)
		switch_colors(fractal);
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
