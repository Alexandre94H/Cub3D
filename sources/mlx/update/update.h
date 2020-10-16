/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 07:30:40 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 19:10:31 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_H
# define UPDATE_H

void	update_floor(t_runtime *runtime, t_ray ray);
void	update_wall(t_runtime *runtime, t_ray ray);
void	update_sprite(t_runtime *runtime, t_ray ray);
#endif
