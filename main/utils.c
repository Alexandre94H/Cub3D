/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 04:35:48 by ahallain          #+#    #+#             */
/*   Updated: 2020/06/28 20:42:06 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>

void	ft_putchar(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr(char *str, int fd)
{
	while (*str)
		ft_putchar(*str++, fd);
}

void	ft_putnbr(int nbr, int fd)
{
	if (nbr < 0)
	{
		ft_putchar('-', fd);
		if (nbr == -2147483648)
		{
			ft_putchar('2', fd);
			nbr = -147483648;
		}
		nbr *= -1;
	}
	if (nbr >= 10)
		ft_putnbr(nbr / 10, fd);
	ft_putchar(nbr % 10 + '0', fd);
}

int		ft_atoi(char *str)
{
	int		multiply;
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
