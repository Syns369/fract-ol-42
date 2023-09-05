/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:13:55 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/05 18:32:02 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft_42/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 512
# define HEIGHT 512
# define MAX_ITERATION 100
# define ZOOM_FACTOR 0.1

typedef struct s_fractol_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_fractol_data;

typedef struct s_mlx_data {
	void	*mlx;
	void	*win;

	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;

	void	*palette;
}	t_mlx_data;

void	my_mlx_pixel_put(t_fractol_data *data, int x, int y, int color);
int		plot_mandelbrot(double x0, double y0, int max_iteration);
int		plot_julia(double x0, double y0, int max_iteration);
int		plot_burningship(double x0, double y0, int max_iteration);
int		close_window(t_mlx_data *data);
void	update_fractal_image(t_mlx_data *data);
int		move_view(int key, void *param);
void	*palette_gen(int max_iteration);
int		init_fractol_data(t_mlx_data *data);
int		main(void);

void	move_x(t_mlx_data *data, float amount);
void	move_y(t_mlx_data *data, float amount);
void	zoom(t_mlx_data *data, double x, double y, double zoom_factor);
int		handle_key(int key, t_mlx_data *data);
int		handle_mouse(int button, int x, int y, t_mlx_data *data);
#endif