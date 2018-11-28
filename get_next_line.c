/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivaton <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 10:13:38 by frivaton          #+#    #+#             */
/*   Updated: 2018/11/28 17:12:39 by frivaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "./libft/libft.h"

static int		fct_read_all(char **sfull, const int fd)
{
	char	*stmp;
	int		ret;

	if ((stmp = ft_strnew(BUFF_SIZE + 1)) == NULL)
		return (-1);
	while ((ret = read(fd, (void *)stmp, BUFF_SIZE)) > 0)
	{
		stmp[ret] = '\0';
		*sfull = ft_strjoin(*sfull, stmp);
		stmp[0] = 0;
	}
	ft_strdel(&stmp);
	if (*sfull[0])
		return (1);
	return (ret);
}

static int		fct_read_line(char *stmp, int *ipos, char **line)
{
	int i;

	i = 0;
	if (!stmp[0])
		return (0);
	while (stmp[i] && stmp[i] != '\n')
		i++;
	if (stmp[i] == '\n')
	{
		*line = ft_strsub(stmp, 0, i);
		if (!stmp[i + 1])
			return (1);
		*ipos = i + 1;
		return (2);
	}
	*line = ft_strsub(stmp, 0, i);
	stmp[0] = 0;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char	*snew = NULL;
	int			ret;
	int			ipos;

	if (!snew)
	{
		if ((snew = ft_strnew(BUFF_SIZE)) == NULL)
			return (-1);
		if ((ret = fct_read_all(&snew, fd)) <= 0)
		{
			ft_strdel(&snew);
			return (ret);
		}
	}
	ret = fct_read_line(snew, &ipos, line);
	if (ret == 2)
	{
		ft_memmove(snew, snew + ipos, ft_strlen(snew));
		return (1);
	}
	ft_strdel(&snew);
	return (ret);
}
