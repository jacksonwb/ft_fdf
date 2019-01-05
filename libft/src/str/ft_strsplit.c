/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:14:44 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/03 14:56:20 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_seg(char const *s, char c)
{
	size_t	size;

	size = 0;
	while (*s && *s != c)
	{
		++size;
		++s;
	}
	return (size);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**ar;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	if (!s)
		return (NULL);
	if (!(ar = (char**)ft_memalloc(sizeof(char*) * (ft_wordcount(s, c)) + 1)))
		return (NULL);
	while (*s)
	{
		if (*s != c && !flag)
		{
			flag = 1;
			if (!(ar[i++] = ft_strsub(s, 0, count_seg(s, c))))
				return (NULL);
		}
		else if (*s == c && flag)
			flag = 0;
		++s;
	}
	ar[i] = NULL;
	return (ar);
}
