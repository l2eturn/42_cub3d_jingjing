/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waragwon <waragwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:45:18 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/10/29 00:02:10 by waragwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd);

char	*get_next_line(int fd)
{
	static char	*readed[1024] = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readed[fd] = update_readed_gnl(fd, readed[fd]);
	if (!readed[fd])
		return (NULL);
	line = get_line_gnl(readed[fd]);
	readed[fd] = trim_read_gnl(readed[fd]);
	if (!line)
		return (NULL);
	if (line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

char	*update_readed_gnl(int fd, char *old_readed)
{
	char	*new_read;
	char	*tmp;

	if (!old_readed)
		return (read_file_gnl(fd));
	if (old_readed[0] == '\0')
	{
		free(old_readed);
		return (read_file_gnl(fd));
	}
	new_read = read_file_gnl(fd);
	if (!new_read)
		return (NULL);
	tmp = append_n_str(old_readed, new_read, ft_strlen_gnl(new_read));
	free(new_read);
	return (tmp);
}

char	*read_file_gnl(int fd)
{
	char	*buffer;
	ssize_t	byte_reads;
	char	*reading;

	byte_reads = 1;
	reading = ft_calloc_gnl(1, 1);
	buffer = ft_calloc_gnl(BUFFER_SIZE + 1, 1);
	if (!buffer || !reading)
		return (free(buffer), free(reading), NULL);
	while (byte_reads > 0)
	{
		byte_reads = read(fd, buffer, BUFFER_SIZE);
		if (byte_reads < 0)
			return (free(buffer), free(reading), NULL);
		buffer[byte_reads] = '\0';
		reading = append_n_str(reading, buffer, byte_reads);
		if (!reading || ft_strchr_gnl(buffer, '\n') >= 0)
			break ;
	}
	free(buffer);
	return (reading);
}

char	*get_line_gnl(char *readed)
{
	char	*line;
	size_t	len;

	len = 0;
	while (readed[len])
	{
		if (readed[len] == '\n')
		{
			len++;
			break ;
		}
		len++;
	}
	line = ft_calloc_gnl(1, 1);
	if (!line)
		return (NULL);
	line = append_n_str(line, readed, len);
	return (line);
}

char	*trim_read_gnl(char *old_readed)
{
	char	*trim;
	size_t	i;

	i = 0;
	while (old_readed[i] && old_readed[i] != '\n')
		i++;
	if (!old_readed[i])
	{
		free(old_readed);
		return (NULL);
	}
	trim = ft_calloc_gnl((ft_strlen_gnl(old_readed) - i + 1), 1);
	if (!trim)
		return (NULL);
	ft_strlcat_gnl(trim, &old_readed[i + 1], ft_strlen_gnl(old_readed) - i + 1);
	free(old_readed);
	return (trim);
}
