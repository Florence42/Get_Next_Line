/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivaton <frivaton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 09:02:28 by frivaton          #+#    #+#             */
/*   Updated: 2019/05/03 09:06:36 by frivaton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"

static int        get_read(const int fd, char **str)
{
    int        ret;
    char    buf[BUFF_SIZE + 1];
    char    *temp;

    ft_bzero(buf, BUFF_SIZE);
    while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
    {
        buf[ret] = '\0';
        temp = *str;
        *str = ft_strjoin(temp, buf);
        free(temp);
        ft_bzero(buf, BUFF_SIZE);
        if (ft_strchr(*str, '\n') != NULL)
            return (1);
    }
    return (ret);
}

int                get_next_line(const int fd, char **line)
{
    static char    *str[MAX_FD];
    char        *temp;
    int            ret;
    int            i;

    i = 0;
    if (fd < 0 || line == NULL || fd > MAX_FD || BUFF_SIZE <= 0)
        return (-1);
    if (str[fd] == NULL)
        str[fd] = ft_strdup("");
    if ((ret = get_read(fd, &str[fd])) < 0)
        return (-1);
    if (ft_strchr(str[fd], '\n') != NULL)
    {
        while (str[fd][i] && str[fd][i] != '\n')
            i++;
        *line = ft_strsub(str[fd], 0, i);
        temp = str[fd];
        str[fd] = ft_strsub(temp, i + 1, ft_strlen(temp) - i - 1);
        free(temp);
        return (1);
    }
    *line = str[fd];
    str[fd] = NULL;
    return (ret == 0 && **line == 0) ? 0 : 1;
}
