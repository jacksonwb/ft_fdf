/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 16:54:05 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/05 15:00:01 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		input_lst(t_list **lst, int fd)
{
	char	*line;
	char	**line_split;
	int		len;
	int		count;
	int		status;

	len = 0;
	while ((status = get_next_line(fd, &line)))
	{
		line_split = ft_strsplit(line, ' ');
		free(line);
		count = fdf_count_row(line_split);
		if (!count || status < 0)
			return (0);
		else if (!len)
			len = count;
		else if (count != len)
			return (0);
		add_line(lst, line_split);
	}
	return (len);
}

int		*atoi_map(char **line_split, int len)
{
	int *row;
	int i;

	i = 0;
	row = (int*)ft_memalloc(sizeof(int) * len);
	while (i < len)
	{
		row[i] = ft_atoi(line_split[i]);
		i++;
	}
	return (row);
}

void	lst_map(t_map *mp, t_list *lst)
{
	t_point	**ar;
	t_list	*lst_head;
	int		rows;
	int		i;
	int		j;

	lst_head = lst;
	rows = ft_lstcount(lst);
	ar = (t_point**)ft_memalloc(sizeof(t_point*) * rows);
	i = -1;
	while (lst)
	{
		ar[++i] = (t_point*)ft_memalloc(sizeof(t_point) * mp->cols);
		j = -1;
		while (j < mp->cols - 1)
		{
			ar[i][++j].y = i;
			ar[i][j].x = j;
			ar[i][j].z = -ft_atoi(((char**)lst->content)[j]);
		}
		lst = lst->next;
	}
	fdf_free_lst(lst_head);
	mp->rows = rows;
	mp->map = ar;
}

void	fdf_free_lst(t_list *lst)
{
	int		i;
	t_list	*temp;

	while (lst)
	{
		i = 0;
		while (((char**)lst->content)[i])
			free(((char**)lst->content)[i++]);
		free(lst->content);
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}

void	fdf_parse(char *arg, t_map *mp)
{
	int		fd;
	int		len;
	t_list	*lst;

	lst = 0;
	fd = open(arg, O_RDWR);
	if (fd < 0)
		fdf_die("fdf");
	if (!(len = input_lst(&lst, fd)))
		die("Error");
	mp->cols = len;
	lst_map(mp, lst);
	mp->z_max = get_map_max(mp);
	mp->z_min = get_map_min(mp);
}
