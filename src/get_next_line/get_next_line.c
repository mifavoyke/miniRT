/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:25:21 by yhusieva          #+#    #+#             */
/*   Updated: 2024/04/25 12:25:24 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_chunk(int fd, char *buffer)
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

char	*get_line(char *buffer)
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

char	*get_remaining(char *buffer)
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

// int main(int argc, char *argv[])
// {
// 	char *line;
// 	int fd;

// 	// line = get_next_line(0);
// 	// printf("%s", line);

// 	if (argc != 2)
// 	{
// 		printf("are you dumb. gimme the file %s", argv[0]);
// 		return (1);
// 	}
// 	fd = open(argv[1], O_RDONLY);
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
