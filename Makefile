# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acarle-m <acarle-m@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 18:00:59 by cben-bar          #+#    #+#              #
#    Updated: 2022/07/24 04:44:43 by acarle-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCSDIR		=	./srcs/

SRCS 		=	$(SRCSDIR)parse_to_exec/struct.c\
				$(SRCSDIR)parsing/check_consec_pipe.c\
				$(SRCSDIR)parsing/check_empty_line.c\
				$(SRCSDIR)parsing/check_first_pipe.c\
				$(SRCSDIR)parsing/check_last_chev.c\
				$(SRCSDIR)parsing/check_last_pipe.c\
				$(SRCSDIR)parsing/check_multi_chev.c\
				$(SRCSDIR)parsing/check_multi_node_chev.c\
				$(SRCSDIR)parsing/check_no_file_name.c\
				$(SRCSDIR)parsing/check_quote.c\
				$(SRCSDIR)parsing/cleaner.c\
				$(SRCSDIR)parsing/cut_redir.c\
				$(SRCSDIR)parsing/dispatch_var.c\
				$(SRCSDIR)parsing/dollar.c\
				$(SRCSDIR)parsing/dollar2.c\
				$(SRCSDIR)parsing/dollar3.c\
				$(SRCSDIR)parsing/fill_var.c\
				$(SRCSDIR)parsing/first_check.c\
				$(SRCSDIR)parsing/flaggeur_file_name.c\
				$(SRCSDIR)parsing/flaggeur_redir.c\
				$(SRCSDIR)parsing/ident_cmd.c\
				$(SRCSDIR)parsing/parse.c\
				$(SRCSDIR)parsing/parsing.c\
				$(SRCSDIR)parsing/parsing_printer.c\
				$(SRCSDIR)parsing/printer_error.c\
				$(SRCSDIR)parsing/quote_supp.c\
				$(SRCSDIR)parsing/re_flaggeur.c\
				$(SRCSDIR)parsing/set_pars.c\
				$(SRCSDIR)parsing/set_var.c\
				$(SRCSDIR)parsing/split_block.c\
				$(SRCSDIR)parsing/supp_empty_node.c\
				$(SRCSDIR)parsing/tote.c\
				$(SRCSDIR)parsing/universal_flaggeur.c\
				$(SRCSDIR)exec/exec.c\
				$(SRCSDIR)exec/execcmd.c\
				$(SRCSDIR)exec/redirection.c\
				$(SRCSDIR)utils/add_back.c\
				$(SRCSDIR)utils/exec_add_back.c\
				$(SRCSDIR)utils/exec_last.c\
				$(SRCSDIR)utils/exec_split.c\
				$(SRCSDIR)utils/ft_itoa.c\
				$(SRCSDIR)utils/ft_split_it.c\
				$(SRCSDIR)utils/ft_strcmp.c\
				$(SRCSDIR)utils/ft_strcpy.c\
				$(SRCSDIR)utils/ft_strdup.c\
				$(SRCSDIR)utils/ft_strjoin.c\
				$(SRCSDIR)utils/ft_strlen.c\
				$(SRCSDIR)utils/ft_utils.c\
				$(SRCSDIR)utils/init.c\
				$(SRCSDIR)utils/init_exec.c\
				$(SRCSDIR)utils/lst_last.c\
				$(SRCSDIR)utils/lst_size.c\
				$(SRCSDIR)utils/signal.c\
				$(SRCSDIR)utils/utils2.c\
				$(SRCSDIR)utils/utils.c\
				$(SRCSDIR)utils/free_memory.c\
				$(SRCSDIR)utils/get_path.c\
				$(SRCSDIR)utils/ft_atoi.c\
				$(SRCSDIR)minishell_main.c\
				$(SRCSDIR)builtin/cd.c\
				$(SRCSDIR)builtin/echo.c\
				$(SRCSDIR)builtin/env.c\
				$(SRCSDIR)builtin/envp_utils.c\
				$(SRCSDIR)builtin/exit.c\
				$(SRCSDIR)builtin/export.c\
				$(SRCSDIR)builtin/pwd.c\
				$(SRCSDIR)builtin/unset.c\


OBJS 		=	${SRCS:.c=.o}

HEADER		=	-I includes -I ~/.brew/opt/readline/include

CC 			=	gcc

CFLAGS 		=	-Wall -Wextra -Werror

LIBS		=	-L ~/.brew/opt/readline/lib -lreadline

OBJSDIR		=	./objs/

DEPS		=	./includes/minishell.h

OBJS		=	$(SRCS:$(SRCSDIR)%.c=$(OBJSDIR)%.o)

all			: 	${NAME}

${NAME}		:	${OBJS} ${DEPS} Makefile
			@$(CC) $(OBJS) ${CFLAGS} $(HEADER) -o $(NAME) $(LIBS) -g3 -fsanitize=address

$(OBJS)		:	$(OBJSDIR)%.o	:	$(SRCSDIR)%.c ${DEPS} Makefile
			@mkdir -p $(OBJSDIR)
			@mkdir -p $(OBJSDIR)builtin
			@mkdir -p $(OBJSDIR)exec
			@mkdir -p $(OBJSDIR)parse_to_exec
			@mkdir -p $(OBJSDIR)parsing
			@mkdir -p $(OBJSDIR)utils
			@${CC} ${CFLAGS} ${HEADER} -c $< -o $@

clean		:
			@rm -rf ${OBJSDIR}

fclean		: 	clean
			@rm ${NAME}

re			:	fclean all

.PHONY		:	all clean fclean re
