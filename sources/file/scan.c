/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 22:40:28 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/20 20:41:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "file_full.h"
#include "../library.h"

unsigned char	dispatch_flag(char *flag, char *line, t_file *file)
{
	if (file->map)
		return (2);
	if (flag[0] == 'R' && !file->resolution.width)
		file->resolution = resolution(line);
	else if (flag[0] == 'N' && flag[1] == 'O' && !file->north.data)
		file->north = texture(line);
	else if (flag[0] == 'S' && flag[1] == 'O' && !file->south.data)
		file->south = texture(line);
	else if (flag[0] == 'E' && flag[1] == 'A' && !file->east.data)
		file->east = texture(line);
	else if (flag[0] == 'W' && flag[1] == 'E' && !file->west.data)
		file->west = texture(line);
	else if (flag[0] == 'C' && !file->ceil.data)
		file->ceil = texture(line);
	else if (flag[0] == 'F' && !file->floor.data)
		file->floor = texture(line);
	else if (flag[0] == 'S')
		add_sprite(file, line);
	else if (flag[0] == 'B' && !BONUS)
		return (3);
	else if (!BONUS && flag[0])
		return (2);
	return (0);
}

unsigned char	divide_line(char *line, t_file *file)
{
	unsigned int	index;
	char			*flag;

	if (*line == '\0')
		return (0);
	else if ((*line == '1' || *line == ' ') && is_init(*file))
		return (map_add(line, file));
	index = 0;
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
	return (index);
}

unsigned char	scan_file(char *path, t_file *file)
{
	int				fd;
	char			*line;
	int				ret;
	unsigned char	error;

	if (ft_strstr(path, ".cub")
		!= (int)(ft_strlen(path, 0) - ft_strlen(".cub", 0))
		|| (fd = open(path, O_RDONLY)) == -1)
		return (2);
	error = 0;
	ret = 1;
	while (!error && ret)
	{
		ret = get_next_line(fd, &line);
		error = divide_line(line, file);
		free(line);
	}
	close(fd);
	return (error);
}
