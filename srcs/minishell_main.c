/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 20:20:54 by acarle-m          #+#    #+#             */
/*   Updated: 2022/07/24 04:19:06 by acarle-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	g_status;

static t_builtin	*init_built2(t_builtin *built)
{
	built->iter->name = ft_strdup("export");
	built->iter->fun = builtin_export;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("env");
	built->iter->fun = built_in_env;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("pwd");
	built->iter->fun = built_in_pwd;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("unset");
	built->iter->fun = builtin_unset;
	built->iter->next = NULL;
	built->iter = built->first;
	return (built);
}

static t_builtin	*init_builtin(void)
{
	t_builtin	*built;

	built = malloc(sizeof(t_builtin));
	built->first = malloc(sizeof(t_btin));
	built->iter = built->first;
	built->iter->name = ft_strdup("cd");
	built->iter->fun = builtin_cd;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("exit");
	built->iter->fun = exit_builtin;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	built->iter->name = ft_strdup("echo");
	built->iter->fun = builtin_echo;
	built->iter->next = malloc(sizeof(t_btin));
	built->iter = built->iter->next;
	return (init_built2(built));
}

static t_instance	*init_minishell(char **envp, int ac, char **av)
{
	t_instance	*instance;

	(void)ac;
	(void)av;
	signal(SIGINT, sig_int_handler);
	signal(SIGQUIT, SIG_IGN);
	instance = malloc(sizeof(t_instance));
	if (!instance)
		return (NULL);
	instance->builtin = init_builtin();
	instance->envp = init_envp(envp);
	addshlv(instance);
	return (instance);
}

static int	if_line(t_instance *instance)
{
	t_control_parse	*parse;
	t_control_exec	*exec;
	int				nb_pipe;

	nb_pipe = 0;
	add_history(instance->line);
	parse = parsing(instance->line, instance->envp);
	if (control_parse(parse) == -1)
		return (-1);
	parse->iter = parse->first;
	nb_pipe = pipe_counter(parse);
	exec = structy(parse, nb_pipe, instance->envp);
	parse->iter = parse->first;
	cleaner(parse);
	if (!exec)
		return (-1);
	chose_exec(exec, instance);
	exec_cleaner(exec);
	instance->builtin->iter = instance->builtin->first;
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_instance	*instance;

	instance = init_minishell(envp, ac, av);
	if (!instance)
		return (-1);
	while (1)
	{
		instance->line = readline("minishell $>");
		if (!instance->line)
			break ;
		else if (instance->line[0] != 0)
			if_line(instance);
	}
	write(1, "\n", 1);
	rl_clear_history();
	return (free_instance(instance, 0));
}
