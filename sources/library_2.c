/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahallain <ahallain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:39:02 by ahallain          #+#    #+#             */
/*   Updated: 2020/10/20 13:58:22 by ahallain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

short			ft_array_add(void ***list, const void *item)
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
	new[length] = (void *)item;
	index = length;
	while (length--)
		new[length] = (*list)[length];
	if (*list)
		free(*list);
	*list = new;
	return (index);
}

void			ft_array_remove(void ***list, const unsigned short index)
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

char			*ft_itoa(const int n)
{
	char *nbr;

	if (!(nbr = malloc(ft_count(n) + 1)))
		return (NULL);
	return (ft_setnbr(n, nbr));
}
