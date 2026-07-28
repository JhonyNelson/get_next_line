#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);

/* helpers (get_next_line_utils.c) */
size_t	gnl_strlen(char *s);
char	*gnl_strchr(char *s, char c);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_extract_line(char *saved);
char	*gnl_get_remainder(char *saved);

#endif
