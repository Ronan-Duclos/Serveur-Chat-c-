#ifndef MYGAME_H_INCLUDED
# define MYGAME_H_INCLUDED

# include <iostream>
# include <cstdlib>
# include <unistd.h>
# include <strings.h>
# include <cstring>
# include <sys/types.h>//pour les sockets
# include <sys/socket.h>//pour les sockets
# include <netinet/in.h>//pour les sockets
# include <arpa/inet.h>//pour les sockets
# include "buf_circle.h"

enum types {SRV_FD, CLT_FD, FREE_FD};

using namespace std;

class client
{

    private:
    	int			sock;
        int     	type;
        int			named;
        string  	name;
        buf_circle	b_read;
        buf_circle	b_write;
        char		tmp_read[BC_SIZE + 1];
		char		tmp_write[BC_SIZE + 1];

    public:
        client(int me);
        ~client(void);
        void		c_send(void);
        int			is_write(void);
		char		*c_receive(void);
		void		clear_tmp_read(void);
		void		set_name(string me);
		std::string	get_name(void);
		int			is_named(void);
		void		set_type(int me);
		int			get_type(void);
		void		set_write(char *tmp);
		char		*get_read(void);
};

class server
{

	private:
		int                 ssock;
		fd_set              fd_read;
		fd_set              fd_write;
        int                 max_fd; //maximum fd available
        int					fd_max; //maximum fd set
        int					r;
		client				**clients;
		struct sockaddr_in  sockserver;

	public:
		server(int);
		~server(void);
		int		run_serv(void);
		void    connection(void);
		void	init_fd(void);
		void	check_actions(int cs, char *msg);
		void	name_client(int cs, char *msg);
		void	send_msg_to_all(int cs, char *msg);
		void	check_fd(void);
		void	init_clt(void);
		void    init_srv(int port);
		void	stop_serv(void);
		int     disconnection(void);
};

#endif // MYGAME_H_INCLUDED
