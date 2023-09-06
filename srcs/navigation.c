/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 18:24:50 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/05 18:43:35 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	move_x(t_mlx_data *data, float amount)
{
	double	range;

	range = data->max_x - data->min_x;
	data->min_x += amount * range;
	data->max_x += amount * range;
}

void	move_y(t_mlx_data *data, float amount)
{
	double	range;

	range = data->max_y - data->min_y;
	data->min_y += amount * range;
	data->max_y += amount * range;
}

void	zoom(t_mlx_data *data, double x, double y, double zoom_factor)
{
	double	rel_pos_x;
	double	rel_pos_y;
	double	range_x;
	double	range_y;

	rel_pos_x = x / (double)WIDTH;
	rel_pos_y = y / (double)HEIGHT;
	range_x = data->max_x - data->min_x;
	range_y = data->max_y - data->min_y;
	data->min_x += rel_pos_x * range_x * zoom_factor;
	data->max_x -= (1 - rel_pos_x) * range_x * zoom_factor;
	data->min_y += rel_pos_y * range_y * zoom_factor;
	data->max_y -= (1 - rel_pos_y) * range_y * zoom_factor;
}

int	handle_key(int key, t_mlx_data *data)
{
	printf("key: %d\n", key);
	if (key == 65307)
		close_window(data);
	else
	{
		if (key == 65361)
			move_x(data, -0.1);
		else if (key == 65363)
			move_x(data, 0.1);
		else if (key == 65364)
			move_y(data, 0.1);
		else if (key == 65362)
			move_y(data, -0.1);
		else if (key == 102)
		{
			data->min_x = -2.0;
			data->max_x = 0.47;
			data->min_y = -1.12;
			data->max_y = 1.12;
		}
		update_fractal_image(data);
	}
	return (0);
}

int	handle_mouse(int button, int x, int y, t_mlx_data *data)
{
	if (button == 4)
		zoom(data, x, y, ZOOM_FACTOR);
	else if (button == 5)
		zoom(data, x, y, -ZOOM_FACTOR);
	update_fractal_image(data);
	return (0);
}
