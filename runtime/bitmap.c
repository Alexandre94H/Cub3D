/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 15:52:50 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/18 20:49:54 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "runtime.h"
#include "../main/cub3d.h"
#include "../get_next_line/get_next_line.h"

int		ft_create_bitmap(char *filename)
{
	int	fd;

	filename = ft_strdup(filename);
	ft_stradd(&filename, ".bmp");
	ft_putstr("Creating ");
	ft_putstr(filename);
	ft_putstr("...");
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	free(filename);
	return (fd);
}

void	ft_bitmap_header(t_mlx mlx, int fd, int null)
{
	int	header;
	int	plane;
	int	bpp;

	header = 40;
	plane = 1;
	bpp = 32;
	write(fd, &header, sizeof(int));
	write(fd, &mlx.settings.width, sizeof(int));
	write(fd, &mlx.settings.height, sizeof(int));
	write(fd, &plane, sizeof(short int));
	write(fd, &bpp, sizeof(short int));
	write(fd, &null, sizeof(int) * 6);
}

void	ft_bitmap_loop(t_mlx mlx, int fd)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < mlx.settings.width)
	{
		x = 0;
		while (x < mlx.settings.height)
		{
			write(fd, &mlx.data[x + y * mlx.settings.height], sizeof(int));
			x++;
		}
		y++;
	}
}

void	ft_bitmap(t_mlx mlx, char *filename)
{
	int	fd;
	int	null;
	int	first;
	int	total;

	fd = ft_create_bitmap(filename);
	null = 0;
	first = 14 + 40;
	total = first + 4 + mlx.settings.width * mlx.settings.height * 4;
	write(fd, "BM", sizeof(char) * 2);
	write(fd, &total, sizeof(int));
	write(fd, &null, sizeof(short int));
	write(fd, &null, sizeof(short int));
	write(fd, &first, sizeof(int));
	ft_bitmap_header(mlx, fd, null);
	ft_bitmap_loop(mlx, fd);
	close(fd);
	ft_putstr(" Done\n");
}
