/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 06:19:55 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 16:21:26 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "../file/file.h"
#include "../library.h"

unsigned char	color(char *line, int *color)
{
	unsigned char	length;
	int				atoi;

	length = 0;
	*color = 0;
	while (length < 3)
	{
		if (length && *line++ != ',')
			return (2);
		while (*line == ' ')
			line++;
		if (!*line || *line < '0' || *line > '9')
			return (2);
		*color *= 256;
		atoi = ft_atoi(line);
		if (atoi < 0 || atoi > 255)
			return (2);
		*color += atoi;
		while (*line >= '0' && *line <= '9')
			line++;
		length++;
	}
}

unsigned char	color_texture(char *line, t_texture *texture)
{
	unsigned char	ret;
	int				color1;

	ret = color(*line, &color1);
	*texture = (t_texture){0, 0, {1, 1}};
	if (!(texture->data = malloc(sizeof(int *))))
		return (2);
	*texture->data = color1;
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
	int			fd;
	int			ret;

	path = (char *)texture->data;
	ret = 0;
	if (ft_strcchr(path, ','))
		ret = color_texture(path, texture);
	else if (ft_strstr(path, ".xpm")
		!= (int)(ft_strlen(path, 0) - ft_strlen(".xpm", 0))
		|| (fd = open(path, O_RDONLY) == -1))
		ret = 2;
	else
	{
		close(fd);
		texture->image = mlx_xpm_file_to_image(mlx, path,
			(int *)&texture->resolution.width,
			(int *)&texture->resolution.height);
		texture->data = image_data(texture->image, texture->resolution.width);
	}
	free(path);
	return (ret);
}
