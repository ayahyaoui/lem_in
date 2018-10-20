/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 11:33:49 by emuckens          #+#    #+#             */
/*   Updated: 2018/06/26 19:44:33 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl/get_next_line.h"

static char	*ft_strjoinfree(char *str, char *str2)
{
	char	*new;

	new = NULL;
	if (!str)
		return (ft_strdupf(new, str2, 0));
	if (!(new = ft_strjoin(str, str2)))
		ft_strdel(&str2);
	ft_memset(str2, 0, BUFF_SIZE + 1);
	ft_strdel(&str);
	return (new);
}

static char	*ft_split_buff(char *str, int option)
{
	size_t		i;
	size_t		j;
	char		*line;

	i = 0;
	line = NULL;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (option == 1)
	{
		if (!(line = ft_strsub(str, 0, i)))
			ft_strdel(&str);
	}
	else if (option == 2)
	{
		j = str[i] ? i + 1 : i--;
		while (str[j] != 0)
			j++;
		line = ft_strsub(str, (unsigned int)(i + 1), j - i - 1);
		ft_strdel(&str);
	}
	return (line);
}

static int	inner_gnl(int fd, long int *ret, char **remain, char **buffer)
{
	while (!(ft_strchr(*remain, SEP))
			&& (*ret = read(fd, *buffer, BUFF_SIZE)) > 0)
	{
		if (*ret == BUFF_SIZE && !(*remain = ft_strjoinfree(*remain, *buffer)))
		{
			ft_strdel(buffer);
			return (-1);
		}
		if (*ret < BUFF_SIZE)
			*remain = ft_strjoinfree(*remain, *buffer);
		ft_bzero(*buffer, BUFF_SIZE);
	}
	ft_strdel(buffer);
	if (*ret == 0 && *remain && (*remain)[0] == 0)
	{
		ft_strdel(remain);
		return (0);
	}
	return (1);
}

int			get_next_line2(const int fd, char **line)
{
	static char		*remain;
	char			*buffer;
	long int		ret;

	buffer = NULL;
	if (BUFF_SIZE <= 0 || (ret = read(fd, "", 0)) == -1 || fd < 0)
		return (ft_display_error("getting line from file"));
	if (!(buffer = ft_strnew(BUFF_SIZE + 1)))
		return (ft_display_error("malloc getting line"));
	if (!inner_gnl(fd, &ret, &remain, &buffer))
		return (0);
	if (remain && !(*line = ft_split_buff(remain, 1)))
	{
		ft_strdel(&remain);
		return (-1);
	}
	remain = ft_split_buff(remain, 2);
	return (1);
}
