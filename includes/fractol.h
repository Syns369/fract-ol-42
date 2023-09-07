/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:13:55 by jdarcour          #+#    #+#             */
/*   Updated: 2023/09/07 19:19:36 by jdarcour         ###   ########.fr       */
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
# define MOVE_FACTOR 0.05
# define STEP_FACTOR 0.01
# define ANIMATE_FACTOR 0.001

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

	int		*current_palette;
	int		*palette1;
	int		*palette2;
	int		*palette3;

	int		fractal_type;

	double	julia_cx;
	double	julia_cy;

}	t_mlx_data;

int		main(int argc, char **argv);
int		init_fractol_data(t_mlx_data *data);

void	move_x(t_mlx_data *data, float amount);
void	move_y(t_mlx_data *data, float amount);
void	zoom(t_mlx_data *data, double x, double y, double zoom_factor);
void	center(t_mlx_data *data);

int		handle_key(int key, t_mlx_data *data);
int		handle_mouse(int button, int x, int y, t_mlx_data *data);

int		close_window(t_mlx_data *data);

void	animate_juliacx(t_mlx_data *data, int direction);
void	animate_juliacy(t_mlx_data *data, int direction);
void	step(t_mlx_data *data, int direction);
void	animate(t_mlx_data *data, int key);

void	update_fractal_image(t_mlx_data *data);
void	color_pixel(t_mlx_data *data, t_fractol_data *img, int px, int py);
void	my_mlx_pixel_put(t_fractol_data *data, int x, int y, int color);

double	ft_atof(const char *str);
int		ft_isfloat(const char *str);

int		*palette_gen(double red, double green, double blue);
void	change_palette(t_mlx_data *data);

void	julia_parse(int argc, char **argv, t_mlx_data *data);
void	parse(int argc, char **argv, t_mlx_data *data);
void	error_message(char **argv, t_mlx_data *data);

int		plot_mandelbrot(double x0, double y0, int type);
int		plot_julia(double x0, double y0, double cx, double cy);
int		plot_burningship(double x0, double y0);
int		plot_tricorn(double x0, double y0);

#endif