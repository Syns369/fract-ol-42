/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:12:05 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/08 01:47:24 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	plot_mandelbrot(double x0, double y0, int type)
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
		if (type == 1)
			y = 2 * x * y + y0;
		else if (type == 3)
			y = fabs(2 * x * y) + y0;
		else if (type == 4)
			y = -2 * x * y + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

int	plot_julia(double x0, double y0, double cx, double cy)
{
	double	xtemp;
	int		iteration;

	iteration = 0;
	while (x0 * x0 + y0 * y0 <= 2 * 2 && iteration < MAX_ITERATION)
	{
		xtemp = x0 * x0 - y0 * y0 + cx;
		y0 = 2 * x0 * y0 + cy;
		x0 = xtemp;
		iteration++;
	}
	return (iteration);
}
