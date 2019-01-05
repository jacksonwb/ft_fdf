/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 15:35:05 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/03 14:54:54 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	cache_filler(const int fd, char **cache, int *eof)
{
	int		read_size;
	char	buf[BUFF_SIZE + 1];
	char	*temp;

	read_size = read(fd, buf, BUFF_SIZE);
	if (read_size < 0)
		*eof = -1;
	else if (read_size == 0)
		*eof = 1;
	else
	{
		buf[read_size] = '\0';
		if (*cache)
		{
			temp = *cache;
			*cache = ft_strjoin(*cache, buf);
			free(temp);
		}
		else
			*cache = ft_strsub(buf, 0, read_size);
	}
	return (read_size);
}

static char	*line_builder(const int fd, char **cache, int *eof)
{
	char	*str;
	char	*end;
	int		read_size;

	end = NULL;
	str = NULL;
	while ((read_size = cache_filler(fd, cache, eof)) > 0 || **cache)
	{
		if ((end = ft_strchr(*cache, '\n')))
		{
			str = ft_strsub(*cache, 0, (end - *cache));
			break ;
		}
		else if (read_size < BUFF_SIZE)
		{
			str = ft_strsub(*cache, 0, ft_strlen(*cache));
			break ;
		}
	}
	return (str);
}

static char	**get_buffer(t_list **alst, const int fd)
{
	t_list	*tmp;
	t_list	*lst;

	lst = *alst;
	while (lst)
	{
		if (fd == ((t_thread*)lst->content)->fd)
			return (((t_thread*)lst->content)->cache);
		lst = lst->next;
	}
	NULL_CHECK((tmp = (t_list*)ft_memalloc(sizeof(t_list))));
	NULL_CHECK((tmp->content = ft_memalloc(sizeof(t_thread))));
	tmp->content_size = sizeof(t_thread);
	tmp->next = NULL;
	((t_thread*)(tmp->content))->fd = fd;
	NULL_CHECK((((t_thread*)tmp->content)->cache =
		(char**)ft_memalloc(sizeof(char*))));
	NULL_CHECK((*(((t_thread*)tmp->content)->cache) =
		(char*)ft_memalloc(sizeof(char))));
	if (*alst)
		ft_lstappend(*alst, tmp);
	else
		*alst = tmp;
	return (((t_thread*)(tmp->content))->cache);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*lst = NULL;
	char			**cache;
	int				eof;
	char			*tmp;

	if (fd < 0 || fd > 8191 || !line || (BUFF_SIZE < 1))
		return (-1);
	if (!(cache = get_buffer(&lst, fd)))
		return (-1);
	eof = 0;
	*line = line_builder(fd, cache, &eof);
	if (*line && ft_strlen(*cache) > ft_strlen(*line))
	{
		tmp = *cache;
		*cache = ft_strsub(*cache, ft_strlen(*line) + 1, ft_strlen(*cache) -
			ft_strlen(*line) - 1);
		free(tmp);
	}
	else
		ft_bzero(*cache, ft_strlen(*cache));
	if (eof == -1)
		return (-1);
	return (!eof || *line ? 1 : 0);
}
