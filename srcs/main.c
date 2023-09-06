/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:53:43 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/06 02:48:41 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	close_window(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
}

int	init_fractol_data(t_mlx_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Window");
	data->min_x = -2.0;
	data->max_x = 0.47;
	data->min_y = -1.12;
	data->max_y = 1.12;
	data->palette = palette_gen(MAX_ITERATION);
	update_fractal_image(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));
	if (argc < 2)
	{
		printf("Usage: %s <fractal_type> [additional_parameters]\n", argv[0]);
		printf("Available fractal types:\n");
		printf("  - mandelbrot\n");
		printf("  - julia\n");
		printf("  - burningship\n");
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "mandelbrot") == 0)
		data->fractal_name = "mandelbrot";
	else if (strcmp(argv[1], "julia") == 0)
		data->fractal_name = "julia";
	else if (strcmp(argv[1], "burningship") == 0)
		data->fractal_name = "burningship";
	else
	{
		printf("Invalid fractal type: %s\n", argv[1]);
		printf("Available fractal types:\n");
		printf("  - mandelbrot\n");
		printf("  - julia\n");
		printf("  - burningship\n");
		exit(EXIT_FAILURE);
	}

	init_fractol_data(data);
	mlx_key_hook(data->win, handle_key, data);
	mlx_mouse_hook(data->win, handle_mouse, data);
	mlx_hook(data->win, 17, 0L, close_window, data);
	mlx_loop(data->mlx);
	return (0);
}
