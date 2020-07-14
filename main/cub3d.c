/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 04:24:42 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/28 20:44:10 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "cub3d.h"
#include "../parse/parse.h"
#include "../runtime/runtime.h"

char	*ft_tolowercase(char *str)
{
	size_t	index;

	index = 0;
	while (str[index])
	{
		if (str[index] >= 'A' && str[index] <= 'Z')
			str[index] += 'a' - 'A';
		index++;
	}
	return (str);
}

bool	ft_equal(char *str, char *str1)
{
	size_t	index;

	index = 0;
	while (str[index] && str[index] == str1[index])
		index++;
	if (str[index] == str1[index])
		return (true);
	return (false);
}

void	ft_error(char *str, int code)
{
	ft_putstr("Error (", 2);
	ft_putnbr(code, 2);
	ft_putstr("): ", 2);
	ft_putstr(str, 2);
	exit(code);
}

int		main(int argc, char **argv)
{
	t_settings	settings;

	if (argc < 2)
		ft_error("You must indicate the parameters file (.cub).", 1);
	settings = (t_settings) {0, 0, 0, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, 0, 0, 0};
	ft_load(argv[1], &settings);
	if (!settings.map)
		ft_error("Map not initialized.", 1);
	if (!ft_vermap(settings.map))
		ft_error("Invalid Map.", 2);
	if (argc > 2 && ft_equal(ft_tolowercase(argv[2]), "--save"))
	{
		settings.bitmap = argc > 3 ? argv[3] : "save";
		settings.save = true;
	}
	return (ft_run(argv[0] + 2, settings));
}
