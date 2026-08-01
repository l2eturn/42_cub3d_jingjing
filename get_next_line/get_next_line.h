/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waroonwork@gmail.com <WaroonRagwongsiri    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 22:44:32 by waroonwork@       #+#    #+#             */
/*   Updated: 2025/06/22 22:44:32 by waroonwork@      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>
// # include <stdio.h>

// # define BUFFER_SIZE 42

char	*get_next_line(int fd);
void	*ft_calloc_gnl(size_t nmemb, size_t size);
char	*append_n_str(char *old, char *read, size_t index_lf);
size_t	ft_strlen_gnl(const char *s);
size_t	ft_strlcat_gnl(char *dst, const char *src, size_t dsize);
ssize_t	ft_strchr_gnl(const char *s, int c);
char	*read_file_gnl(int fd);
char	*update_readed_gnl(int fd, char *old_readed);
char	*get_line_gnl(char *readed);
char	*trim_read_gnl(char *old_readed);

#endif