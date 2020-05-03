/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 04:24:42 by ahallain          #+#    #+#             */
/*   Updated: 2020/05/04 01:03:06 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_settings	settings;

	if (argc < 2)
	{
		ft_putstr("You must indicate the parameters file (.cub).");
		return (1);
	}
	settings = (t_settings) {0, 0, {0, 0, 0, 0, 0}, {0, 0}, 0};
	ft_load(argv[1], &settings);
	if (!settings.map)
	{
		ft_putstr("Map not initialized.");
		return (2);
	}
	if (ft_vermap(settings.map))
	{
		ft_putstr("Invalid Map.");
		return (3);
	}
}
