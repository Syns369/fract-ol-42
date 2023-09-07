/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:01:33 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/07 19:04:03 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	my_mlx_pixel_put(t_fractol_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	color_pixel(t_mlx_data *data, t_fractol_data *img, int px, int py)
{
	double	x0;
	double	y0;
	int		iteration;
	int		*palette;

	iteration = 0;
	x0 = (double)px / WIDTH * (data->max_x - data->min_x) + data->min_x;
	y0 = (double)py / HEIGHT * (data->max_y - data->min_y) + data->min_y;
	palette = data->current_palette;
	if (data->fractal_type == 1)
		iteration = plot_mandelbrot(x0, y0);
	else if (data->fractal_type == 2)
		iteration = plot_julia(x0, y0, data->julia_cx, data->julia_cy);
	else if (data->fractal_type == 3)
		iteration = plot_burningship(x0, y0);
	else if (data->fractal_type == 4)
		iteration = plot_tricorn(x0, y0);
	if (iteration >= MAX_ITERATION)
		my_mlx_pixel_put(img, px, py, 0x000000);
	else
		my_mlx_pixel_put(img, px, py, palette[iteration]);
}

void	update_fractal_image(t_mlx_data *data)
{
	t_fractol_data	*img;
	int				px;
	int				py;

	img = malloc(sizeof(t_fractol_data));
	img->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	py = 0;
	while (py < HEIGHT)
	{
		px = 0;
		while (px < WIDTH)
		{
			color_pixel(data, img, px, py);
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(data->mlx, data->win, img->img, 0, 0);
	mlx_destroy_image(data->mlx, img->img);
	free(img);
	if (data->fractal_type == 2)
	{
		printf("julia_cx: %f\n", data->julia_cx);
		printf("julia_cy: %f\n", data->julia_cy);
	}
}
