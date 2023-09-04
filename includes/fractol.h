/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:13:55 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/04 15:37:13 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft_42/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 1000
# define HEIGHT 1000
# define MAX_ITERATION 100
# define ZOOM 1.1

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
	double	view_x;
	double	view_y;

	// double	min_x;
	// double	max_x;
	// double	min_y;
	// double	max_y;

	void	*palette;
	double	zoom;
	double	zoom_center_x;
	double	zoom_center_y;
}	t_mlx_data;

void	my_mlx_pixel_put(t_fractol_data *data, int x, int y, int color);
int		plot_mandelbrot(double x0, double y0, int max_iteration);
int		plot_julia(double x0, double y0, int max_iteration);
int		plot_burningship(double x0, double y0, int max_iteration);
int		close_window(t_mlx_data *data);
void	update_fractal_image(t_mlx_data *data);
int		move_view(int key, void *param);
void	*palette_gen(int max_iteration);
#endif