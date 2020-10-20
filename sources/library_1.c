/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:38:28 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/20 13:57:40 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "library.h"

void	ft_putchar_fd(const char c, const int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(const char *str, const int fd)
{
	while (*str)
		ft_putchar_fd(*str++, fd);
}

void	ft_putnbr_fd(int nbr, const int fd)
{
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		if (nbr == -2147483648)
		{
			ft_putchar_fd('2', fd);
			nbr = -147483648;
		}
		nbr *= -1;
	}
	if (nbr >= 10)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar_fd(nbr % 10 + '0', fd);
}

int		ft_atoi(const char *str)
{
	char	multiply;
	int		nbr;

	multiply = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			multiply = -1;
		str++;
	}
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr *= 10;
		nbr += *str++ - '0';
	}
	return (nbr * multiply);
}

void	*ft_strdup(const char *str, const size_t length)
{
	char	*ret;
	size_t	index;

	if (length)
		index = length;
	else
		index = ft_strlen(str, 0);
	if (!(ret = malloc(sizeof(char *) * (index + 1))))
		return (0);
	ret[index] = 0;
	while (index--)
		ret[index] = str[index];
	return (ret);
}
