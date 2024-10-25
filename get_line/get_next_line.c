/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:25:33 by ikhalil           #+#    #+#             */
/*   Updated: 2024/10/25 16:26:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}

char	*freel(char **stash, char *b)
{
	if (*stash)
	{
		free(*stash);
		*stash = NULL;
	}
	if (b)
		free(b);
	return (NULL);
}

char	*read1(int fd, char *stash)
{
	char	*buf;
	char	*temp;
	int		bytes_read;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	bytes_read = read(fd, buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buf[bytes_read] = '\0';
		temp = stash;
		stash = ft_strjoin(stash, buf);
		free(temp);
		if (ft_strchr(stash, '\n'))
			break ;
		bytes_read = read(fd, buf, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (freel(&stash, buf));
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*temp;
	int			nlen;

	temp = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read1(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		freel(&stash, temp);
		return (NULL);
	}
	nlen = n_length(stash);
	line = ft_substr(stash, 0, nlen + 1);
	if (n_length(stash) != ft_strlen(stash))
	{
		temp = stash;
		stash = ft_substr(stash, nlen + 1, ft_strlen(stash) - nlen);
		free(temp);
	}
	else
		freel(&stash, temp);
	return (line);
}

/*int main() {
    int fd;
    char *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0) {
        perror("Error opening file"); 
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }

    close(fd); 
    return 0;
}*/
