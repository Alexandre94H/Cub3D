/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 21:11:38 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 22:19:31 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

unsigned char	error(unsigned char error)
{
	if (!error)
		return (error);
	ft_putstr_fd("Error\n", 2);
	if (error == 1)
		ft_putstr_fd("Please add the file path after the command.", 2);
	else if (error == 2)
		ft_putstr_fd("An error occurred while scanning files.", 2);
	else if (error == 3)
		ft_putstr_fd("You must compile with the bonuses.", 2);
	else if (error == 4)
		ft_putstr_fd("Unable to find player position on map.", 2);
	return (error);
}
