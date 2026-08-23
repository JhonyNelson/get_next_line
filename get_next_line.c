/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhcosta- <jhcosta-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:47:16 by jhcosta-          #+#    #+#             */
/*   Updated: 2026/08/04 16:47:25 by jhcosta-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_saved(int fd, char *saved, char *buf)
{
	char	*joined;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (!gnl_strchr(saved, SEPARATOR) && bytes_read > 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(saved);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		joined = gnl_strjoin(saved, buf);
		if (!joined)
		{
			free(saved);
			return (NULL);
		}
		saved = joined;
	}
	return (saved);
}

static char	*read_to_saved(int fd, char *saved)
{
	char	*buf;

	buf = malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
	{
		free(saved);
		return (NULL);
	}
	saved = fill_saved(fd, saved, buf);
	free(buf);
	return (saved);
}

static int	update_saved(char **saved)
{
	char	*remainder;

	if (!gnl_strchr(*saved, SEPARATOR))
	{
		free(*saved);
		*saved = NULL;
		return (0);
	}
	remainder = gnl_get_remainder(*saved);
	*saved = remainder;
	if (!*saved)
		return (-1);
	return (0);
}

static char	*extract_saved(char **saved)
{
	char	*line;

	line = gnl_extract_line(*saved);
	if (!line)
	{
		free(*saved);
		*saved = NULL;
		return (NULL);
	}
	if (update_saved(saved) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	saved = read_to_saved(fd, saved);
	if (!saved)
		return (NULL);
	if (saved[0] == '\0')
	{
		free(saved);
		saved = NULL;
		return (NULL);
	}
	return (extract_saved(&saved));
}
