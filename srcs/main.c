/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:53:43 by jdarcour          #+#    #+#             */
/*   Updated: 2023/05/17 01:25:06 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_window(void *param)
{
	t_callback_data	*data;
	void			*mlx;
	void			*mlx_win;

	data = (t_callback_data *)param;
	mlx = data->mlx;
	mlx_win = data->mlx_win;
	mlx_destroy_window(mlx, mlx_win);
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

void	update_fractal_image(void *mlx, void *win, double view_x, double view_y)
{
	t_data	img;
	double	x0, y0;
	int		iteration;
	int		px, py;
	int		color;
	int		*palette;
	double	min_x = -2.0 + view_x;
	double	max_x = 0.47 + view_x;
	double	min_y = -1.12 + view_y;
	double	max_y = 1.12 + view_y;

	palette = palette_gen(MAX_ITERATION);
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	py = 0;
	while (py < HEIGHT)
	{
		px = 0;
		while (px < WIDTH)
		{
			x0 = (double)px / WIDTH * (max_x - min_x) + min_x;
			y0 = (double)py / HEIGHT * (max_y - min_y) + min_y;
			// iteration = plot_mandelbrot(x0, y0, MAX_ITERATION);
			// iteration = plot_julia(x0, y0, MAX_ITERATION);
			iteration = plot_burningship(x0, y0, MAX_ITERATION);
			color = palette[iteration];
			my_mlx_pixel_put(&img, px, py, color);
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_destroy_image(mlx, img.img);
}

int	move_view(int key, void *param)
{
	t_callback_data	*data;

	data = (t_callback_data *)param;
	printf("key: %d\n", key);
	if (key == 65307)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
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
		update_fractal_image(data->mlx, data->mlx_win, data->view_x, data->view_y);
	}
}

int	main(void)
{
	t_data			img;
	t_callback_data	data;
	void			*mlx_ptr;
	void			*win_ptr;
	int				*palette;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WIDTH, HEIGHT, "Window");
	data.mlx = mlx_ptr;
	data.mlx_win = win_ptr;
	data.view_x = 0;
	data.view_y = 0;
	update_fractal_image(mlx_ptr, win_ptr, data.view_x, data.view_y);
	mlx_key_hook(data.mlx_win, move_view, (void *)&data);
	// mlx_key_hook(data.mlx_win, deal_key, (void *)&data);
	mlx_hook(data.mlx_win, 17, 0L, close_window, (void *)&data);
	mlx_loop(data.mlx);
}
