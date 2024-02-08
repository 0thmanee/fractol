/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:28:05 by obouchta          #+#    #+#             */
/*   Updated: 2024/02/08 17:45:18 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static long	int_part(char **s)
{
	long	int_res;

	int_res = 0;
	while (**s && **s != '.')
	{
		int_res = (int_res * 10) + (**s - 48);
		(*s)++;
	}
	return (int_res);
}

static double	frac_part(char *s)
{
	double	frac;
	double	frac_res;

	frac = 1;
	frac_res = 0;
	if (*s == '.')
		s++;
	while (*s)
	{
		frac /= 10;
		frac_res += (*s - 48) * frac;
		s++;
	}
	return (frac_res);
}

double	ft_atoi_double(char *s)
{
	long	int_res;
	double	frac_res;
	double	frac;
	int		sign;

	sign = 1;
	frac = 1;
	while (*s && (*s == ' ' || (*s >= 9 && *s <= 13)))
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	int_res = int_part(&s);
	frac_res = frac_part(s);
	return ((int_res + frac_res) * sign);
}

int	invalid_coords(char *coord)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	if (coord[i] == '+' || coord[i] == '-')
		i++;
	while (coord[i])
	{
		if (coord[i] != '.' && (coord[i] < '0' || coord[i] > '9'))
			return (1);
		if (coord[i] == '.')
			point++;
		i++;
	}
	if (point > 1)
		return (1);
	return (0);
}
