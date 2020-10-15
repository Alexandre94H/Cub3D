/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_full.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:05:26 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 22:54:15 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_FULL_H
# define MLX_FULL_H

# include "mlx1.h"

# define TEXTURE_SIDE 64
# define FOV 70

typedef struct	s_ray {
	t_position	direction;
	t_position	plan;
	float		*buffer;
}				t_ray;

int				update(t_runtime *runtime);
unsigned int	*image_data(void *image, unsigned short width);
int				press(int key, t_runtime *runtime);
int				release(int key, t_runtime *runtime);
void			update_keys(t_runtime *runtime);
void			bitmap(char *filename, t_runtime *runtime);
void			end(t_runtime *runtime);
void			init_texture(void *mlx, t_texture *texture,
	unsigned short width, unsigned short height);
int				release(int code, t_runtime *runtime);
#endif
