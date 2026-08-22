/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhcosta- <jhcosta-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:48:45 by jhcosta-          #+#    #+#             */
/*   Updated: 2026/08/04 16:48:47 by jhcosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef SEPARATOR
#  define SEPARATOR '\n'
# endif

char	*get_next_line(int fd);

size_t	gnl_strlen(char *s);
char	*gnl_strchr(char *s, char c);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_extract_line(char *saved);
char	*gnl_get_remainder(char *saved);

#endif
