/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:53:43 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/06 04:06:09 by jdarcour         ###   ########.fr       */
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
	if (strcmp(data->fractal_name, "julia") == 0)
	{
		data->min_x = -2.0;
		data->max_x = 2.0;
		data->min_y = -2.0;
		data->max_y = 2.0;
	}
	else
	{
		data->min_x = -2.0;
		data->max_x = 0.47;
		data->min_y = -1.12;
		data->max_y = 1.12;
	}
	data->palette = palette_gen(MAX_ITERATION);
	update_fractal_image(data);
	return (0);
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
			center(data);
		else
			animate(data, key);
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

int	main(int argc, char **argv)
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));
	if (argc < 2)
	{
		printf("Usage: %s <fractal_type> [additional_parameters]\n", argv[0]);
		printf("Available fractal types:\n");
		printf("  m - mandelbrot\n");
		printf("  j - julia\n");
		printf("  b - burningship\n");
		exit(EXIT_FAILURE);
	}
	if (strcmp(argv[1], "m") == 0)
		data->fractal_name = "mandelbrot";
	else if (strcmp(argv[1], "j") == 0)
	{
		data->fractal_name = "julia";
		if (argc == 4)
		{
			data->julia_cx = atof(argv[2]);
			data->julia_cy = atof(argv[3]);
		}
		else
		{
			data->julia_cx = -0.8;
			data->julia_cy = 0.4;
		}
	}
	else if (strcmp(argv[1], "b") == 0)
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
