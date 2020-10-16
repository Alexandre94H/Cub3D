/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 22:40:28 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 19:42:18 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "file_full.h"
#include "../library.h"

int	dispatch_flag(char *flag, char *line, t_file *file)
{
	if (flag[0] == 'R')
		file->resolution = resolution(line);
	else if (flag[0] == 'N' && flag[1] == 'O')
		file->north = texture(line);
	else if (flag[0] == 'S' && flag[1] == 'O')
		file->south = texture(line);
	else if (flag[0] == 'W' && flag[1] == 'E')
		file->west = texture(line);
	else if (flag[0] == 'E' && flag[1] == 'A')
		file->east = texture(line);
	else if (flag[0] == 'F')
		file->floor = texture(line);
	else if (flag[0] == 'C')
		file->ceil = texture(line);
	else if (flag[0] == 'S')
		add_sprite(file, line);
	else if (flag[0] == 'B' && flag[1] == 'O' && flag[2] == 'N'
		&& flag[3] == 'U' && flag[4] == 'S' && BONUS == 0)
		return (1);
	return (0);
}

int	divide_line(char *line, t_file *file)
{
	unsigned int	index;
	char			*flag;

	if (*line == '\0')
		return (0);
	index = 0;
	if (*line == '1' || *line == ' ')
		map_add(line, file);
	else
	{
		while (line[index++] != ' ')
			;
		if (!(flag = malloc(sizeof(char *) * index)))
			return (0);
		flag[--index] = 0;
		while (index--)
			flag[index] = line[index];
		while (*++line != ' ')
			;
		while (*++line == ' ')
			;
		index = dispatch_flag(flag, line, file);
		free(flag);
	}
	return (index);
}

int	scan_file(char *path, t_file *file)
{
	int		fd;
	char	*line;
	int		ret;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (0);
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		if (divide_line(line, file))
			return (1);
		free(line);
	}
	close(fd);
	return (0);
}
