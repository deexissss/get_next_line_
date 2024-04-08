/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjehaes <tjehaes@student.42luxembourg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 10:50:22 by tjehaes           #+#    #+#             */
/*   Updated: 2024/04/08 12:50:58 by tjehaes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_buffer(int fd, char *left, char *buff);
char	*set_line(char *line_buffer);

char	*get_next_line(int fd)
{
	static char	*left;
	char		*line;
	char		*buff;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left);
		free(buff);
		left = NULL;
		buff = NULL;
		return (0);
	}
	if (!buff)
		return (NULL);
	line = fill_buffer(fd, left, buff);
	free(buff);
	buff = NULL;
	if (!line)
		return (NULL);
	left = set_line(line);
	return (line);
}

char	*set_line(char *line_buffer)
{
	char	*left;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == 0)
		return (0);
	left = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*left == 0)
	{
		free(left);
		left = NULL;
	}
	line_buffer[i + 1] = 0;
	return (left);
}

char	*fill_buffer(int fd, char *left, char *buff)
{
	ssize_t	read_buffer;
	char	*temp;

	read_buffer = 1;
	while (read_buffer > 0)
	{
		read_buffer = read(fd, buff, BUFFER_SIZE);
		if (read_buffer == -1)
		{
			free(left);
			return (0);
		}
		else if (read_buffer == 0)
			break ;
		buff[read_buffer] = 0;
		if (!left)
			left = ft_strdup("");
		temp = left;
		left = ft_strjoin(temp, buff);
		free(temp);
		temp = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (left);
}
