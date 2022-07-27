#include <minishell.h>

static t_control_exec	*struct2(t_control_parse *parse, t_control_exec *exec,
	t_fthenorm *ntom, char **envp)
{
	if (parse->iter->flag == PIPE_FLAG)
	{
		exec->iter = exec->iter->next;
		ntom->in = 0;
		ntom->out = 0;
		ntom->i = 1;
	}
	else if (parse->iter->flag == CMD_FLAG)
	{
        exec->iter->cmd[0] = get_path(ft_strdup(parse->iter->elem), envp, 0);
	}
	else if (parse->iter->flag == BUILTIN_FLAG)
	{
		exec->iter->cmd[0] = ft_strdup(parse->iter->elem);
		exec->iter->is_builtin = true;
	}
    else if (parse->iter->flag == ARGS_FLAG)
	{
		exec->iter->cmd[ntom->i] = ft_strdup(parse->iter->elem);
		ntom->i++;
	}
	return (exec);
}

static t_control_exec	*struct3(t_control_parse *parse, t_control_exec *exec,
	t_fthenorm *ntom)
{
	if (parse->iter->flag == REDIR_IN_FLAG)
	{
		parse->iter = parse->iter->next;
		exec->iter->in[ntom->in++] = ft_strdup(parse->iter->elem);
	}
	else if (parse->iter->flag == REDIR_OUT_FLAG)
	{
		parse->iter = parse->iter->next;
		exec->iter->out[ntom->out] = ft_strdup(parse->iter->elem);
		exec->iter->is_append[ntom->out++] = '0';
	}
	else if (parse->iter->flag == REDIR_OUT_ADD_FLAG)
	{
		parse->iter = parse->iter->next;
		exec->iter->out[ntom->out] = ft_strdup(parse->iter->elem);
		exec->iter->is_append[ntom->out++] = '1';
	}
	else if (parse->iter->flag == HERE_DOC_FLAG)
	{
		parse->iter = parse->iter->next;
		exec->iter->is_here_doc = true;
		exec->iter->limiter = ft_strdup(parse->iter->elem);
	}
	return (exec);
}

t_control_exec	*structy(t_control_parse *parse, int nb_pipe, char **envp)
{
	t_control_exec	*exec;
	t_fthenorm		ntom;

	ntom.i = 1;
	ntom.in = 0;
	ntom.out = 0;
	exec = init_exe_list();
	if (test_free(exec, nb_pipe) == -1)
		return (NULL);
	while (parse->iter)
	{
		exec = struct3(parse, struct2(parse, exec, &ntom, envp),
			&ntom);
		if (parse->iter->flag == PIPE_FLAG &&
			parse->iter->next->flag == PIPE_FLAG)
			parse->iter = parse->iter->next;
		parse->iter = parse->iter->next;
	}
	parse->iter = parse->first;
	exec->iter = exec->first;
	return (exec);
}

