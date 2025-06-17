/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:58:59 by tsaeed            #+#    #+#             */
/*   Updated: 2024/12/12 16:38:00 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_file(int fd, char *keep)
{
	char	*temp;
	int		rd;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
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
	if (!keep[i])
	{
		free(keep);
		return (NULL);
	}
	rtn = malloc(sizeof(char) * (ft_strlen(keep) - i));
	if (!rtn)
		return (NULL);
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
	static char	*keep[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	keep[fd] = ft_read_file(fd, keep[fd]);
	if (!keep[fd])
		return (NULL);
	line = ft_extract_line(keep[fd]);
	if (!line)
	{
		free(keep[fd]);
		keep[fd] = NULL;
		return (NULL);
	}
	keep[fd] = ft_delete_read(keep[fd]);
	return (line);
}
/*
int main (void)
{
		int     fd1,fd2;
		char    *line1 , *line2;
		fd1 = open("test.txt",O_RDONLY);
	fd2 = open("test2.txt",O_RDONLY);

		line1 =get_next_line(fd1);


		printf("%s",line1);
	free(line1);
	line2 =get_next_line(fd2);


		printf("%s",line2);
	free(line2);
		line1 =get_next_line(fd1);


		printf("%s",line1);
	free(line1);
	line2 =get_next_line(fd2);


		printf("%s",line2);
	free(line2);
		line1 =get_next_line(fd1);



		printf("%s",line1);
	free(line1);
	line2 =get_next_line(fd2);


		printf("%s",line2);
	close(fd1);
	close(fd2);

	free(line1);
	free(line2);

}*/
