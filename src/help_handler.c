/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:00:55 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/02 17:00:56 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void		ft_prec_nums(t_data *data, char **str)
{
	char	*new_str;
	char	*buff;
	char	c;

	buff = *str;
	if (data->prec == 0 && !ft_strcmp("0", *str))
	{
		**str = '\0';
		return ;
	}
	if (data->prec == -1)
		data->prec = 1;
	if ((size_t)data->prec < ft_strlen(*str))
		return ;
	c = (!ISDIGIT((*str)[0]) && data->spec == 'd') ? (*str)[0] : 0;
	if (c)
		(*str)++;
	new_str = ft_strnew(data->prec + !!c);
	ft_memset(new_str + !!c, '0', data->prec - ft_strlen(*str));
	ft_strcpy(new_str + data->prec - ft_strlen(*str) + !!c, *str);
	if (c)
		new_str[0] = c;
	free(buff);
	*str = new_str;
}

void		ft_prec_handle(t_data *data, char **str)
{
	if (data->prec == -1)
		return ;
	if (ft_strlen(*str) <= (size_t)data->prec)
		return ;
	(*str)[data->prec] = '\0';
}

void		ft_build_new(t_data *data, char **str, char *new_str)
{
	char	c;

	c = 0;
	if (data->flags & ZER)
	{
		c = (!ISDIGIT((*str)[0])) && data->spec == 'd' ? (*str)[0] : 0;
		ft_memset(new_str, '0', data->width - ft_strlen(*str) + !!c);
		if (c)
		{
			new_str[0] = c;
			(*str)[0] = '0';
		}
	}
	else
	{
		ft_memset(new_str, ' ', data->width - ft_strlen(*str));
		if ((data->flags & POS) && **str != '-')
			new_str[data->width - ft_strlen(*str)] = \
			((*str)[0] == '-') ? '-' : '+';
	}
	ft_strcpy(new_str + data->width - ft_strlen(*str) + !!c, *str + !!c);
}

void		ft_handle_zer(t_data *data, char **str)
{
	char	*new_str;

	if (data->width == 0 || ft_strlen(*str) >= (size_t)data->width)
		return ;
	new_str = ft_strnew(data->width);
	if (data->flags & LEFT)
	{
		ft_strcpy(new_str, *str);
		ft_memset(new_str + ft_strlen(*str), ' ', \
			data->width - ft_strlen(*str));
	}
	else
		ft_build_new(data, str, new_str);
	free(*str);
	*str = new_str;
	return ;
}
