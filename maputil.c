/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maputil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:25:08 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/23 14:19:38 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*load_line(t_app *app, int fd)
{
	static int	is_first = 1;
	char		*line;

	line = get_next_line(fd);
	if (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (is_first)
		{
			is_first = 0;
			app->width = ft_strlen(line);
			app->height = 0;
		}
		else if (app->width != (int)ft_strlen(line))
		{
			free(line);
			free(app->map);
			ft_dprintf(STDERR_FILENO, "Error\nmap is not rectangle\n");
			exit(EXIT_FAILURE);
		}
		app->height++;
	}
	return (line);
}

void	load_map(t_app *app, int fd)
{
	char	*line;
	char	*tmp;

	app->map = ft_strdup("");
	if (app->map == NULL)
	{
		perror("Error\nft_strdup()");
		exit(EXIT_FAILURE);
	}
	line = load_line(app, fd);
	while (line != NULL)
	{
		tmp = ft_strjoin(app->map, line);
		free(app->map);
		free(line);
		if (tmp == NULL)
		{
			perror("Error\nft_strjoin()");
			exit(EXIT_FAILURE);
		}
		app->map = tmp;
		line = load_line(app, fd);
	}
}

void	check_map(t_app *app)
{
	int	i;
	int	j;

	i = -1;
	while (++i < app->height)
	{
		j = -1;
		while (++j < app->width)
		{
			if (ft_strchr("01CEP", app->map[app->width * i + j]) == NULL)
				exit_on_error(app, "Error\ninvalid map character\n");
			if (i == 0 || i == app->height - 1 || j == 0 || j == app->width - 1)
				if (app->map[app->width * i + j] != '1')
					exit_on_error(app, "Error\nmap isn't be closed\n");
		}
	}
	if (ft_strchr(app->map, 'P') == NULL || ft_strchr(app->map, 'E') == NULL)
		exit_on_error(app, "Error\nplayer or/and exit are not found\n");
	if (ft_strchr(app->map, 'P') != ft_strrchr(app->map, 'P')
		|| ft_strchr(app->map, 'E') != ft_strrchr(app->map, 'E'))
		exit_on_error(app, "Error\nplayer of/and exit are duplicate\n");
}

void	parse_map(t_app *app)
{
	int	i;
	int	j;

	i = -1;
	while (++i < app->height)
	{
		j = -1;
		while (++j < app->width)
		{
			if (app->map[app->width * i + j] == 'P')
			{
				app->pos_x = j;
				app->pos_y = i;
				app->map[app->width * i + j] = '0';
			}
			if (app->map[app->width * i + j] == 'C')
				app->num_item++;
		}
	}
	if (app->num_item <= 0)
		exit_on_error(app, "Error\nitem is not found\n");
}
