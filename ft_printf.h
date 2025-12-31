/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 13:05:07 by eates             #+#    #+#             */
/*   Updated: 2023/09/05 13:07:09 by eates            ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>

# define DECIMAL "0123456789"
# define HEXALOW "0123456789abcdef"
# define HEXAUP "0123456789ABCDEF"

int		write_char(char c, int *len);
int		write_string(char *s, int *len);
int		write_int(int n, int *len);
int		write_uint(unsigned int n, int *len);
int		write_point(void *n, int *len);
int		write_hex(unsigned int n, char c, int *len);
int		ft_printf(const char *s, ...);

#endif
