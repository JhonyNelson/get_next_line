#include "get_next_line.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *s, char c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = 0;
	if (s1)
		len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	result = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s1 && i < len1)
	{
		result[i] = s1[i];
		i++;
	}
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*gnl_extract_line(char *saved)
{
	char	*line;
	size_t	i;
	size_t	len;

	len = gnl_strlen(saved);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*gnl_get_remainder(char *saved)
{
	char	*newline;
	char	*remainder;
	size_t	i;

	newline = gnl_strchr(saved, '\n');
	if (!newline)
	{
		free(saved);
		return (NULL);
	}
	remainder = malloc(sizeof(char) * (gnl_strlen(newline + 1) + 1));
	if (!remainder)
	{
		free(saved);
		return (NULL);
	}
	i = 0;
	while (newline[i + 1])
	{
		remainder[i] = newline[i + 1];
		i++;
	}
	remainder[i] = '\0';
	free(saved);
	return (remainder);
}
