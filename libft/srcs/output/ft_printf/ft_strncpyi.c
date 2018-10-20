/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpyi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emuckens <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 15:01:44 by emuckens          #+#    #+#             */
/*   Updated: 2018/03/05 16:49:46 by emuckens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf/ft_printf.h"

void	ft_strncpyi_buf(t_env *env, unsigned char src[], int *index, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (src[j] && j < n)
	{
		if (*index + i >= BUFF_SIZE)
		{
			write(1, env->buf, i + *index);
			env->rindex += BUFF_SIZE;
			*index = 0;
			i = 0;
		}
		env->buf[*index + i] = src[j];
		++i;
		++j;
	}
	env->buf[*index + i] = '\0';
	*index += i;
}

void	ft_strncpyi_wbuf(t_env *env, unsigned char src[], int *index, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (src[j] && j < n)
	{
		if (*index + i >= BUFF_SIZE)
		{
			write(1, env->wbuf, i + *index);
			env->rindex += BUFF_SIZE;
			*index = 0;
			i = 0;
		}
		env->wbuf[*index + i] = src[j];
		++i;
		++j;
	}
	env->wbuf[*index + i] = '\0';
	*index += i;
}

void	ft_strncpyi_tmp(t_env *env, unsigned char src[], int *index, int n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (src[j] && j < n)
	{
		if (*index + i >= BUFF_SIZE)
		{
			write(1, env->tmpbuf, i + *index);
			env->rindex += BUFF_SIZE;
			*index = 0;
			i = 0;
		}
		env->tmpbuf[*index + i] = src[j];
		++i;
		++j;
	}
	env->tmpbuf[*index + i] = '\0';
	*index += i;
}

void	ft_strcpyi_buf(t_env *env, unsigned char src[], int *index)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (src[j])
	{
		if (*index + i >= BUFF_SIZE)
		{
			write(1, env->buf, i + *index);
			env->rindex += BUFF_SIZE;
			*index = 0;
			i = 0;
		}
		env->buf[*index + i] = src[j];
		++i;
		++j;
	}
	env->buf[*index + i] = '\0';
	*index += i;
}
