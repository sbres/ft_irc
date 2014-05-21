/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbres <sbres@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/20 10:05:12 by sbres             #+#    #+#             */
/*   Updated: 2014/05/21 10:50:11 by sbres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define COMANDS "/join|/nick|/who|/msg|/join|/quitchanel|/quit|/help"
# include <sys/select.h>
# include <netinet/in.h>

typedef struct			s_user
{
	int					fd;
	char				*username;
	struct s_user		*next;
}						t_user;

typedef struct			s_usercont
{
	t_user				*user;
	struct s_usercont	*next;
}						t_usercont;

typedef struct			s_chat_rooms
{
	char				*name;
	t_user				*users;
}						t_chat_rooms;

typedef struct			s_tosend
{
	int					fd;
	char				*message;
}						t_tosend;

typedef struct			s_env
{
	int					stream_socket;
	struct sockaddr_in	addr;
	struct fd_set		master_in;
	struct fd_set		working_in;
	struct fd_set		master_out;//we might be able to only use one master ?
	struct fd_set		working_out;
	int					fd_max;
	struct timeval		timeout;
	t_user				*users_list;
	t_chat_rooms		*rooms_list;
}						t_env;

void	ft_create_user(t_env *env, int fd);
void	ft_handle_input(t_env *env, int fd);
void	ft_delete_user(t_env *env, int fd);
t_env	*ft_init_server(char *port);
void	hf_join(t_env *env, char *str);

#endif
