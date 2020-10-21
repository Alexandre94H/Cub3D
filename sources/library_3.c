/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:27:05 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/21 17:09:53 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>

bool		ft_equals(const char *str, const char *str1)
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

char		*ft_tolower(char *str)
{
	size_t index;

	index = 0;
	if (str)
		while (str[index])
		{
			if (str[index] >= 'A' && str[index] <= 'Z')
				str[index] += 'a' - 'A';
			index++;
		}
	return (str);
}

int			ft_strstr(const char *str, const char *chunk)
{
	size_t	ret;
	size_t	index;

	ret = 0;
	while (str[ret])
	{
		index = 0;
		while (str[ret + index] == chunk[index])
		{
			index++;
			if (!chunk[index])
				return (ret);
		}
		ret++;
	}
	return (-1);
}


long long	ft_abs(long long number)
{
	if (number < 0)
		return (-1 * number);
	return (number);
}