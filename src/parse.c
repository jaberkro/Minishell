/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/19 14:08:32 by bsomers       #+#    #+#                 */
/*   Updated: 2022/07/21 16:44:10 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_info(t_part *parts)
{
	printf("START\n");
	printf("lb: %c\n", parts->lb);
	printf("str: %s\n", parts->str);
	printf("rb: %c\n", parts->rb);
	printf("END\n");
}

int	check_redirections_pipe(char *str)
{
	if (ft_strncmp(str, "<\0", 2) == 0 || ft_strncmp(str, ">\0", 2) == 0 || 
	ft_strncmp(str, "|\0", 2) == 0 || ft_strncmp(str, "<<\0", 3) == 0 || ft_strncmp(str, ">>\0", 3) == 0)
		return (0);
	else
		return (1);
}

int	count_redirections_pipe(char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && str[i+1] == '<')
		{
			j++;
			i = i + 2;
		}
		else if (str[i] == '>' && str[i+1] == '>')
		{
			j++;
			i = i + 2;
		}
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
		{
			j++;
			i++;
		}
		else
			i++;
	}
	return (j);
}

int	count_pipes(char *str)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '|')
		{
			j++;
			i++;
		}
		else
			i++;
	}
	return (j);
}

char	set_b(char *str)
{
	if (ft_strncmp(str, "<<\0", 3) == 0)
		return ('[');
	else if (ft_strncmp(str, ">>\0", 3) == 0)
		return(']');
	else
		return(str[0]);
}

void	make_parts_cmd(t_part *part, char *str)
{

}

void	make_parts_file(t_part *part, char *str)
{
	int	i;

	i = 0;
	while (i < (ft_strlen(str)))
	{
		//HIERRRRRR
		if (ft_strncmp(str[i], "<", 1) == 0)
			part->out_r = '<';
		else if (ft_strncmp(str[i], ">", 1) == 0)
			part->in_r = '>';
		else if (ft_strncmp((str[i] + str[i+1]), "<<", 2) == 0)
			part->out_r = '[';
		else if (ft_strncmp((str[i] + str[i+1]), ">>", 2) == 0)
			part->in_r = ']';
		i++;
	}
}

void	make_parts_r(t_part *part, char *str)
{
	int	i;

	i = 0;
	while (i < (ft_strlen(str)))
	{
		if (ft_strncmp(str[i], "<", 1) == 0)
			part->out_r = '<';
		else if (ft_strncmp(str[i], ">", 1) == 0)
			part->in_r = '>';
		else if (ft_strncmp((str[i] + str[i+1]), "<<", 2) == 0)
			part->out_r = '[';
		else if (ft_strncmp((str[i] + str[i+1]), ">>", 2) == 0)
			part->in_r = ']';
		i++;
	}
}

void	set_zero_parts(t_part *part)
{
	ft_bzero(part->in, 1);
	ft_bzero(part->cmd, 1);
	ft_bzero(part->out, 1);
	part->in_r = '\0';
	part->out_r = '\0';
}

void	exec_minishell(char *input)
{
	char **input_split;
	t_part *parts;
	int	count_red;
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (ft_strchr(input, '|') != NULL)
		input_split = ft_split(input, '|'); //REKENING HOUDEN MET PIPE TUSSEN QUOTES
	//input_split = ft_split(input, ' ');
	count_pipe = count_pipes(input);
	parts = malloc((count_pipe + 1) * sizeof(t_part *));
	while (i < (count_pipe + 1))
	{
		set_zero_parts(parts[i]);
		make_parts_r(parts[i], input_split[i]);
		///HIERONDER
		make_parts_cmd(parts[i], input_split[i]);
		make_parts_file(parts[i], input_split[i]);
		i++;
	}
	i = 0;



	while (check_redirections_pipe(input_split[i]) != 0 && input_split[i] != NULL)
	{
		if (i == 0)
			parts[0].str = ft_strdup(input_split[i]);
		else
			parts[0].str = ft_strjoin(parts[0].str, input_split[i]);
		i++;
	}
	parts[0].lb = 0;
	parts[0].rb = set_b(input_split[i]);
	while (input_split[i] != NULL)
	{
		if (ft_strncmp(input_split[i], "<<\0", 3) == 0)
			parts[j].lb = '[';
		else if (ft_strncmp(input_split[i], ">>\0", 3) == 0)
			parts[j].lb = ']';
		else
			parts[j].lb = *input_split[i]; //Check for quotes!!
		i++;
		if (check_redirections_pipe(input_split[i]) != 0)
			parts[j].str = ft_strdup(input_split[i]);
		while (check_redirections_pipe(input_split[i]) != 0 && input_split[i] != NULL)
		{
			parts[j].str = ft_strjoin(parts[j].str, input_split[i]);
			i++;
		}
		if (ft_strncmp(input_split[i], "<<\0", 3) == 0)
			parts[j].rb = '[';
		else if (ft_strncmp(input_split[i], ">>\0", 3) == 0)
			parts[j].rb = ']';
		else
			parts[j].rb = *input_split[i]; //Check for quotes!!
		print_info(&parts[j]);
		j++;
	}
	parts[j].str = NULL;
	parts[j].lb = '\0';
	parts[j].rb = '\0';
}

void	run_minishell()
{
	char *str;
	int	cmp;

	cmp = -1;
	while (cmp != 0)
	{
		str = readline("mickeyshell>");
		cmp = ft_strncmp(str, "exit\0", 5);
		if (cmp == 0)
			break ;
		exec_minishell(str);
		free (str);
	}
	free (str);
	//exit_minishell();
}

int	main()
{
	run_minishell();
}