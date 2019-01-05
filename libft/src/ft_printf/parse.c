/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 10:35:37 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/29 11:34:24 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			parse_mod(const char *s, t_block *block)
{
	char		*ptr;
	static char	key[] = "hlL";

	if (ft_strnstr(s, "hh", 2))
	{
		block->mod = 1;
		return (2);
	}
	else if (ft_strnstr(s, "ll", 2))
	{
		block->mod = 5;
		return (2);
	}
	else if ((ptr = ft_strchr(key, *s)) && *s)
	{
		block->mod = ptr - key + 2;
		return (1);
	}
	return (0);
}

const char	*parse_flag(const char *s, t_block *block)
{
	while (ft_strchr("#0-+ ", *s) && *s)
	{
		if (*s == '#')
			block->hash_flag = 1;
		else if (*s == '0')
			block->zero_flag = 1;
		else if (*s == '-')
			block->minus_flag = 1;
		else if (*s == '+')
			block->plus_flag = 1;
		else if (*s == ' ')
			block->space_flag = 1;
		++s;
	}
	return (s);
}

const char	*parse_width(const char *s, t_block *block, va_list ap)
{
	int star_flag;

	star_flag = 0;
	if (*s == '*')
	{
		star_flag = handle_star_width(block, ap, star_flag);
		++s;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (!(block->width) || star_flag)
			block->width = ft_atoi(s);
		++s;
	}
	if (*s == '*')
	{
		star_flag = handle_star_width(block, ap, star_flag);
		++s;
	}
	return (s);
}

const char	*parse_p(const char *s, t_block *block, va_list ap)
{
	int garbage;

	if (*s == '.')
	{
		block->p_flag = 1;
		++s;
	}
	while (*s >= '0' && *s <= '9' && block->p_flag)
	{
		if (!(block->p))
			block->p = ft_atoi(s);
		++s;
	}
	if (*s == '*' && block->p_flag)
	{
		if (!block->p)
			block->p = va_arg(ap, int);
		else
			garbage = va_arg(ap, int);
		if (block->p < 0)
			block->p_flag = 0;
		++s;
	}
	return (s);
}

const char	*parse_c(const char *s, t_block *block)
{
	static char key[] = "cspdouxXf%";

	if (*s && (ft_strchr(key, *s) || *s == 'i'))
	{
		block->c = ft_strchr(key, *s) - key;
		if (*s == 'i')
			block->c = 3;
		block->valid = 1;
		++s;
	}
	return (s);
}
