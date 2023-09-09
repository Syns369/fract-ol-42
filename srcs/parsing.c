/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:18:53 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/09 17:29:30 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	print_controls(void)
{
	ft_printf("\n+===============  Controls  =========================+\n");
	ft_printf("Arrow keys\t\tMove view.\n");
	ft_printf("Scroll wheel\t\tZoom in/out.\n");
	ft_printf("F\t\t\tReset view.\n");
	ft_printf("5 (numpad)\t\tChange color schemes.\n");
	ft_printf("4, 8, 6, 2 (numpad)\tAnimate Julia\n");
	ft_printf("S / D\t\t\tStep anim Julia.\n");
	ft_printf("P / O\t\t\tChange power (not for julia).\n");
	ft_printf("+ / -\t\t\tChange max iteration.\n");
	ft_printf("ESC or close window\tQuit fract'ol.\n");
	ft_printf("+====================================================+\n");
}

void	error_message(t_mlx_data *data)
{
	ft_printf("\nUsage: ./fractol <fractal_type> [additional_parameters]\n\n");
	ft_printf("Available fractal :\n\n");
	ft_printf("  m - mandelbrot\n");
	ft_printf("  j - julia\n");
	ft_printf("  b - burningship\n");
	ft_printf("  t - tricorn\n\n");
	ft_printf("For all fractals (exept julia) you can put the ");
	ft_printf("letter 'p' after the fractal type to use power :\n\n");
	ft_printf("Example : ./fractol m p\n\n");
	ft_printf("For Julia, you can specify starting values ");
	ft_printf("for the initial fractal shape :\n\n");
	ft_printf("You can put integer and float values\n\n");
	ft_printf("Example : ./fractol j -0.765000 -1\n");
	print_controls();
	free(data);
	exit(EXIT_FAILURE);
}

void	julia_parse(int argc, char **argv, t_mlx_data *data)
{
	data->fractal_type = 2;
	if (argc == 4)
	{
		if (ft_isfloat(argv[2]) && ft_isfloat(argv[3]))
		{
			data->julia_cx = ft_atof(argv[2]);
			data->julia_cy = ft_atof(argv[3]);
		}
		else
			error_message(data);
	}
	else if (argc == 3)
		error_message(data);
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
			error_message(data);
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
		error_message(data);
}

void	parse(int argc, char **argv, t_mlx_data *data)
{
	if (argc < 2)
		error_message(data);
	if (ft_strcmp(argv[1], "j") == 0)
		julia_parse(argc, argv, data);
	else
		mandel_parse(argc, argv, data);
}
