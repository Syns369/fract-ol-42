/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:05:29 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/07 16:05:53 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	plot_burningship(double x0, double y0)
{
	double	x;
	double	y;
	double	xtemp;
	int		iteration;

	x = 0.0;
	y = 0.0;
	iteration = 0;
	while (x * x + y * y <= 2 * 2 && iteration < MAX_ITERATION)
	{
		xtemp = x * x - y * y + x0;
		y = fabs(2 * x * y) + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

int	plot_tricorn(double x0, double y0)
{
	double	x;
	double	y;
	double	xtemp;
	int		iteration;

	x = 0.0;
	y = 0.0;
	iteration = 0;
	while (x * x + y * y <= 2 * 2 && iteration < MAX_ITERATION)
	{
		xtemp = x * x - y * y + x0;
		y = -2 * x * y + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}
