/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:18:53 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/08 12:38:57 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	error_message(char **argv, t_mlx_data *data)
{
	ft_printf("Usage: %s <fractal_type> [additional_parameters]\n", argv[0]);
	ft_printf("Available fractal types:\n");
	ft_printf("  m - mandelbrot\n");
	ft_printf("  j - julia\n");
	ft_printf("  b - burningship\n");
	ft_printf("  t - tricorn\n");
	ft_printf("Additional parameters for julia:\n");
	ft_printf("must be float values\n");
	ft_printf("  - julia_cx\n");
	ft_printf("  - julia_cy\n");
	free(data);
	exit(EXIT_FAILURE);
}

void	julia_parse(int argc, char **argv, t_mlx_data *data)
{
	if (argc == 4)
	{
		if (ft_isfloat(argv[2]) && ft_isfloat(argv[3]))
		{
			ft_printf("julia_cx: %f\n", ft_atof(argv[2]));
			ft_printf("julia_cy: %f\n", ft_atof(argv[3]));
			data->julia_cx = ft_atof(argv[2]);
			data->julia_cy = ft_atof(argv[3]);
		}
		else
			error_message(argv, data);
	}
	else if (argc == 3)
		error_message(argv, data);
	else
	{
		data->julia_cx = -0.765000;
		data->julia_cy = -0.310000;
	}
}

void	mandel_parse(int argc, char **argv, t_mlx_data *data)
{
	if (argc > 2)
	{
		if (ft_strcmp(argv[2], "p") == 0)
			data->use_power = 1;
		else
			error_message(argv, data);
	}
	else
		data->use_power = 0;
	if (ft_strcmp(argv[1], "m") == 0)
		data->fractal_type = 1;
	else if (ft_strcmp(argv[1], "b") == 0)
		data->fractal_type = 3;
	else if (ft_strcmp(argv[1], "t") == 0)
		data->fractal_type = 4;
	else
		error_message(argv, data);
}

void	parse(int argc, char **argv, t_mlx_data *data)
{
	if (argc < 2)
		error_message(argv, data);
	if (ft_strcmp(argv[1], "j") == 0)
	{
		data->fractal_type = 2;
		julia_parse(argc, argv, data);
	}
	else
		mandel_parse(argc, argv, data);
}
