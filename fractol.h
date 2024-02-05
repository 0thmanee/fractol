/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:28:14 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/04 14:37:19 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>

typedef struct s_image {
	void	*img_ptr;
	char	*pxls_ptr;
	int		bpp;
	int		line_length;
	int		endian;
} 	t_image;

typedef struct s_complex {
	double	re;
	double	im;
} 	t_complex;

typedef struct s_fractal {
	char		*name;
	void		*mlx_ptr;
	void		*win_ptr;
	t_image		*img;
} 				t_fractal;

#define WIDTH 800
#define HEIGHT 800

int	ft_strcmp(const char *s1, const char *s2);

#endif