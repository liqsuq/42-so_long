/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maputil.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:25:08 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/21 15:29:35 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*load_line(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line != NULL && line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	return (line);
}

void	load_map(t_app *app, int fd)
{
	char	*line;

	line = load_line(fd);
	app->width = ft_strlen(line);
	app->height = 1;
	app->map = line;
	line = load_line(fd);
	while (line != NULL)
	{
		if (app->width != (int)ft_strlen(line))
		{
			free(line);
			ft_dprintf(STDERR_FILENO, "Error\nmap is not rectangle\n");
			exit(EXIT_FAILURE);
		}
		app->height++;
		app->map = ft_strjoin(app->map, line);
		free(line);
		if (app->map == NULL)
		{
			perror("Error\nft_strjoin()");
			exit(EXIT_FAILURE);
		}
		line = load_line(fd);
	}
}

static int	is_none_or_duplicate(char *map, char c)
{
	char	*ptr1;
	char	*ptr2;

	if (map == NULL)
		return (0);
	ptr1 = ft_strchr(map, c);
	ptr2 = ft_strrchr(map, c);
	if (ptr1 == NULL || ptr2 == NULL || ptr1 != ptr2)
		return (1);
	return (0);
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
	if (is_none_or_duplicate(app->map, 'P'))
		exit_on_error(app, "Error\nplayer is not found or duplicate\n");
	if (is_none_or_duplicate(app->map, 'E'))
		exit_on_error(app, "Error\nexit is not found or duplicate\n");
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
