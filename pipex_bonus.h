/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:32:15 by eates             #+#    #+#             */
/*   Updated: 2023/10/20 17:15:27 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>

char	**ft_split(char const *s, char c);
void	free_double_array(void **tab);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		control;
	pid_t	*pid;
	int		**pipefd;
	int		pipefd_limiter[2];
	char	**str;
	int		filefd1;
	int		filefd2;
	char	**cmd_paths;
	char	*cmd;
}	t_pipex;

void	has_error_of_pid(t_pipex *pipex, pid_t pid);
void	finish(t_pipex *pipex, int status);
void	has_error_of_arg(t_pipex *pipex);
void	dup_input(t_pipex *pipex);
void	here_doc_operation(t_pipex *pipex, char *input);
void	create_path(t_pipex *pipex);
void	child1(t_pipex *pipex);
void	child2(t_pipex *pipex);
void	child(t_pipex *pipex, int index);
#endif
