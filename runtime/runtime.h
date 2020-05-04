/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 22:17:23 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/04 18:27:55 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include "../main/cub3d.h"
# include <mlx.h>

typedef struct	s_player
{
	float	degree;
	float	x;
	float	y;
	bool	initiate;
}				t_player;

typedef struct	s_mlx
{
	t_settings	settings;
	t_player	player;
	void		*mlx;
	void		*win;
	void		*img;
}				t_mlx;

void			ft_detect(t_mlx mlx);
void			ft_update(t_mlx mlx);

#endif
