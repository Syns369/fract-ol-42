/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:12:05 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/08 18:37:46 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	plot_mandelbrot(double x0, double y0, t_mlx_data *data)
{
	double	x;
	double	y;
	double	xtemp;
	int		iteration;

	x = 0.0;
	y = 0.0;
	iteration = 0;
	while (x * x + y * y <= 2 * 2 && iteration < data->max_iteration)
	{
		xtemp = x * x - y * y + x0;
		if (data->fractal_type == 1)
			y = 2 * x * y + y0;
		else if (data->fractal_type == 3)
			y = fabs(2 * x * y) + y0;
		else if (data->fractal_type == 4)
			y = -2 * x * y + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

int	plot_mandelbrot_p(double x0, double y0, t_mlx_data *data)
{
	double	x;
	double	y;
	double	xtemp;
	int		iteration;
	double	power;

	x = 0.0;
	y = 0.0;
	iteration = 0;
	while (x * x + y * y <= 2 * 2 && iteration < data->max_iteration)
	{
		power = pow((x * x + y * y), (data->power / 2));
		xtemp = power * cos(data->power * atan2(y, x)) + x0;
		if (data->fractal_type == 1)
			y = power * sin(data->power * atan2(y, x)) + y0;
		else if (data->fractal_type == 3)
			y = fabs(power * sin(data->power * atan2(y, x))) + y0;
		else if (data->fractal_type == 4)
			y = -power * sin(data->power * atan2(y, x)) + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

int	plot_julia(double x0, double y0, t_mlx_data *data)
{
	double	xtemp;
	int		iteration;

	iteration = 0;
	while (x0 * x0 + y0 * y0 <= 2 * 2 && iteration < data->max_iteration)
	{
		xtemp = x0 * x0 - y0 * y0 + data->julia_cx;
		y0 = 2 * x0 * y0 + data->julia_cy;
		x0 = xtemp;
		iteration++;
	}
	return (iteration);
}
