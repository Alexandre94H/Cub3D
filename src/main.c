/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 20:05:46 by ahallain          #+#    #+#             */
/*   Updated: 2020/09/21 15:30:14 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "file/file.h"

int     main(int argc, char** argv)
{
	int		ret;
	t_file	file;

	ret = 0;
	if (argc == 1)
		ret = 1;
    if (!ret)
		ret = init_file(argv[1], &file) ? 2 : 0;
	return (error(ret));
}