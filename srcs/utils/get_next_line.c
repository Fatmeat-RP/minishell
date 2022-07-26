#include <minishell.h>

int	get_next_line(char **line)
{
	char	buffer[512];
	int		readed;
	int		i;
	char	c;

	i = 0;
	readed = read(0, &c, 1);
	while (readed && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		readed = read(0, &c, 1);
	}
	buffer[i++] = '\n';
	buffer[i] = '\0';
	*line = ft_strdup(buffer);
	return (readed);
}