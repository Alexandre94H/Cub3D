/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 00:32:53 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/07 23:59:08 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include "mlx1.h"

void	bitmap(char *filename, t_runtime *runtime)
{
	int				fd;
	int				null;
	int				first;
	int				total;
	int				header;
	int				plane;
	int				bpp;
	unsigned short	x;
	unsigned short	y;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	first = 14 + 40;
	total = first + 4 + runtime->file.resolution.width * runtime->file.resolution.height * 4;
	write(fd, "BM", sizeof(char) * 2);
	write(fd, &total, sizeof(int));
	null = 0;
	write(fd, &null, sizeof(short int));
	write(fd, &null, sizeof(short int));
	write(fd, &first, sizeof(int));
	header = 40;
	write(fd, &header, sizeof(int));
	plane = runtime->file.resolution.width;
	bpp = runtime->file.resolution.height;
	write(fd, &plane, sizeof(int));
	write(fd, &bpp, sizeof(int));
	plane = 1;
	write(fd, &plane, sizeof(short int));
	bpp = 32;
	write(fd, &bpp, sizeof(short int));
	write(fd, &null, sizeof(int) * 6);
	y = runtime->file.resolution.height;
	while (y-- > 0)
	{
		x = 0;
		while (x < runtime->file.resolution.width)
		{
			null = runtime->mlx.data[y * runtime->file.resolution.width + x];
			write(fd, &null, sizeof(int));
			x++;
		}
	}
	close(fd);
}