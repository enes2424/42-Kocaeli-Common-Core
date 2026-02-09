/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:52:08 by eates             #+#    #+#             */
/*   Updated: 2024/01/25 16:12:52 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

int	g_sig_control;

enum e_token
{
	NONE,
	PIPE,
	INPUT,
	HEREDOC,
	WRITE,
	REWRITE,
	STD_IN,
	STD_OUT
};

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*value;
	int				token;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_ms
{
	t_cmd	*cmd;
	t_cmd	*main_cmd;
	t_env	*env;
	char	*input;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*name;
	char	*pwd;
	char	*home;
	char	*path;
	char	*convert_str;
	int		**heredocs;
	int		status;
	int		num_of_pipe;
	int		is_prev_token_heredoc;
}	t_ms;

int		ft_free(void **element, int num);
void	free_env(t_env *env, int status);
void	*free_cmd(t_cmd *cmd);
void	free_heredocs(t_ms *ms);
void	frees(t_ms *ms, int status);
void	frees2(char **ev, char **cmd, t_ms *ms);
void	frees3(t_ms *ms);
void	frees4(t_ms *ms);
void	if_error_frees(t_ms *ms, void *elm, int status);
t_env	*create_env(char **ev, int i, int j);
int		edit_env(t_ms *ms, t_env *env, char **ev, int i);
char	**convert_t_env_to_str_array2(t_ms *ms, char **cmd,
			char **ev, int status);
char	**convert_t_env_to_str_array(t_ms *ms, char **cmd, int status);
char	*get_env(t_ms *ms, char *key);
int		add_char_to_str(char **str, char c);
char	**sort(char **ev);
void	write_error(char *str1, char *str2, char *str3);
int		control(char *key, int status);
void	add_env(t_ms *ms, t_env *tmp, char *key, char *value);
void	set_env(t_ms *ms, char *key);
void	delete_env(t_ms *ms, char *str);
void	add_export(t_ms *ms);
void	unset(t_ms *ms);
int		special_expression(t_ms *ms, t_cmd *tmp, char *str, int status);
char	*while_loop(t_ms *ms, char *input, int flag, t_cmd **tmp);
char	*dolar_mark(t_ms *ms, char *input, int flag);
void	edit_end_element(t_cmd *tmp, char *str, int flag);
char	*add_cmd(t_ms *ms, t_cmd **tmp, char *input);
char	*operations_w_q(t_ms *ms, char *input, int *status, t_cmd **tmp);
void	end_edit_cmd(t_ms *ms, int *status, t_cmd *tmp);
void	edit_cmd(t_ms *ms, int *status, char *input, t_cmd *tmp);
int		create_cmd(t_ms *ms, char *input);
char	**llist_cmd_to_cmd(t_ms *ms);
int		pre_create_path(t_ms *ms, char **path);
char	*create_path(t_ms *ms, char *path, int i);
void	export(t_ms *ms);
void	echo(t_ms *ms);
void	sigcontrol(void);
void	ft_signal(int x);
void	ft_exit(t_ms *ms);
void	cd(t_ms *ms);
void	cd_pwd(t_ms *ms);
int		control_cd(t_ms *ms, int ctrl);
void	create_pwd_and_name_and_home(t_ms *ms);
void	init(t_ms *ms, char **ev);
int		redirection(t_ms *ms);
void	ft_control(t_cmd **iter, t_ms *ms);
int		ft_token(t_ms *ms, t_cmd *iter, int *fd);
int		ft_input(t_cmd *iter, int *fd);
void	ft_heredoc(t_ms *ms, int *fd);
void	ft_write(t_cmd *iter, int *fd);
void	ft_rewrite(t_cmd *iter, int *fd);
int		ft_exec_heredoc(t_cmd *tmp, int i, t_ms *ms);
void	env(t_ms *ms);
void	execute(t_ms *ms);

#endif
