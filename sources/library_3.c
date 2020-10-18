/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:27:05 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/17 19:43:28 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

bool	ft_equals(char *str, char *str1)
{
	if (str && str1)
		while (*str == *str1)
		{
			if (!*str)
				return (true);
			str++;
			str1++;
		}
	return (false);
}