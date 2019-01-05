/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:45:23 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/03 14:56:20 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	places(unsigned long long n)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		++count;
		n /= 16;
	}
	return (count);
}

char		*ft_ptoa(void *p, char c)
{
	char				*s;
	unsigned long long	n;
	int					i;

	n = (unsigned long long)p;
	i = places(n);
	if (!(s = (char*)ft_memalloc(i + 1)))
		return (NULL);
	if (p == NULL)
		s[0] = '0';
	while (n)
	{
		s[--i] = (n % 16 > 9) ? (n % 16 - 10 + c) : (n % 16 + '0');
		n /= 16;
	}
	return (s);
}
