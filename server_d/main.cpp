#include "mygame.h"

int main()
{
    server     my_serv(4242);

    cout << "Server started." << endl;
    while (my_serv.run_serv() == 1)
        ;
    my_serv.stop_serv();
    return (0);
}
