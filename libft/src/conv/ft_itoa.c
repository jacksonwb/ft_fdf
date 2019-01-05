/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:45:23 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/03 14:56:20 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	places(int n)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		++count;
		n /= 10;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	int		neg;
	char	*s;
	int		i;

	if (n < 0)
		neg = 1;
	else
		neg = 0;
	i = places(n) + neg - 1;
	if (!(s = (char*)ft_memalloc(i + 2)))
		return (NULL);
	if (neg)
		s[0] = '-';
	if (n == 0)
	{
		s[i] = '0';
		return (s);
	}
	while (n)
	{
		s[i--] = ((n > 0) ? (n % 10) : -(n % 10)) + '0';
		n /= 10;
	}
	return (s);
}
