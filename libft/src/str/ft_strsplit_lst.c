/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_lst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:49:18 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/03 14:56:20 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*new_elem(const char *s, char c, t_list *lst)
{
	t_list		*new;
	size_t		wordlen;
	static int	first = 1;

	wordlen = ft_countseg(s, c);
	if (!(new = ft_lstnew(NULL, 0)))
		return (NULL);
	if (!(new->content = ft_strsub(s, 0, wordlen)))
		return (NULL);
	new->content_size = wordlen + 1;
	if (first)
	{
		lst = new;
		first = 0;
	}
	else
		ft_lstappend(lst, new);
	return (lst);
}

t_list			*ft_strsplit_lst(char const *s, char c)
{
	t_list		*lst;
	int			flag;
	int			i;

	i = 0;
	flag = 0;
	if (!s)
		return (NULL);
	if (!(ft_wordcount(s, c)))
		return (NULL);
	while (*s)
	{
		if (*s != c && !flag)
		{
			flag = 1;
			if (!(lst = new_elem(s, c, lst)))
				return (NULL);
		}
		else if (*s == c && flag)
			flag = 0;
		++s;
	}
	return (lst);
}
