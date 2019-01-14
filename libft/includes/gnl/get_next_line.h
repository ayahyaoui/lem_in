/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:30:36 by emuckens          #+#    #+#             */
/*   Updated: 2019/01/14 17:42:42 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define BUFF_SIZE 200

# define SEP '\n'

typedef struct		s_file
{
	int				fd;
	char			padding[4];
	char			*buff;

}					t_file;

int					get_next_line(const int fd, char **line);

#endif
