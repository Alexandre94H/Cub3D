/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 23:34:38 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/08 18:39:29 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "library.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		ft_putchar_fd(*str++, fd);
}

void	ft_putnbr_fd(int nbr, int fd)
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

int		ft_atoi(char *str)
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

void	*ft_strdup(char *str)
{
	char	*ret;
	size_t	index;

	index = ft_strlen(str, 0);
	if (!(ret = malloc(sizeof(char *) * (index + 1))))
		return (0);
	ret[index] = 0;
	while (index--)
		ret[index] = str[index];
	return (ret);
}

short	array_add(void ***list, void *item)
{
	unsigned short	length;
	void			**new;
	unsigned short	index;

	length = 0;
	if (*list)
		while ((*list)[length])
			length++;
	if (!(new = malloc(sizeof(*list) * (length + 2))))
		return (-1);
	new[length + 1] = 0;
	new[length] = item;
	index = length;
	while (length--)
		new[length] = (*list)[length];
	if (*list)
		free(*list);
	*list = new;
	return (index);
}

void	array_remove(void ***list, unsigned short index)
{
	unsigned short	length;
	void			**new;

	length = 0;
	if (*list)
	{
		while ((*list)[++length])
			;
		length--;
	}
	if (!(new = malloc(sizeof(*list) * (length + 1))))
		return ;
	new[length] = 0;
	while (length--)
		new[length] = (*list)[length < index ? length : length + 1];
	if (*list)
		free(*list);
	*list = new;
}

static size_t	ft_count(int n)
{
	size_t count;

	count = 0;
	if (n < 0)
	{
		count++;
		if (n == -2147483648)
		{
			count++;
			n = 147483648;
		}
		else
			n *= -1;
	}
	while (n > 9)
	{
		count++;
		n /= 10;
	}
	return (count + 1);
}

static char		*ft_setnbr(int n, char *nbr)
{
	size_t	index;

	index = 0;
	if (n < 0)
	{
		nbr[index++] = '-';
		if (n == -2147483648)
		{
			nbr[index++] = '2';
			n = 147483648;
		}
		else
			n *= -1;
	}
	nbr[ft_count(n) + index] = 0;
	while (n > 9)
	{
		nbr[ft_count(n) - 1 + index] = n % 10 + '0';
		n /= 10;
	}
	nbr[index] = n % 10 + '0';
	return (nbr);
}

char			*ft_itoa(int n)
{
	char *nbr;

	if (!(nbr = malloc(ft_count(n) + 1)))
		return (NULL);
	return (ft_setnbr(n, nbr));
}