/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:13:55 by jdarcour          #+#    #+#             */
/*   Updated: 2023/05/17 01:20:10 by jdarcour         ###   ########.fr       */
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

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_callback_data {
	void	*mlx;
	void	*mlx_win;
	double	view_x;
	double	view_y;
}	t_callback_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		plot_mandelbrot(double x0, double y0, int max_iteration);
int		plot_julia(double x0, double y0, int max_iteration);
int		plot_burningship(double x0, double y0, int max_iteration);
int		close_window(void *param);
void	update_fractal_image(void *mlx, void *win, double view_x, double view_y);
int		move_view(int key, void *param);
void	*palette_gen(int max_iteration);
#endif