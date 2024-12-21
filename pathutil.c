/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathutil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:20:57 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/21 15:35:29 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	find_path(t_app *app, char *map, int x, int y)
{
	if (x < 0 || y < 0 || x >= app->width || y >= app->height)
		return (1);
	if (map[app->width * y + x] == '1')
		return (1);
	if (map[app->width * y + x] == 'P')
		return (0);
	map[app->width * y + x] = '1';
	if (find_path(app, map, x - 1, y) == 0)
		return (0);
	if (find_path(app, map, x + 1, y) == 0)
		return (0);
	if (find_path(app, map, x, y - 1) == 0)
		return (0);
	if (find_path(app, map, x, y + 1) == 0)
		return (0);
	return (1);
}

void	find_paths(t_app *app)
{
	int		i;
	int		j;
	int		retval;
	char	*map;

	i = -1;
	while (++i < app->height)
	{
		j = -1;
		while (++j < app->width)
		{
			if (app->map[app->width * i + j] == 'E'
				|| app->map[app->width * i + j] == 'C')
			{
				map = ft_strjoin("", app->map);
				if (map == NULL)
					exit_on_syserror(app, "[ERR] ft_strjoin() in find_paths()");
				retval = find_path(app, map, j, i);
				free(map);
				if (retval == 1)
					exit_on_error(app, "[ERR] map doesn't have valid path\n");
			}
		}
	}
}
