/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:03:51 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/23 13:41:24 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	close_window(t_app *app)
{
	ft_printf(INFO"close window\n");
	exit_app(app);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	is_move_key(int keycode)
{
	return (keycode == XK_Up || keycode == XK_Down
		|| keycode == XK_Left || keycode == XK_Right
		|| keycode == XK_w || keycode == XK_W
		|| keycode == XK_s || keycode == XK_S
		|| keycode == XK_a || keycode == XK_A
		|| keycode == XK_d || keycode == XK_D);
}

void	control(t_app *app, int x, int y)
{
	if (app->map[app->width * y + x] == '1')
		return ;
	app->pos_x = x;
	app->pos_y = y;
	ft_printf(INFO"num_move: %d\n", ++app->num_move);
	if (app->map[app->width * y + x] == 'C')
	{
		app->num_item--;
		app->map[app->width * y + x] = '0';
		if (app->num_item <= 0)
			ft_printf(INFO"yummy fish! now go to the exit!\n");
		else
			ft_printf(INFO"yummy fish! more %d to eat!\n", app->num_item);
	}
	if (app->map[app->width * y + x] == 'E')
	{
		if (app->num_item == 0)
		{
			ft_printf(INFO"So Long, and Thanks for All the Fish...\n");
			exit_app(app);
			exit(EXIT_SUCCESS);
		}
		ft_printf(INFO"fishes are not extinct yet! eat 'em all!\n");
	}
	draw_all(app);
}

static int	key_hook(int keycode, t_app *app)
{
	int	future_x;
	int	future_y;

	future_x = app->pos_x;
	future_y = app->pos_y;
	if (keycode == XK_Escape)
		close_window(app);
	else if (is_move_key(keycode))
	{
		if (keycode == XK_Up || keycode == XK_w || keycode == XK_W)
			future_y--;
		else if (keycode == XK_Down || keycode == XK_s || keycode == XK_S)
			future_y++;
		else if (keycode == XK_Left || keycode == XK_a || keycode == XK_A)
			future_x--;
		else
			future_x++;
		control(app, future_x, future_y);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_app	app;

	if (argc != 2)
	{
		ft_printf("Error\nUsage: ./so_long map.ber\n");
		exit (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nopen()");
		exit (EXIT_FAILURE);
	}
	load_map(&app, fd);
	close(fd);
	init_app(&app);
	check_map(&app);
	find_paths(&app);
	parse_map(&app);
	mlx_key_hook(app.win, key_hook, &app);
	mlx_expose_hook(app.win, draw_all, &app);
	mlx_hook(app.win, DestroyNotify, 0, close_window, &app);
	mlx_loop(app.mlx);
	return (0);
}
