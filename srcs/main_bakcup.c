/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:53:43 by jdarcour          #+#    #+#             */
/*   Updated: 2023/05/16 01:06:56 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft_42/libft.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_callback_data{
	void	*mlx;
	void	*mlx_win;
}	t_callback_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	deal_key(int key, void *param)
{
	t_callback_data	*data;
	void			*mlx;
	void			*mlx_win;

	data = (t_callback_data *)param;
	mlx = data->mlx;
	mlx_win = data->mlx_win;
	ft_putnbr_fd(key, 1);
	if (key == 65307)
	{
		mlx_destroy_window(mlx, mlx_win);
		exit(0);
	}
	return (0);
}

int	deal_click(int button, int x, int y, void *param)
{
	t_callback_data	*data;
	void			*mlx;
	void			*mlx_win;

	data = (t_callback_data *)param;

	mlx = data->mlx;
	mlx_win = data->mlx_win;
	ft_putnbr_fd(button, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(x, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(y, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int	plot_mandelbrot(double x0, double y0, int max_iteration)
{
	double	x;
	double	y;
	double	xtemp;
	int		iteration;

	x = 0.0;
	y = 0.0;
	iteration = 0;

	while (x * x + y * y <= 2 * 2 && iteration < max_iteration)
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

int	plot_julia(double x0, double y0, int max_iteration)
{
	double	cx;
	double	cy;
	double	xtemp;
	int		iteration;

	cx = -0.7;
	cy = 0.27015;
	iteration = 0;
	while (x0 * x0 + y0 * y0 <= 2 * 2 && iteration < max_iteration)
	{
		xtemp = x0 * x0 - y0 * y0 + cx;
		y0 = 2 * x0 * y0 + cy;
		x0 = xtemp;
		iteration++;
	}
	return (iteration);
}

int	plot_burningShip(double x0, double y0, int max_iteration)
{
	double	x;
	double	y;
	double	xtemp;
	int		iteration;

	x = 0.0;
	y = 0.0;
	iteration = 0;
	while (x * x + y * y <= 2 * 2 && iteration < max_iteration)
	{
		xtemp = x * x - y * y + x0;
		y = fabs(2 * x * y) + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

void generate_palette(int palette[], int max_iteration)
{
	for (int i = 0; i < max_iteration; i++)
	{
		// Calculate the color based on the iteration count
		double t = (double)i / max_iteration;  // Normalize the iteration count
		int red = (int)(9 * (1 - t) * t * t * t * 255);
		int green = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
		int blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

		// Combine the color channels into a single integer value
		int color = (red << 16) | (green << 8) | blue;

		// Store the color in the palette array
		palette[i] = color;
	}
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int		width;
	int		height;
	int		max_iteration;
	void	*mlx_ptr;
	void	*win_ptr;
	t_callback_data	data;
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
	int 	py;
	int 	px;
	double	x0;
	double	y0;

	// mandelbrot set
	min_x = -2;
	max_x = 0.47;
	min_y = -1.12;
	max_y = 1.12;


	width = 1000;
	height = 1000;
	max_iteration = 100;

	int 	palette[max_iteration];
	generate_palette(palette, max_iteration);

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, height, "mlx 42");

	data.mlx = mlx_ptr;
	data.mlx_win = win_ptr;

	img.img = mlx_new_image(data.mlx, width, height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	py = 0;
	while (py < height)
	{
		px = 0;
		while (px < width)
		{
			x0 = (double)px / width * (max_x - min_x) + min_x;
			y0 = (double)py / height * (max_y - min_y) + min_y;
			
			// int iteration = plot_burningShip(x0, y0, max_iteration);
			int iteration = plot_julia(x0, y0, max_iteration);
			// int iteration = plot_mandelbrot(x0, y0, max_iteration);
			
			int color = palette[iteration];
			my_mlx_pixel_put(&img, px, py, color);
			px++;
		}
		py++;
	}
	mlx_put_image_to_window(data.mlx, data.mlx_win, img.img, 0, 0);
	mlx_key_hook(data.mlx_win, deal_key, (void *)&data);
	mlx_mouse_hook(data.mlx_win, deal_click, (void *)&data);
	mlx_loop(data.mlx);
}