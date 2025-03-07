/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:13:23 by yhusieva          #+#    #+#             */
/*   Updated: 2024/04/06 13:13:25 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *buff, char *read_tmp)
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

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	if (c == 0)
		return ((char *)s + (ft_strlen(s)));
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	i;
	size_t	s_len;

	if (s == NULL || len == 0)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return ("");
	if (len > s_len - start)
		len = s_len - start;
	subs = (char *)malloc((len + 1) * sizeof(char));
	if (subs == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}
