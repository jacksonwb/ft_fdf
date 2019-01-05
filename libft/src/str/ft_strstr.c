/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 17:05:15 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/03 14:56:20 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;
	size_t	needlel;

	needlel = ft_strlen(needle);
	i = 0;
	j = 0;
	if (needlel == 0)
		return ((char*)haystack);
	while (*haystack)
	{
		while (needle[j] == haystack[i])
		{
			if ((j + 1) == needlel)
				return ((char*)haystack);
			++i;
			++j;
		}
		j = 0;
		i = 0;
		++haystack;
	}
	return (NULL);
}
