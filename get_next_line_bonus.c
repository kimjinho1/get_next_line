/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinhokim <jinhokim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 08:45:05 by jinhokim          #+#    #+#             */
/*   Updated: 2022/09/01 17:33:02 by jinhokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check_newline(char *stack)
{
	int			i;

	i = 0;
	while (stack[i])
	{
		if (stack[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_split_stack(char **stack, char **line, int nl_idx)
{
	char		*temp;
	int			len;

	(*stack)[nl_idx] = '\0';
	*line = ft_strdup(*stack);
	len = ft_strlen(*stack + nl_idx + 1);
	if (len == 0)
	{
		free(*stack);
		*stack = 0;
		return (1);
	}
	temp = ft_strdup(*stack + nl_idx + 1);
	free(*stack);
	*stack = temp;
	return (1);
}

int	ft_return_all(char **stack, char **line, int ret)
{
	int			nl_idx;

	if (ret < 0)
		return (-1);
	if (*stack)
	{
		nl_idx = ft_check_newline(*stack);
		if (nl_idx >= 0)
			return (ft_split_stack(stack, line, nl_idx));
		else
		{
			*line = *stack;
			*stack = 0;
			return (0);
		}
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*stack[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	int			nl_idx;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		stack[fd] = ft_strjoin(stack[fd], buf);
		nl_idx = ft_check_newline(stack[fd]);
		if (nl_idx >= 0)
			return (ft_split_stack(&stack[fd], line, nl_idx));
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_return_all(&stack[fd], line, ret));
}
