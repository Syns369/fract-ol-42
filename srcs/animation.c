/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 03:30:20 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/06 03:54:02 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	animate_julia(t_mlx_data *data, float amount, int direction)
{
	while (amount > 0)
	{
		data->julia_cx += 0.001 * direction;
		data->julia_cy += 0.001 * direction;
		update_fractal_image(data);
		amount -= 0.001;
	}
}

void	step(t_mlx_data *data, int direction)
{
	data->julia_cx += 0.001 * direction;
	data->julia_cy += 0.001 * direction;
}

void	animate(t_mlx_data *data, int key)
{
	if (key == 116 && strcmp(data->fractal_name, "julia") == 0)
		animate_julia(data, 0.1, 1);
	else if (key == 114 && strcmp(data->fractal_name, "julia") == 0)
		animate_julia(data, 0.1, -1);
	else if (key == 117 && strcmp(data->fractal_name, "julia") == 0)
		step(data, 1);
	else if (key == 121 && strcmp(data->fractal_name, "julia") == 0)
		step(data, -1);
}
