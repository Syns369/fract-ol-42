/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:53:43 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/03 22:26:34 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_fractol_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(t_mlx_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	free(data->mlx);
	exit(0);
}

void	*palette_gen(int max_iteration)
{
	int		*palette;
	int		i;
	double	t;

	palette = malloc(sizeof(int) * max_iteration);
	i = 0;
	while (i < max_iteration)
	{
		t = (double)i / max_iteration;
		palette[i] = (int)(9 * (1 - t) * pow(t, 3) * 255) << 16
			| (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255) << 8
			| (int)(8.5 * pow((1 - t), 3) * t * 255);
		i++;
	}
	return (palette);
}

void	update_fractal_image(t_mlx_data *data)
{
	t_fractol_data	img;
	double			x0;
	double			y0;
	int				iteration;
	int				px;
	int				py;
	int				*palette;

	double	min_x = -2.0 + data->view_x;
	double	max_x = 0.47 + data->view_x;
	double	min_y = -1.12 + data->view_y;
	double	max_y = 1.12 + data->view_y;

	img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	py = 0;
	palette = data->palette;

	while (py < HEIGHT)
	{
		px = 0;
		while (px < WIDTH)
		{
			x0 = (double)px / WIDTH * (max_x - min_x) + min_x;
			y0 = (double)py / HEIGHT * (max_y - min_y) + min_y;
			iteration = plot_mandelbrot(x0, y0, MAX_ITERATION);
			// iteration = plot_julia(x0, y0, MAX_ITERATION);
			// iteration = plot_burningship(x0, y0, MAX_ITERATION);
			// color = ;
			my_mlx_pixel_put(&img, px, py, palette[iteration]);
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img.img, 0, 0);
	mlx_destroy_image(data->mlx, img.img);
}

int	handle_key(int key, t_mlx_data *data)
{
	printf("key: %d\n", key);
	if (key == 65307)
	{
		close_window(data);
	}
	else
	{
		if (key == 65361)
			data->view_x -= 0.1;
		else if (key == 65363)
			data->view_x += 0.1;
		else if (key ==	65364)
			data->view_y += 0.1;
		else if (key ==	65362)
			data->view_y -= 0.1;
		update_fractal_image(data);
	}
	return (0);
}

int	handle_mouse(int button, int x, int y, t_mlx_data *data)
{
	printf("button: %d\n", button);
	printf("x: %d\n", x);
	printf("y: %d\n", y);
	if (button == 4)
	{
		
	}
	else if (button == 5)
	{
		
	}
	return (0);
}

int	main(void)
{
	t_mlx_data	*data;

	data = malloc(sizeof(t_mlx_data));

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Window");

	data->view_x = 0;
	data->view_y = 0;
	data->palette = palette_gen(MAX_ITERATION);

	update_fractal_image(data);

	mlx_key_hook(data->win, handle_key, data);
	mlx_mouse_hook(data->win, handle_mouse, data);
	mlx_hook(data->win, 17, 0L, close_window, data);

	mlx_loop(data->mlx);
}
