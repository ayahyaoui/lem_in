/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anyahyao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 17:48:29 by anyahyao          #+#    #+#             */
/*   Updated: 2018/07/22 17:50:46 by anyahyao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long		ft_atol(char *str)
{
	int i;
	int neg;
	long res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] > 0 && str[i] < 33 && str[i] != 27)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		res = res * 10 + (int)str[i] - 48;
		i++;
	}
	return (neg * res);
}
