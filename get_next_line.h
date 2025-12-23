/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42kocaeli.com.tr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:03:52 by eates             #+#    #+#             */
/*   Updated: 2025/12/23 18:03:53 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# elif BUFFER_SIZE <= 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 16
# elif BUFFER_SIZE > 5000000
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

char	*get_next_line(int fd);

#endif
