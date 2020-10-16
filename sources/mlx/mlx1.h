/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:57:38 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 19:34:07 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX1_H
# define MLX1_H

# include <stdbool.h>
# include "../file/file.h"
# include "../player/player.h"

# define MAX_FPS 60

typedef struct	s_mlx
{
	void			*mlx;
	void			*window;
	void			*image;
	unsigned int	*data;
	float			*buffer;

}				t_mlx;

typedef struct s_runtime	t_runtime;
typedef	void				(*t_key_f)(t_runtime *);

struct			s_runtime
{
	t_file		file;
	t_player	player;
	t_mlx		mlx;
	t_key_f		*keys;
	bool		save;
	bool		end;
};

void			init_mlx(t_file *file, t_mlx *mlx, t_player *player);
void			loop(char *name, t_runtime runtime);
#endif
