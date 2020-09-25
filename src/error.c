/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 21:11:38 by ahallain          #+#    #+#             */
/*   Updated: 2020/09/25 11:12:37 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int		error(int error)
{
	if (!error)
		return (0);
	ft_putstr_fd("Error: ", 2);
	if (error == 1)
		ft_putstr_fd("Please add the file path after the command.", 2);
	else if (error == 2)
		ft_putstr_fd("An error occurred while scanning files, please check the contents.", 2);
	else if (error == 3)
		ft_putstr_fd("Unable to find player position on map.", 2);
	return(error);
}