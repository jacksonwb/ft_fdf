/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handlef_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:58:52 by jbeall            #+#    #+#             */
/*   Updated: 2018/11/29 20:56:01 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	ten_pow(int pow)
{
	long double f;

	f = 1;
	while (pow > 0)
	{
		f = f * 10;
		--pow;
	}
	while (pow < 0)
	{
		f = f / 10;
		++pow;
	}
	return (f);
}

int			is_not_even_str(char *str)
{
	return ((str[ft_strlen(str) - 1] - '0') % 2);
}

long double	ft_round(long double f, t_block *block)
{
	long double	temp;
	char		*big_s;
	char		*little_s;

	f = f < 0 ? -f : f;
	temp = f * ten_pow(block->p);
	big_s = big_f(temp);
	little_s = little_f(temp, block->p, big_s);
	temp -= pf_atof_helper(big_s);
	free(big_s);
	if (temp > 0.5 || (temp == 0.5 && is_not_even_str(big_s)))
		f += 0.5 * ten_pow(-block->p);
	return (f);
}

int			is_nan(long double f)
{
	return (!(f == f));
}

int			is_inf(long double f)
{
	if (f == (1.0 / 0.0) || f == -(1.0 / 0.0))
		return (1);
	else
		return (0);
}
