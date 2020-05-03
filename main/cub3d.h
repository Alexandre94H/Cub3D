/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 04:30:49 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/03 09:04:08 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stddef.h>

typedef	struct	s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
}				t_texture;

typedef	struct	s_color
{
	char	*f;
	char	*c;
}				t_color;

typedef	struct	s_settings
{
	unsigned int	width;
	unsigned int	height;
	t_texture		texture;
	t_color			color;
	char			**map;
}				t_settings;

void			ft_putchar(char c);
void			ft_putstr(char *str);
int				ft_atoi(char *str);
void			ft_putnbr(int nbr);
t_settings		ft_load(char *filename, t_settings *settings);

#endif
