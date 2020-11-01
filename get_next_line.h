/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xsun <xiaobai@student.42tokyo.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:42:23 by xsun              #+#    #+#             */
/*   Updated: 2020/11/01 19:45:33 by xsun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

int		smart_free(char **ptr1, char **ptr2, int ret);
ssize_t	ft_strchr(const char *s, char c);
char	*ft_strappend(char *l, char *r, size_t len_l, size_t len_r);
int		update_line_save(char **line, char **save, long long endl_pos);
ssize_t	update_save_by_buf(char **save, char **buf, ssize_t *read_size);
int		get_next_line(int fd, char **line);
#endif
