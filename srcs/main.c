/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:53:43 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/09 16:47:57 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	close_window(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data->palette1);
	free(data->palette2);
	free(data->palette3);
	free(data);
	exit(0);
}

int	init_fractol_data(t_mlx_data *data)
{
	data->max_iteration = MAX_ITERATION;
	center(data);
	init_palette(data);
	data->current_palette = &data->palette1;
	data->power = 2.0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Window");
	update_fractal_image(data);
	return (0);
}

int	handle_key(int key, t_mlx_data *data)
{
	if (key == 65307)
		close_window(data);
	else if (key == 65361)
		move_x(data, -MOVE_FACTOR);
	else if (key == 65363)
		move_x(data, MOVE_FACTOR);
	else if (key == 65364)
		move_y(data, MOVE_FACTOR);
	else if (key == 65362)
		move_y(data, -MOVE_FACTOR);
	else if (key == 102)
		center(data);
	else if (key == 65437)
		change_palette(data);
	else if (key == 65453)
		change_iteration(data, -1);
	else if (key == 65451)
		change_iteration(data, 1);
	else
		animate_all(data, key);
	update_fractal_image(data);
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
	parse(argc, argv, data);
	init_fractol_data(data);
	mlx_key_hook(data->win, handle_key, data);
	mlx_mouse_hook(data->win, handle_mouse, data);
	mlx_hook(data->win, 17, 0L, close_window, data);
	mlx_loop(data->mlx);
	return (0);
}
