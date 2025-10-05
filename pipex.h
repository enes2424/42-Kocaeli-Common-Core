/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eates <eates@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:32:15 by eates             #+#    #+#             */
/*   Updated: 2023/10/07 16:45:06 by eates            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>

char	**ft_split(char const *s, char c);
void	free_string_array(char **tab);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	has_error_of_arg(int argc, char **argv);
void	has_error_of_pid(pid_t pid, char **str);

typedef struct s_pipex
{
	pid_t	pid1;
	pid_t	pid2;
	char	**cmd;
	int		filefd1;
	int		filefd2;
	char	**cmd_paths;
	char	*path;
}	t_pipex;

void	finish(t_pipex *pipex);
void	child1(t_pipex pipex, int *pipefd, char **argv, char **envp);
void	child2(t_pipex pipex, int *pipefd, char **argv, char **envp);

#endif
