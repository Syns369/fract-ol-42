/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarcour <jdarcour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 22:13:55 by jdarcour          #+#    #+#             */
/*   Updated: 2023/05/16 22:21:13 by jdarcour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft_42/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>

# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct {
	void	*mlx;
	void	*mlx_win;
} t_callback_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		deal_key(int key, void *param);
int		deal_click(int button, int x, int y, void *param);
int		plot_mandelbrot(double x0, double y0, int max_iteration);
int		plot_julia(double x0, double y0, int max_iteration);
int		plot_burningship(double x0, double y0, int max_iteration);

#endif