/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 20:05:46 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 20:26:20 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "runtime.h"
#include "library.h"

int	main(int argc, char **argv)
{
	unsigned char	ret;
	t_file			file;
	t_player		player;
	t_mlx			mlx;
	t_runtime		runtime;

	ret = 0;
	if (argc == 1)
		ret = 1;
	if (!ret)
		ret = init_file(argv[1], &file);
	player = (t_player) {0, {0, 0, 0}, 0, 0, 0};
	if (!ret)
		ret = init_player(file.map, &player);
	if (!ret)
		ret = init_mlx(&file, &mlx, &player);
	if (!ret)
	{
		runtime = (t_runtime) {file, player, mlx, 0, 0, 0};
		loop(*argv + 2, &runtime, ft_equals(ft_tolower(argv[2]), "--save"));
	}
	return (error(&runtime, ret));
}
