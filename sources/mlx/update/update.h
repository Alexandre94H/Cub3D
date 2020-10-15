/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:30:40 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/15 17:56:00 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_H
# define UPDATE_H

int		texture_color(t_texture texture, t_resolution position);
void	update_floor(t_runtime *runtime, t_ray ray);
void	update_wall(t_runtime *runtime, t_ray ray);
void	update_sprite(t_runtime *runtime, t_ray ray);
#endif
