/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 21:46:49 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/19 20:40:23 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file_full.h"

unsigned char	init_file(char *path, t_file *file)
{
	unsigned char	ret;

	*file = (t_file){{0, 0}, {0, 0, {0, 0}}, {0, 0, {0, 0}}, {0, 0, {0, 0}},
		{0, 0, {0, 0}}, 0, {0, 0, {0, 0}}, {0, 0, {0, 0}}, 0};
	if ((ret = scan_file(path, file)))
		return (ret);
	return (file->map ? !verification(file->map) : 2);
}
