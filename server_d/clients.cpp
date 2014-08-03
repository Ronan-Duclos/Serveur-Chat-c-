#include "mygame.h"

int		client::is_write(void)
{
	if (b_write.bc_iscmd() == 1)
		return (1);
	return (0);
}

void	client::c_send(void)
{
	int		i;

	b_write.bc_read(tmp_write);
	i = strlen(tmp_write);
	send(sock, tmp_write, i, 0);
	bzero(tmp_write, i + 1);
}

char	*client::c_receive(void)
{
	int		r;

	r = recv(sock, tmp_read, BC_SIZE, 0);
	if (r <= 0)
	{
		type = FREE_FD;
		cout << "Client : " << sock << " disconnected." << endl; 
		name = "";
		close(sock);
	}
	else
	{
		b_read.bc_write(tmp_read, 0);
		bzero(tmp_read, BC_SIZE + 1);
		if (b_read.bc_iscmd() == 1)
		{
			b_read.bc_read(tmp_read);
			return (tmp_read);
		}
	}
	return (NULL);
}

void		client::clear_tmp_read(void)
{
	bzero(tmp_read, BC_SIZE + 1);
}

void		client::set_name(string me)
{
	name = me;
}

std::string	client::get_name(void)
{
	return (name);
}

int			client::is_named(void)
{
	if (name == "")
		return (0);
	return (1);
}

void		client::set_type(int me)
{
	type = me;
}

int			client::get_type(void)
{
	return (type);
}

void		client::set_write(char *tmp)
{
	b_write.bc_write(tmp, 1);
}

char		*client::get_read(void)
{
	b_read.bc_read(tmp_read);
	return (tmp_read);
}
