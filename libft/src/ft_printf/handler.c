/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 17:09:38 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/26 21:12:18 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_c(t_block *block, va_list ap)
{
	char c;

	c = va_arg(ap, int);
	if (block->width && !block->minus_flag && !block->zero_flag)
		write_padding(block->width - 1, ' ');
	if (block->width && !block->minus_flag && block->zero_flag)
		write_padding(block->width - 1, '0');
	write(1, &c, 1);
	if (block->width && block->minus_flag)
		write_padding(block->width - 1, ' ');
	return (block->width ? block->width : 1);
}

int	handle_percent(t_block *block)
{
	if (block->width && !block->zero_flag && !block->minus_flag)
		write_padding(block->width - 1, ' ');
	if (block->width && block->zero_flag && !block->minus_flag)
		write_padding(block->width - 1, '0');
	write(1, "%", 1);
	if (block->width && block->minus_flag)
		write_padding(block->width - 1, ' ');
	return (block->width ? block->width : 1);
}

int	handle_s(t_block *block, va_list ap)
{
	char	*s;
	int		len;

	s = va_arg(ap, char*);
	len = s ? ft_strlen(s) : 6;
	if (block->p_flag && block->p < len)
		len = block->p;
	if (block->width && !block->minus_flag && !block->zero_flag
		&& block->width > len)
		write_padding(block->width - len, ' ');
	if (block->width && !block->minus_flag && block->zero_flag
		&& block->width > len)
		write_padding(block->width - len, '0');
	s ? write(1, s, len) : write(1, "(null)", len);
	if (block->width && block->minus_flag && block->width > len)
		write_padding(block->width - len, ' ');
	return (block->width > len ? block->width : len);
}

int	handle_p(t_block *block, va_list ap)
{
	void	*p;
	char	*s;
	int		len;
	int		b_len;

	p = va_arg(ap, void*);
	s = ft_ptoa(p, 'a')	;
	block->prepend = 1;
	len = (block->p_flag && !block->p && !p ? 0 : ft_strlen(s));
	b_len = block_len(block, len, "0x");
	pad_block(block, len, b_len, START);
	write(1, "0x", 2);
	pad_block(block, len, b_len, ZEROS);
	write(1, s, len);
	pad_block(block, len, b_len, END);
	free(s);
	return (MAX(block->width, b_len));
}

int	handle_d(t_block *block, va_list ap)
{
	long long int	n;
	char			sign;
	char			*s;
	int				len;
	int				b_len;

	n = signed_handle_mod(block, ap);
	s = pf_dtoa_signed(n);
	flag_manager(block);
	sign = set_sign(n, block);
	len = block->p_flag && !block->p && n == 0 ? 0 : ft_strlen(s);
	b_len = block_len(block, len, NULL);
	pad_block(block, len, b_len, START);
	if (n < 0 || block->plus_flag || block->space_flag)
		write(1, &sign, 1);
	pad_block(block, len, b_len, ZEROS);
	write(1, s, len);
	pad_block(block, len, b_len, END);
	free(s);
	return (block->width > b_len ? block->width : b_len);
}
