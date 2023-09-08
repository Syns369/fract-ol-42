/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 03:30:20 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/08 13:40:21 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	step(t_mlx_data *data, int direction)
{
	data->julia_cx += STEP_FACTOR * direction;
	data->julia_cy += STEP_FACTOR * direction;
}

void	animate(t_mlx_data *data, double *ptr, int direction, double rate)
{
	float	lifespan;

	lifespan = 0.1;
	while (lifespan > 0)
	{
		*ptr += rate * direction;
		update_fractal_image(data);
		lifespan -= 0.001;
	}
}

void	animate_all(t_mlx_data *data, int key)
{
	if (data->fractal_type == 2)
	{
		if (key == 65432)
			animate(data, &data->julia_cx, 1, ANIMATE_JULIA_RATE);
		else if (key == 65430)
			animate(data, &data->julia_cx, -1, ANIMATE_JULIA_RATE);
		else if (key == 65431)
			animate(data, &data->julia_cy, 1, ANIMATE_JULIA_RATE);
		else if (key == 65433)
			animate(data, &data->julia_cy, -1, ANIMATE_JULIA_RATE);
		else if (key == 100)
			step(data, 1);
		else if (key == 115)
			step(data, -1);
	}
	else
	{
		if (key == 112)
			animate(data, &data->power, 1, ANIMATE_POWER_RATE);
		else if (key == 111)
			animate(data, &data->power, -1, ANIMATE_POWER_RATE);
	}
}
