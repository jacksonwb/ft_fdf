/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbeall <jbeall@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:08:21 by jbeall            #+#    #+#             */
/*   Updated: 2018/12/14 17:30:18 by jbeall           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

# define HH 1
# define H 2
# define L 3
# define LL 5
# define ZEROS 0
# define START 1
# define END 2
# define MAX(x, y) x > y ? x : y

typedef struct			s_block
{
	char				hash_flag;
	char				zero_flag;
	char				minus_flag;
	char				plus_flag;
	char				space_flag;
	char				is_neg;
	char				prepend;
	int					width;
	char				p_flag;
	int					p;
	char				is_nan;
	char				is_inf;
	char				mod;
	int					c;
	char				valid;
}						t_block;

int						ft_printf(const char *format, ...);
int						pf_call_handler(t_block *block, va_list ap);

/*
** Parse Handlers
*/

int						block_parser(const char *s, t_block *block, va_list ap);
int						parse_mod(const char *s, t_block *block);
const char				*parse_flag(const char *s, t_block *block);
const char				*parse_width(const char *s, t_block *block, va_list ap);
int						handle_star_width(t_block *block, va_list ap,
	int star_flag);
const char				*parse_p(const char *s, t_block *block, va_list ap);
const char				*parse_c(const char *s, t_block *block);

/*
** Coversion Handlers
*/
int						handle_c(t_block *block, va_list ap);
int						handle_s(t_block *block, va_list ap);
int						handle_p(t_block *block, va_list ap);
int						handle_d(t_block *block, va_list ap);
int						handle_u(t_block *block, va_list ap);
int						handle_o(t_block *block, va_list ap);
int						handle_x(t_block *block, va_list ap);
int						handle_f(t_block *block, va_list ap);
int						handle_percent(t_block *block);
int						handle_plain(const char *s);

/*
** Handler utilities
*/
long long int			signed_handle_mod(t_block *block, va_list ap);
unsigned long long int	unsigned_handle_mod(t_block *block, va_list ap);
int						write_unsigned(t_block *block, unsigned long long n,
	char *s, char *prepend);
long double				float_handle_mod(t_block *block, va_list ap);
int						count_big_f(long double f);
long double				pf_atof_helper(char *s);
char					*big_f(long double f);
char					*little_f(long double f, int p, char *big_f);
void					pad_block_f(int len, t_block *block, int seg);
int						block_len_f(char *big_s, t_block *block);
char					set_sign_f(long double f, t_block *block);
void					flag_manager_f(long double f, t_block *block);
void					flag_helper_f_nan(t_block *block);
int						write_f(t_block *block, char sign, char *big_s,
	char *little_s);
void					free_helper_f(t_block *block, char *big_s,
	char *little_s);
long double				ten_pow(int pow);
int						is_even_str(char *str);
long double				ft_round(long double f, t_block *block);
int						is_signed_conv(int c);
void					flag_manager(t_block *block);
void					pad_block(t_block *block, int len, int b_len, int seg);
int						block_len(t_block *block, int len, char *prepend);
char					set_sign(long long int n, t_block *block);

/*
** Utilities
*/
void					write_padding(int len, char c);
char					*pf_dtoa_signed(long long int n);
int						places(unsigned long long n, int base);
char					*pf_dtoa_u(unsigned long long int n, int base, char c);
void					zero_helper(t_block *block, int *count);
int						is_nan(long double f);
int						is_inf(long double f);
int						is_not_even_str(char *str);

#endif
