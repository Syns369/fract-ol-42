/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:18:53 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/07 12:27:57 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	error_message(char **argv)
{
	printf("Usage: %s <fractal_type> [additional_parameters]\n", argv[0]);
	printf("Available fractal types:\n");
	printf("  m - mandelbrot\n");
	printf("  j - julia\n");
	printf("  b - burningship\n");
	printf("  t - tricorn\n");
	printf("Additional parameters for julia:\n");
	printf("must be float values\n");
	printf("  - julia_cx\n");
	printf("  - julia_cy\n");
	exit(EXIT_FAILURE);
}

void	julia_parse(int argc, char **argv, t_mlx_data *data)
{
	if (argc == 4)
	{
		if (ft_isfloat(argv[2]) && ft_isfloat(argv[3]))
		{
			printf("julia_cx: %f\n", ft_atof(argv[2]));
			printf("julia_cy: %f\n", ft_atof(argv[3]));
			data->julia_cx = ft_atof(argv[2]);
			data->julia_cy = ft_atof(argv[3]);
		}
		else
			error_message(argv);
	}
	else if (argc == 3)
		error_message(argv);
	else
	{
		data->julia_cx = -0.8;
		data->julia_cy = 0.156;
	}
}

void	parse(int argc, char **argv, t_mlx_data *data)
{
	if (argc < 2)
		error_message(argv);
	if (strcmp(argv[1], "m") == 0)
		data->fractal_name = "mandelbrot";
	else if (strcmp(argv[1], "b") == 0)
		data->fractal_name = "burningship";
	else if (strcmp(argv[1], "t") == 0)
		data->fractal_name = "tricorn";
	else if (strcmp(argv[1], "j") == 0)
	{
		data->fractal_name = "julia";
		julia_parse(argc, argv, data);
	}
	else
		error_message(argv);
}
