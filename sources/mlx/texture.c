/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 06:19:55 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 19:38:39 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "../file/file.h"
#include "../library.h"

t_texture	color(char *line)
{
	int			color;
	t_texture	texture;

	color = ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line < '0' || *line > '9')
		line++;
	color *= 16 * 16;
	color += ft_atoi(line);
	while (*line >= '0' && *line <= '9')
		line++;
	while (*line < '0' || *line > '9')
		line++;
	color *= 16 * 16;
	color += ft_atoi(line);
	texture = (t_texture){0, 0, {1, 1}};
	if (!(texture.data = malloc(sizeof(unsigned int))))
		return (texture);
	*texture.data = color;
	return (texture);
}

int			*image_data(void *image, unsigned short width)
{
	unsigned int	bits_per_pixel;
	unsigned char	endian;

	bits_per_pixel = 32;
	endian = 0;
	width *= 4;
	return ((int *)mlx_get_data_addr(image, (int *)&bits_per_pixel,
		(int *)&width, (int *)&endian));
}

void		init_texture(void *mlx, t_texture *texture)
{
	char		*path;

	path = (char *)texture->data;
	if (ft_strcchr(path, ','))
		*texture = color(path);
	else
	{
		texture->image = mlx_xpm_file_to_image(mlx, path,
			(int *)&texture->resolution.width,
			(int *)&texture->resolution.height);
		texture->data = image_data(texture->image, texture->resolution.width);
	}
	free(path);
}
