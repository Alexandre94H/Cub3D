/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:49:25 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/03 09:23:35 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../main/cub3d.h"

t_settings	ft_flag_set(char *flag, char *line, t_settings *settings);
t_settings	ft_map_line(char *line, t_settings *settings);
char		*ft_stradhere(char **str, char c);

#endif
