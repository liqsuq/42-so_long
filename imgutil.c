/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imgutil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:08:41 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/23 20:35:59 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_image(t_app *app, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(app->mlx, path, &img->width, &img->height);
	if (img->img == NULL)
		exit_on_syserror(app, "Error\nload_image()\n");
}

static void	draw_image(t_app *app, t_img *img, int x, int y)
{
	mlx_put_image_to_window(app->mlx, app->win, img->img, x * SQ, y * SQ);
}

static void	draw_tile(t_app *app, int x, int y)
{
	if (app->map[app->width * y + x] == '1')
		draw_image(app, &app->wall, x, y);
	else if (app->map[app->width * y + x] == 'C')
		draw_image(app, &app->item, x, y);
	else if (app->map[app->width * y + x] == 'E')
		draw_image(app, &app->exit, x, y);
	else
		draw_image(app, &app->empty, x, y);
	if (app->pos_x == x && app->pos_y == y)
		draw_image(app, &app->player, x, y);
}

int	draw_all(t_app *app)
{
	int	i;
	int	j;

	i = -1;
	while (++i < app->height)
	{
		j = -1;
		while (++j < app->width)
			draw_tile(app, j, i);
	}
	return (0);
}
