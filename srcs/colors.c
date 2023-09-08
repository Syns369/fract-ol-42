/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:38:55 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/08 19:08:29 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	*palette_gen(double red, double green, double blue, int max_iteration)
{
	int		*palette;
	int		i;
	double	t;

	palette = malloc(sizeof(int) * max_iteration);
	i = 0;
	while (i < max_iteration)
	{
		t = (double)i / max_iteration;
		palette[i] = (int)(red * (1 - t) * pow(t, 3) * 255) << 16
			| (int)(green * pow((1 - t), 2) * pow(t, 2) * 255) << 8
			| (int)(blue * pow((1 - t), 3) * t * 255);
		i++;
	}
	return (palette);
}

void	change_palette(t_mlx_data *data)
{
	if (data->current_palette == data->palette1)
		data->current_palette = data->palette2;
	else if (data->current_palette == data->palette2)
		data->current_palette = data->palette3;
	else if (data->current_palette == data->palette3)
		data->current_palette = data->palette1;
}

void	init_palette(t_mlx_data *data)
{
	int	max_iteration;

	max_iteration = data->max_iteration;
	data->palette1 = palette_gen(9, 15, 8.5, max_iteration);
	data->palette2 = palette_gen(10 * 5, 8.43 * 5, 5.42 * 5, max_iteration);
	data->palette3 = palette_gen(38.62, 84.15, 11.77, max_iteration);
	data->current_palette = data->palette1;
}
