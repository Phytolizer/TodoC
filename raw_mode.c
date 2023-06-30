#include "raw_mode.h"
#include <termios.h>
#include <unistd.h>

static struct termios raw_mode__orig_termios;

extern bool raw_mode_enable(void)
{
	if (tcgetattr(STDIN_FILENO, &raw_mode__orig_termios) == -1)
	{
		return false;
	}

	struct termios raw = raw_mode__orig_termios;
	raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;

	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		return false;
	}
	return true;
}

extern void raw_mode_disable(void)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_mode__orig_termios);
}
