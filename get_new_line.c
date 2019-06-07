/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivaton <frivaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 08:12:55 by frivaton          #+#    #+#             */
/*   Updated: 2019/05/14 08:46:27 by frivaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

static char *g_str[MAX_FD];

static int			get_read(const int fd)
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*temp;

	ft_bzero(buf, BUFF_SIZE);
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		temp = g_str[fd];
		g_str[fd] = ft_strjoin(temp, buf);
		free(temp);
		ft_bzero(buf, BUFF_SIZE);
		if (ft_strchr(g_str[fd], '\n') != NULL)
			return (1);
	}
	return (ret);
}

static int			get_sub(const int fd, char **line)
{
	char			*temp;
	int				i;

	i = 0;
	while (g_str[fd][i] && g_str[fd][i] != '\n')
		i++;
	if ((*line = ft_strsub(g_str[fd], 0, i)) == NULL)
		return (-1);
	temp = g_str[fd];
	if ((g_str[fd] = ft_strsub(temp, i + 1, ft_strlen(temp) - i - 1)) == NULL)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	return (1);
}

int					get_next_line(const int fd, char **line)
{
	int				ret;

	if (fd < 0 || line == NULL || fd > MAX_FD || BUFF_SIZE <= 0)
		return (-1);
	if (g_str[fd] == NULL)
		if ((g_str[fd] = ft_strdup("")) == NULL)
			return (-1);
	if ((ret = get_read(fd)) < 0)
		return (-1);
	if (ft_strchr(g_str[fd], '\n') != NULL)
	{
		ret = get_sub(fd, line);
		return (ret);
	}
	*line = g_str[fd];
	g_str[fd] = NULL;
	return (ret == 0 && **line == 0) ? 0 : 1;
}
