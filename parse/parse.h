/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:49:25 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/19 05:22:56 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdbool.h>

typedef	struct	s_xpm
{
	bool	initiate;
	void	*img;
	int		*data;
}				t_xpm;

typedef	struct	s_texture
{
	t_xpm	no;
	t_xpm	so;
	t_xpm	we;
	t_xpm	ea;
	t_xpm	s;
	t_xpm	f;
	t_xpm	c;
}				t_texture;

typedef	struct	s_settings
{
	unsigned int	width;
	unsigned int	height;
	char			**map;
	t_texture		textures;
	char			*music;
	char			*bitmap;
	bool			save;
}				t_settings;

t_settings		ft_flag_set(char *flag, char *line, t_settings *settings);
t_settings		ft_map_line(char *line, t_settings *settings);
char			*ft_stradhere(char **str, char c);
t_settings		ft_load(char *path, t_settings *settings);
bool			ft_vermap(char **map);
void			*ft_strdup(char *str);
int				ft_line_color(char *line);

#endif
