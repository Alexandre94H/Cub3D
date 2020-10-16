/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:44:56 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/16 11:01:06 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_key.h"
#include "../library.h"

void	update_keys(t_runtime *runtime)
{
	unsigned short	index;
	t_key_f			key;

	if (!runtime->player.updated)
		return ;
	index = 0;
	if (runtime->keys)
		while (runtime->keys[index])
		{
			(void)key;
			key = runtime->keys[index++];
			if (*key)
				(*key)(runtime);
			runtime->player.updated = false;
		}
}

int		press(int code, t_runtime *runtime)
{
	unsigned short	index;
	t_key			*key;

	index = 0;
	while ((key = &g_key_board[index++])->input)
	{
		if (key->input == code)
		{
			if (key->index != -1)
				return (1);
			key->index = array_add((void ***)&runtime->keys, key->function);
			break ;
		}
	}
	update_keys(runtime);
	return (0);
}

int		release(int code, t_runtime *runtime)
{
	unsigned short	index;
	t_key			*key;
	char			old_index;

	if (!runtime->keys)
		return (1);
	index = 0;
	while ((key = &g_key_board[index++])->input)
	{
		if (key->input == code)
		{
			if (key->index == -1)
				return (1);
			array_remove((void ***)&runtime->keys, key->index);
			old_index = key->index;
			key->index = -1;
			index = 0;
			while ((key = &g_key_board[index++])->input)
				if (key->index > old_index)
					key->index--;
			break ;
		}
	}
	return (0);
}
