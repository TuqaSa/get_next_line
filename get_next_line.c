/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:30:51 by tsaeed            #+#    #+#             */
/*   Updated: 2024/12/12 17:38:39 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_read_file(int fd, char *keep)
{
	char	*temp;
	int		rd;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		return (NULL);
	}
	rd = 1;
	while (!ft_strchr(keep, '\n') && rd != 0)
	{
		rd = read(fd, temp, BUFFER_SIZE);
		if (rd == -1)
		{
			free(temp);
			free(keep);
			return (NULL);
		}
		temp[rd] = '\0';
		keep = ft_strjoin(keep, temp);
		if (!keep)
			break ;
	}
	free(temp);
	return (keep);
}

char	*ft_extract_line(char *keep)
{
	char	*line;
	int		i;

	i = 0;
	if (!keep[i])
		return (NULL);
	while (keep[i] != '\0' && keep[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (keep[i] != '\0' && keep[i] != '\n')
	{
		line[i] = keep[i];
		i++;
	}
	if (keep[i] == '\n')
	{
		line[i] = keep[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_delete_read(char *keep)
{
	char	*rtn;
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (keep[i] != '\0' && keep[i] != '\n')
		i++;
	rtn = malloc(sizeof(char) * (ft_strlen(keep) - i + 1));
	if (!rtn)
	{
		free(keep);
		return (NULL);
	}
	if (keep[i] == '\n')
		i++;
	while (keep[i + j] != '\0')
	{
		rtn[j] = keep[j + i];
		j++;
	}
	rtn[j] = '\0';
	free(keep);
	return (rtn);
}

char	*get_next_line(int fd)
{
	static char	*keep;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep = ft_read_file(fd, keep);
	if (!keep)
		return (NULL);
	line = ft_extract_line(keep);
	if (!line)
	{
		free(keep);
		keep = NULL;
		return (NULL);
	}
	keep = ft_delete_read(keep);
	if (!keep)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int main (void)
{
		int     fd;
		char    *line;
		fd = open("test.txt",O_RDONLY);
		line =get_next_line(fd);
    
		printf("%s",line);
    
    free(line);

}
