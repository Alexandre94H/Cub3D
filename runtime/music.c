/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 01:59:00 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/20 02:20:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "runtime.h"
#include "../get_next_line/get_next_line.h"

void		ft_music_clear()
{
	system("killall -q aplay");
}

void		ft_music(char *path)
{
	char	*cmd;

	cmd = ft_strdup("aplay ");
	ft_stradd(&cmd, path);
	ft_stradd(&cmd, " &");
	system(cmd);
	free(cmd);
}