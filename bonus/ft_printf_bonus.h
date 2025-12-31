/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:05:07 by eates             #+#    #+#             */
/*   Updated: 2025/12/31 13:34:38 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

# define DECIMAL "0123456789"
# define HEXALOW "0123456789abcdef"
# define HEXAUP "0123456789ABCDEF"

typedef struct s_printf
{
	int	len;
	int	has_minus;
	int	has_dot;
	int	has_sharp;
	int	has_space;
	int	has_plus;
	int	has_zero;
	int	width;
	int	decimal;
	int	unlimit;
}	t_printf;

int			ft_printf(const char *s, ...);
int			ft_isdigit(int c);
size_t		ft_strlen(const char *s);
int			write_fill_char(int n, t_printf *pf);
char		*ft_strchr(const char *s, int c);
const char	*take_number_and_continue(const char *s, t_printf *pf);
int			write_char(char c, t_printf *pf);
int			write_char_with_flags(char c, t_printf *pf);
int			write_string(char *s, t_printf *pf);
int			write_string_with_flags(char *s, t_printf *pf);
int			write_pointer_with_flags(void *n, t_printf *pf);
int			write_int_with_flags(int n, t_printf *pf);
int			write_uint_with_flags(unsigned int n, t_printf *pf);
int			write_hex_with_flags(unsigned int n, char c, t_printf *pf);

#endif
