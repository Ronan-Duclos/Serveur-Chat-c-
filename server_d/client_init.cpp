#include "mygame.h"

client::client(int me)
{
	sock = me;
	bzero(tmp_read, BC_SIZE + 1);
	bzero(tmp_write, BC_SIZE + 1);
}

client::~client()
{
	bzero(tmp_read, BC_SIZE + 1);
	bzero(tmp_write, BC_SIZE + 1);
}