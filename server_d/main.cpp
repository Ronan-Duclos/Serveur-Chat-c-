#include "mygame.h"

int 	main()
{
	int		port;

	cout << "Veuillez entrer un port entre 1024 et 49151 : " << endl;
	cin >> port;
	if (port < 1024 || port > 49151)
	{
		cerr << "Server : error wrong port." << endl;
		exit (0);
	}
    server my_serv(port);
    cout << "Server started." << endl;
    while (my_serv.run_serv() == 1)
        ;
    my_serv.stop_serv();
    return (0);
}
