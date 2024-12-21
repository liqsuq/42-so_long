/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:03:15 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/21 16:46:24 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>
# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "libft.h"

# define SQ 32
# define PATH_EMPTY "textures/umi.xpm"
# define PATH_WALL "textures/same.xpm"
# define PATH_ITEM "textures/sakana.xpm"
# define PATH_EXIT1 "textures/rocket1.xpm"
# define PATH_EXIT2 "textures/rocket2.xpm"
# define PATH_PLAYER "textures/iruka.xpm"
# define INFO "[INFO] "

# define RESET_FLAG 0b0000
# define EXIST_PLAYER 0b0001
# define EXIST_EXIT 0b0010

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}			t_img;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	char	*map;
	int		width;
	int		height;
	int		pos_x;
	int		pos_y;
	int		num_item;
	int		num_move;
	t_img	empty;
	t_img	wall;
	t_img	item;
	t_img	exit;
	t_img	player;
}			t_app;

void	init_app(t_app *app);
void	exit_app(t_app *app);
void	exit_on_syserror(t_app *app, char *message);
void	exit_on_error(t_app *app, char *message, ...);
void	load_image(t_app *app, t_img *img, char *path);
int		draw_all(t_app *app);
void	load_map(t_app *app, int fd);
void	check_map(t_app *app);
void	parse_map(t_app *app);
void	find_paths(t_app *app);

#endif
