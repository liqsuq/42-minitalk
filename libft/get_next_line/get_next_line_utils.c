/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 20:46:12 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/02 14:14:08 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_fgetc(int fd)
{
	static char		buf[BUFFER_SIZE];
	static ssize_t	pos;
	static ssize_t	size;

	if (pos >= size)
	{
		size = read(fd, buf, BUFFER_SIZE);
		pos = 0;
		if (size <= 0)
			return (EOF);
	}
	return ((unsigned char)buf[pos++]);
}
