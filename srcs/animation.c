/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 03:30:20 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/07 22:13:45 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	animate_juliacx(t_mlx_data *data, int direction)
{
	float	lifespan;

	lifespan = 0.1;
	while (lifespan > 0)
	{
		data->julia_cx += ANIMATE_FACTOR * direction;
		update_fractal_image(data);
		lifespan -= 0.001;
	}
}

void	animate_juliacy(t_mlx_data *data, int direction)
{
	float	lifespan;

	lifespan = 0.1;
	while (lifespan > 0)
	{
		data->julia_cy += ANIMATE_FACTOR * direction;
		update_fractal_image(data);
		lifespan -= 0.001;
	}
}

void	step(t_mlx_data *data, int direction)
{
	data->julia_cx += STEP_FACTOR * direction;
	data->julia_cy += STEP_FACTOR * direction;
}

void	animate(t_mlx_data *data, int key)
{
	if (data->fractal_type == 2)
	{
		if (key == 65432)
			animate_juliacx(data, 1);
		else if (key == 65430)
			animate_juliacx(data, -1);
		else if (key == 65431)
			animate_juliacy(data, 1);
		else if (key == 65433)
			animate_juliacy(data, -1);
		else if (key == 100)
			step(data, 1);
		else if (key == 115)
			step(data, -1);
	}
}
