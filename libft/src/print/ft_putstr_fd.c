/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 17:27:37 by jbeall            #+#    #+#             */
/*   Updated: 2018/10/30 10:13:09 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char const *str, int fd)
{
	int len;
	int i;

	i = 0;
	len = 0;
	if (!str)
		return ;
	while (*(str + i++))
		len++;
	write(fd, str, len);
}
