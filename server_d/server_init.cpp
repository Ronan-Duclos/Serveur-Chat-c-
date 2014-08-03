#include "mygame.h"

void    server::init_srv(int port)
{
	struct sockaddr_in		sockserver;

    sockserver.sin_family = AF_INET;
	sockserver.sin_port = htons(port);
	sockserver.sin_addr.s_addr = INADDR_ANY;
	bzero(&(sockserver.sin_zero),8);
	if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
		cerr << "Serveur : error creation socket()" << endl;
		exit(-1);
	}
	if(bind(ssock,(struct sockaddr*)&sockserver,sizeof(struct sockaddr)) == -1)
	{
		cerr << "Serveur : error bind()" << endl;
		exit(-1);
	}
	if(listen(ssock, 42) == -1)
	{
		cerr << "Serveur : error listen()" << endl;
		exit(-1);
	}
}

void	server::init_clt(void)
{
	int 			i;

	i = 0;
	if ((clients = (client **)malloc(sizeof(client *) * max_fd)) == NULL)
	{
		cerr << "Server : error malloc clients" << endl;
		exit(-1);
	}
	while (i < max_fd)
	{
		clients[i] = new client(i);
		clients[i]->set_type(FREE_FD);
		i++;
	}
}

server::server(int port)
{
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) == -1)
	{
		cerr << "Serveur : error getrlimit()" << endl;
		exit(-1);
	}
	max_fd = rlp.rlim_cur;
	init_srv(port);
	init_clt();
}

server::~server(void)
{
	int		i;

	i = 0;
	while (i < max_fd)
	{
		delete(clients[i]);
		i++;
	}
	free(clients);
	close(ssock);
}
