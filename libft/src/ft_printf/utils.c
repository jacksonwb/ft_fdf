/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:45:23 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/27 14:49:16 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		places(unsigned long long n, int base)
{
	int count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		++count;
		n /= base;
	}
	return (count);
}

char	*pf_dtoa_signed(long long int n)
{
	char				*s;
	int					i;

	i = places(n < 0 ? -n : n, 10);
	if (!(s = (char*)ft_memalloc(i + 1)))
		return (NULL);
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		s[--i] = ((n > 0) ? (n % 10) : -(n % 10)) + '0';
		n /= 10;
	}
	return (s);
}

char	*pf_dtoa_u(unsigned long long int n, int base, char c)
{
	char				*s;
	int					i;

	i = places(n, base);
	if (!(s = (char*)ft_memalloc(i + 1)))
		return (NULL);
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		s[--i] = (n % base > 9) ? (n % base - 10 + c) : (n % base + '0');
		n /= base;
	}
	return (s);
}

void	write_padding(int len, char c)
{
	while (len)
	{
		write(1, &c, 1);
		--len;
	}
}

int		write_unsigned(t_block *block, unsigned long long n,
	char *s, char *prepend)
{
	int len;
	int b_len;

	flag_manager(block);
	if (block->c == 'o' && block->hash_flag)
	{
		block->p = (block->p_flag && block->p > (int)ft_strlen(s) + 1)
			? block->p : ft_strlen(s) + 1;
		block->p_flag = 1;
	}
	len = block->p_flag && !block->p && n == 0 ? 0 : ft_strlen(s);
	b_len = block_len(block, len, prepend);
	pad_block(block, len, b_len, START);
	if (block->prepend)
		write(1, prepend, ft_strlen(prepend));
	pad_block(block, len, b_len, ZEROS);
	write(1, s, len);
	pad_block(block, len, b_len, END);
	free(s);
	return (block->width > b_len ? block->width : b_len);
}
