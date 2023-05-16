/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:53:43 by jdarcour          #+#    #+#             */
/*   Updated: 2023/05/16 22:32:49 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"
#include "fractals.c"

// typedef struct s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

// typedef struct {
// 	void *mlx;
// 	void *mlx_win;
// } t_callback_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	deal_key(int key, void *param)
{
	void			*mlx;
	void			*mlx_win;
	t_callback_data	*data;

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
	ft_putnbr_fd(button, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(x, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(y, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}



int	main(void)
{
	t_data			img;
	t_callback_data	data;
	int				width;
	int				height;
	double			x0;
	double			y0;
	int				iteration;
	int				px;
	int				py;
	int				color;
	int				max_iteration;
	void			*mlx_ptr;
	void			*win_ptr;

	width = 1000;
	height = 1000;

	// Define the Mandelbrot Set scale
	double min_x = -2.0;
	double max_x = 0.47;
	double min_y = -1.12;
	double max_y = 1.12;

	max_iteration = 100;
	int palette[max_iteration];

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

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, width, height, "Window");

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

			// iteration = plot_mandelbrot(x0, y0, max_iteration);
			iteration = plot_julia(x0, y0, max_iteration);
			//iteration = plot_burningShip(x0, y0, max_iteration);
			color = palette[iteration];
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