/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhusieva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 13:13:18 by yhusieva          #+#    #+#             */
/*   Updated: 2024/04/06 13:13:19 by yhusieva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

// MAIN BODY
char	*get_next_line(int fd);
char	*read_chunk(int fd, char *buffer);
char	*get_line(char *buffer);
char	*get_remaining(char *buffer);

// UTILS
size_t	ft_strlen(const char *str);
char	*ft_strjoin_gnl(char *buff, char *read_tmp);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);

#endif
