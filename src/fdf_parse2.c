/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 20:12:51 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/05 14:40:20 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_die(char *msg)
{
	perror(msg);
	exit(0);
}

void	add_line(t_list **lst, char **line_split)
{
	t_list *new;

	if (!*lst)
	{
		*lst = ft_lstnew(NULL, 0);
		(*lst)->content = (void*)line_split;
	}
	else
	{
		new = (t_list*)ft_memalloc(sizeof(t_list));
		new->content = (void*)line_split;
		ft_lstappend(*lst, new);
	}
}

int		fdf_count_row(char **line_split)
{
	int i;

	i = 0;
	while (line_split[i])
		i++;
	return (i);
}

void	fdf_persp(t_vector *v, t_mlx *mlx)
{
	v->x = v->x / (1 + v->z / mlx->cam->focal_length);
	v->y = v->y / (1 + v->z / mlx->cam->focal_length);
}
