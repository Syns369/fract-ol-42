/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:38:55 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/07 18:31:23 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	*palette_gen(double red, double green, double blue)
{
	int		*palette;
	int		i;
	double	t;

	palette = malloc(sizeof(int) * MAX_ITERATION);
	i = 0;
	while (i < MAX_ITERATION)
	{
		t = (double)i / MAX_ITERATION;
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
