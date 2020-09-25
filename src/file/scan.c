/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 22:40:28 by ahallain          #+#    #+#             */
/*   Updated: 2020/09/23 23:45:09 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "file_full.h"

void		dispatch_flag(char *flag, char *line, t_file *file)
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
	else if (flag[0] == 'S')
		file->sprite = texture(line);
	else if (flag[0] == 'F')
		file->floor = texture(line);
	else if (flag[0] == 'C')
		file->ceil = texture(line);
}

void		divide_line(char *line, t_file *file)
{
	unsigned int	index;
	char			*flag;

	if (*line == '\0')
		return ;
	if (*line == '1' || *line == ' ')
		map_add(line, file);
	else
	{
		index = 0;
		while (line[index++] != ' ')
			;
		if (!(flag = malloc(sizeof(char *) * index)))
			return ;
		flag[--index] = 0;
		while (index--)
			flag[index] = line[index];
		while (*++line != ' ')
			;
		while (*++line == ' ')
			;
		dispatch_flag(flag, line, file);
		free(flag);
	}
}

void		scan_file(char *path, t_file *file)
{
	int		fd;
	char	*line;
	int		ret;

	if ((fd = open(path, O_RDONLY)) == -1)
		return ;
	ret = 1;
	while (ret)
	{
		ret = get_next_line(fd, &line);
		divide_line(line, file);
		free(line);
	}
	close(fd);
}
