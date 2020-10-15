/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 23:36:53 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 20:12:17 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

typedef struct	s_resolution
{
	unsigned short	width;
	unsigned short	height;
}				t_resolution;

typedef struct	s_texture
{
	void			*image;
	unsigned int	*data;
	t_resolution	resolution;
}				t_texture;

typedef struct	s_file
{
	t_resolution	resolution;
	t_texture		north;
	t_texture		south;
	t_texture		east;
	t_texture		west;
	t_texture		**sprites;
	t_texture		floor;
	t_texture		ceil;
	char			**map;
}				t_file;

int				init_file(char *path, t_file *file);
#endif
