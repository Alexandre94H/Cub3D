/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 06:19:55 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/19 23:43:01 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mlx.h>
#include "../file/file.h"
#include "../library.h"

unsigned char	color(char *line, t_texture *texture)
{
	unsigned char	length;
	int				color;

	length = 0;
	color = 0;
	while (length < 3)
	{
		while (*line && (*line < '0' || *line > '9'))
			line++;
		if (!*line)
			return (2);
		color *= 256;
		color += ft_atoi(line);
		while (*line >= '0' && *line <= '9')
			line++;
		length++;
	}
	*texture = (t_texture){0, 0, {1, 1}};
	if (!(texture->data = malloc(sizeof(unsigned int))))
		return (2);
	*texture->data = color;
	return (0);
}

int				*image_data(void *image, unsigned short width)
{
	unsigned int	bits_per_pixel;
	unsigned char	endian;

	bits_per_pixel = 32;
	endian = 0;
	width *= 4;
	return ((int *)mlx_get_data_addr(image, (int *)&bits_per_pixel,
		(int *)&width, (int *)&endian));
}

unsigned char	init_texture(void *mlx, t_texture *texture)
{
	char		*path;

	path = (char *)texture->data;
	if (ft_strcchr(path, ','))
		return (color(path, texture));
	if (access(path, F_OK) == -1)
		return (2);
	texture->image = mlx_xpm_file_to_image(mlx, path,
		(int *)&texture->resolution.width,
		(int *)&texture->resolution.height);
	texture->data = image_data(texture->image, texture->resolution.width);
	free(path);
	return (0);
}
