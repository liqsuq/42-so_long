/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apputil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:48:20 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/28 16:00:11 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_app(t_app *app)
{
	app->mlx = mlx_init();
	if (app->mlx == NULL)
		exit_on_initerror("Error\nmlx_init() failed\n");
	app->win = mlx_new_window(app->mlx, app->width * SQ, app->height * SQ, APP);
	if (app->win == NULL)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
		exit_on_initerror("Error\nmlx_new_window() failed\n");
	}
	app->pos_x = 0;
	app->pos_y = 0;
	app->num_item = 0;
	app->num_move = 0;
	app->empty.img = NULL;
	app->wall.img = NULL;
	app->item.img = NULL;
	app->exit.img = NULL;
	app->player.img = NULL;
	load_image(app, &app->empty, PATH_EMPTY);
	load_image(app, &app->wall, PATH_WALL);
	load_image(app, &app->item, PATH_ITEM);
	load_image(app, &app->exit, PATH_EXIT);
	load_image(app, &app->player, PATH_PLAYER);
}

void	exit_app(t_app *app)
{
	free(app->map);
	if (app->empty.img != NULL)
		mlx_destroy_image(app->mlx, app->empty.img);
	if (app->wall.img != NULL)
		mlx_destroy_image(app->mlx, app->wall.img);
	if (app->item.img != NULL)
		mlx_destroy_image(app->mlx, app->item.img);
	if (app->exit.img != NULL)
		mlx_destroy_image(app->mlx, app->exit.img);
	if (app->player.img != NULL)
		mlx_destroy_image(app->mlx, app->player.img);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
}

void	exit_on_syserror(t_app *app, char *message)
{
	perror(message);
	exit_app(app);
	exit(EXIT_FAILURE);
}

void	exit_on_error(t_app *app, char *message, ...)
{
	va_list	args;

	va_start(args, message);
	ft_vdprintf(STDERR_FILENO, message, args);
	va_end(args);
	exit_app(app);
	exit(EXIT_FAILURE);
}

void	exit_on_initerror(char *message, ...)
{
	va_list	args;

	va_start(args, message);
	ft_vdprintf(STDERR_FILENO, message, args);
	va_end(args);
	exit(EXIT_FAILURE);
}
