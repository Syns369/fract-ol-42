/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 14:57:14 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/07 16:25:51 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

double	ft_atof(const char *str)
{
	double	int_part;
	double	dec_part;
	double	sign;
	int		i;
	int		exp;

	int_part = 0.0;
	dec_part = 0.0;
	sign = 1.0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1.0;
	while (ft_isdigit(str[i]))
		int_part = int_part * 10 + (str[i++] - '0');
	exp = -1;
	if (str[i] == '.' && ft_isdigit(str[i + 1]))
		i++;
	while (ft_isdigit(str[i]))
		dec_part += (pow(10, exp--) * (str[i++] - '0'));
	return (sign * (int_part + dec_part));
}

int	ft_isfloat(const char *str)
{
	int	dot_count;
	int	i;

	dot_count = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) || str[i] == '.')
		if (str[i++] == '.')
			dot_count++;
	return (dot_count <= 1 && i == (int)ft_strlen(str));
}
