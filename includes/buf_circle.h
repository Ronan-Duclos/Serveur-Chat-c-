#ifndef BUF_CIRCLE_H
# define BUF_CIRCLE_H

# include <iostream>
# include <strings.h>

# define BC_SIZE	8192

using namespace std;

class buf_circle
{
	private:
		char	bc_start[BC_SIZE + 1];
		char	*bc_end;
		char	*bc_headr;
		char	*bc_headw;
		int		bc_nbcmd;

	public:
		buf_circle(void);
		~buf_circle(void);
		void	bc_read(char *tmp);
		void	bc_write(char *tmp, int type);
		int		bc_iscmd(void);
		void	bc_display(void);
};

#endif