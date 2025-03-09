/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <yhusieva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:25:21 by yhusieva          #+#    #+#             */
/*   Updated: 2025/03/08 14:42:22 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_gnl(char *buff, char *read_tmp)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!buff)
	{
		buff = (char *)malloc(sizeof(char));
		buff[0] = 0;
	}
	if (!buff || !read_tmp)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(buff) + ft_strlen(read_tmp) + 1));
	if (new == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (buff)
		while (buff[++i] != '\0')
			new[i] = buff[i];
	while (read_tmp[j] != '\0')
		new[i++] = read_tmp[j++];
	new[ft_strlen(buff) + ft_strlen(read_tmp)] = '\0';
	free(buff);
	return (new);
}

static char	*read_chunk(int fd, char *buffer)
{
	int		bytes_read;
	char	*read_buffer;

	read_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			read_buffer[bytes_read] = '\0';
			buffer = ft_strjoin_gnl(buffer, read_buffer);
			if (ft_strchr(buffer, '\n'))
				break ;
		}
		else
			break ;
	}
	free(read_buffer);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_substr(buffer, 0, i + (buffer[i] == '\n'));
	return (line);
}

static char	*get_remaining(char *buffer)
{
	int		i;
	char	*remaining;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	remaining = ft_substr(buffer, i, ft_strlen(buffer + i));
	if (!remaining)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_chunk(fd, buffer);
	if (!buffer)
		return (NULL);
	line = get_line(buffer);
	buffer = get_remaining(buffer);
	return (line);
}
