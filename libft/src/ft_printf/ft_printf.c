/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:08:05 by jbeall            #+#    #+#             */
/*   Updated: 2019/01/04 21:09:22 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			block_parser(const char *s, t_block *block, va_list ap)
{
	const char *start;

	start = s;
	s = parse_flag(s, block);
	s = parse_width(s, block, ap);
	s = parse_p(s, block, ap);
	s += parse_mod(s, block);
	s = parse_c(s, block);
	return (s - start);
}

int			pf_call_handler(t_block *block, va_list ap)
{
	static int	(*handlers[11])(t_block *block, va_list ap) = {
		&handle_c,
		&handle_s,
		&handle_p,
		&handle_d,
		&handle_o,
		&handle_u,
		&handle_x,
		&handle_x,
		&handle_f
	};
	static int	(*handle_percent_ptr)(t_block *block) = &handle_percent;

	if (block->c == 9)
		return (handle_percent_ptr(block));
	return ((handlers[block->c](block, ap)));
}

int			handle_plain(const char *s)
{
	int		len;
	char	*next;

	next = ft_strchr(s, '%');
	len = next ? next - s : ft_strlen(s);
	write(1, s, len);
	return (len);
}

inline void	zero_helper(t_block *block, int *count)
{
	ft_bzero(block, sizeof(*block));
	*count = 0;
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	t_block	block;
	int		count;
	int		temp;

	zero_helper(&block, &count);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format += block_parser(format + 1, &block, ap) + 1;
			if (block.valid)
				count += pf_call_handler(&block, ap);
			ft_bzero(&block, sizeof(block));
		}
		else
		{
			temp = handle_plain(format);
			format += temp;
			count += temp;
		}
	}
	va_end(ap);
	return (count);
}
