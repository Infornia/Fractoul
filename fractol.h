/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwilk <mwilk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/11 15:42:54 by mwilk             #+#    #+#             */
/*   Updated: 2015/11/27 21:27:42 by mwilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <mlx.h>
# include <fcntl.h>
# include <math.h>
# include "Libft/includes/libft.h"

/*
**Parameters
*/

# define X_WIN 800
# define Y_WIN 600
# define Y_HALF Y_WIN / 2
# define X_HALF X_WIN / 2
# define NB_FRACTAL 8
# define NB_PAL 7
# define NB_TREE_COLORS 7

/*
** Textures
*/
# define T_PAL			"textures/pal.xpm"
# define T_PAL1			"textures/pal1.xpm"
# define T_PAL2			"textures/pal2.xpm"
# define T_PAL3			"textures/pal3.xpm"
# define T_PAL4			"textures/pal4.xpm"
# define T_PAL5			"textures/pal5.xpm"
# define T_PAL6			"textures/pal6.xpm"
/*

**Colors
*/
# define RED		0xFF0000
# define GREEN		0x00FF00
# define BLUE 		0x0000FF
# define QUOISE		0x74BDF9
# define GREEN 		0x00FF00
# define PINK 		0xFF00FF
# define WHITE 		0xFFFFFF
# define GRAY 		0x0F0F0F
# define BLACK 		0x000000
# define RGB(r, g, b)(256 * 256 * (int)(r) + 256 * (int)(g) + (int)(b))
# define ABS(x)		((x) < 0 ? -(x) : (x))

/*
**keys
*/

# define ESC		53
# define UP			126
# define DOWN		125
# define LEFT		123
# define RIGHT		124
# define TAB		48
# define SHIFT		257
# define ZOOM_IN	24
# define ZOOM_OUT	27
# define IT_UP	30
# define IT_DOWN	33
# define RESET		29
# define KEY1		18
# define KEY2		19
# define NUM1		83
# define NUM2		84
# define NUM3		85
# define NUM4		86
# define NUM5		87
# define NUM6		88
# define KEYR		15
# define ZOOM_IN_M	5
# define ZOOM_OUT_M	4

/*
**Structures
*/

typedef struct s_data	t_data;
typedef int				 (*t_fractal)(t_data *d, int x, int y, int mi);

typedef struct	s_key
{
	int			key_code;
	void		(*event)(t_data *d);
}				t_key;

typedef struct	s_coor
{
	int	x;
	int	y;
}				t_coor;

typedef struct	s_triangle
{
	int	x;
	int	y;
	int	h;
	int	d;
	int	max_i;
}				t_triangle;

typedef struct	s_util
{
	float		old_RZ;
	float		old_IZ;
	float		RC;
	float		IC;
	float		RZ;
	float		IZ;
	float		zxx;
	float		zyy;
	float		d;
	int			i;
}				t_util;

typedef struct	s_img
{
	void		*img;
	char		*data_img;	
	int			bpp;
	int			size;
	int			endian;
	int			max_size;
	int			w;
	int			h;
}				t_img;

struct			s_data
{
	void			*mlx;
	void			*win;
	t_img			screen;
	t_img			pals[NB_PAL];
	t_fractal		fractal[NB_FRACTAL];
	t_util			u;
	int				it;

	int				rainbow;
	int				r;
	int				g;
	int				b;

	int				current_pal;
	int				current_frac;
	int				tree_color_opt;

	int				click_x;
	int				click_y;
	int				move_x;
	int				move_y;
	float			mouse_x;
	float			mouse_y;
	float			c0x;
	float			c0y;
	float			zoom;
	float			zoom_w;
	float			zoom_h;
	float			os_x;
	float			os_y;
	float			os_zoom_x;
	float			os_zoom_y;
	float			julia_cx;
	float			julia_cy;
};


/*
**Prototypes
*/

/*
*******************INIT
*/

void			print_usage(int ac);
t_data			*frac_data(void);
void			fractal_del(t_data *d);
t_data			*main_frac(int n);
void			init_mlx(t_data *d, int n);
void			init_screen(t_img *d, void * mlx);
void			init_frac(t_data *d);
void			init_variables(t_data *d);
void			init_images(t_data *d);
void			init_julia(t_data *d, int x, int y);
void			init_mandelbrot(t_data *d, int x, int y);

/*
*******************HOOKS
*/

int				expose_hook(t_data *d);
int				mouse_hook(int button, int x, int y, t_data *d);
int				mouse_hook_move(int x, int y, t_data *d);
int				key_hook(int keycode, t_data *d);
void			hook_key_moves(t_data *d, int keycode);
void			hook_key_fractal(t_data *d, int keycode);
void			hook_key_colors(t_data *d, int keycode);

/*
*******************DRAW
*/

void			draw(t_data *d);
void			draw_tree(t_data *d);
void			draw_triangle(t_data *d);
void			display_for_tree(t_data *d, int opt);
void			color_pixel(t_img *d, unsigned int color, int x, int y);
unsigned int	get_img_color(t_data *d, float it, int max_i);
int				get_r_color(float t);
unsigned int	create_color(int r, int g, int b);

/*
*******************MOVE
*/

void			update_zoom(t_data *d);

/*
*******************FRAC
*/

int				mandelbrot(t_data *d, int x, int y, int max_i);
int				mandelbrot_special(t_data *d, int x, int y, int max_i);
int				burnship(t_data *d, int x, int y, int max_i);
int				newton(t_data *d, int x, int y, int max_i);
int				julia(t_data *d, int x, int y, int max_i);
int				julia_special(t_data *d, int x, int y, int max_i);
void			fractree(t_data *d, t_coor c, double a, int max_i);
void			fractriangle(t_data *d, t_coor c, float h, int max_i);

#endif
