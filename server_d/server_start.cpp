#include "mygame.h"

void     server::connection(void)
{
	int						cs;
	struct sockaddr_in		clt;
	unsigned int			len;

	if ((cs = accept(ssock, (struct sockaddr *)&clt, &len)) == -1)
	{
		cout << "Server : error accept client" << endl;
		exit(-1);
	}
	cout << "Client : " << cs << " connected." << endl;
	clients[cs]->set_type(CLT_FD);
	clients[cs]->set_write((char *)"Veuillez entrer un pseudo :");
}

void	server::init_fd(void)
{
	int		i;

	i = 0;
	FD_ZERO(&fd_read);
	FD_ZERO(&fd_write);
	FD_SET(ssock, &fd_read);
	fd_max = ssock + 1;
	while (i < max_fd)
	{
		if (clients[i]->get_type() != FREE_FD)
		{
			FD_SET(i, &fd_read);
			if (clients[i]->is_write() == 1)
				FD_SET(i, &fd_write);
			fd_max = i + 1;
		}
		i++;
	}
}

void	server::send_msg_to_all(int cs, char *msg)
{
	string name;
	char	buf[BC_SIZE];
	int		i;
	int		j;

	i = 0;
	j = 0;
	name = clients[cs]->get_name();
	while (name[i] != '\0')
		buf[j++] = name[i++];
	buf[j++] = ':';
	buf[j++] = ' ';
	i = 0;
	while (msg[i] != '\n')
		buf[j++] = msg[i++];
	i = -1;
	buf[j] = '\0';
	clients[cs]->clear_tmp_read();
	while (++i < max_fd)
	{
		if (clients[i]->get_type() != FREE_FD && i != cs)
			clients[i]->set_write(buf);
	}
}

void	server::name_client(int cs, char *msg)
{
	int		i;

	i = 0;
	while (msg[i] != '\n')
		i++;
	msg[i] = '\0';
	string name(msg);
	clients[cs]->set_name(name);
}

void	server::check_actions(int cs, char *msg)
{
	if (clients[cs]->is_named() == 1)
		send_msg_to_all(cs, msg);
	else
		name_client(cs, msg);
}

void	server::check_fd(void)
{
	int		i;
	char	*msg;

	i = 0;
	if (FD_ISSET(ssock, &fd_read) != 0)
		connection();
	while (i < fd_max)
	{
		if (clients[i]->get_type() != FREE_FD)
		{
			if (FD_ISSET(i, &fd_read) != 0)
			{
				if ((msg = clients[i]->c_receive()) != NULL)
					check_actions(i, msg);
			}
			else if (FD_ISSET(i, &fd_write) != 0)
				clients[i]->c_send();
			if (FD_ISSET(i, &fd_read) != 0 || FD_ISSET(i, &fd_write) != 0)
				r--;
		}
		i++;
	}
}

int		server::run_serv()
{
	int		r;

	init_fd();
	r = select(fd_max, &fd_read, &fd_write, NULL, NULL);
	if (r == -1)
		return (-1);
	check_fd();
	return (1);
}

void	server::stop_serv(void)
{
	cout << "Server Stopped." << endl;
}