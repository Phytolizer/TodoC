#include "ansi_esc.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

struct window_size
{
	bool success;
	int rows;
	int cols;
};

struct window_size get_window_size(void)
{
	struct winsize ws;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
	{
		return (struct window_size){.success = false};
	}
	return (struct window_size){.success = true, .rows = ws.ws_row, .cols = ws.ws_col};
}

bool enable_raw_mode(struct termios* orig_termios)
{
	if (tcgetattr(STDIN_FILENO, orig_termios) == -1)
	{
		return false;
	}

	struct termios raw = *orig_termios;
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

void disable_raw_mode(struct termios* orig_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios);
}

int main(void)
{
	struct termios orig_termios;
	if (!enable_raw_mode(&orig_termios))
	{
		return 1;
	}
	struct window_size window_size = get_window_size();
	char* cursor_pos = ansi_esc_cursor_pos(window_size.rows / 2, window_size.cols / 2 - 3);
	printf(ANSI_ESC_KILL_SCREEN "%sHello\r\n", cursor_pos);

	free(cursor_pos);
	disable_raw_mode(&orig_termios);
	return 0;
}
