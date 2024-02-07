/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 23:31:43 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/07 23:59:06 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	ft_scale(double v, double mn_n, double mx_n, double min_o, double max_o)
{
	return (mx_n - mn_n) * (v - min_o) / (max_o - min_o) + mn_n;
}

t_complex	sum_z(t_complex z1, t_complex z2)
{
	t_complex	res;

	res.re = z1.re + z2.re;
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
