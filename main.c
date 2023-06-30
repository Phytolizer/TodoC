#include "ansi_esc.h"
#include "raw_mode.h"
#include "ui.h"
#include <stb_ds.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int main(void)
{
	if (!raw_mode_enable())
	{
		return 1;
	}
	atexit(&raw_mode_disable);

	fputs(ANSI_ESC_CURSOR_HIDE, stderr);

	const char* const todos[] = {
	    "Write the todo app",
	    "Buy bread",
	    "Make a cup of tea",
	};
	size_t todo_curr = 0;
	const char* const dones[] = {
	    "Start the stream",
	    "Have breakfast",
	    "Make a cup of tea",
	};
	size_t done_curr = 0;

	struct Ui ui = {0};
	bool quit = false;
	while (!quit)
	{
		fputs(ANSI_ESC_KILL_SCREEN, stderr);
		UiBegin(&ui, 0, 0);
		UiLabel(&ui, "TODO:", regular_pair);
		UiBeginList(&ui, todo_curr);
		for (size_t i = 0; i < sizeof(todos) / sizeof(*todos); ++i)
		{
			char buff[256];
			snprintf(buff, sizeof(buff), "- [ ] %s", todos[i]);
			UiListElement(&ui, buff, i);
		}
		UiEndList(&ui);

		UiLabel(&ui, "DONE:", regular_pair);
		UiBeginList(&ui, done_curr);
		for (size_t i = 0; i < sizeof(dones) / sizeof(*dones); ++i)
		{
			char buff[256];
			snprintf(buff, sizeof(buff), "- [ ] %s", dones[i]);
			UiListElement(&ui, buff, i);
		}
		UiEndList(&ui);
		UiEnd(&ui);

		fflush(stderr);

		int c;
		while (read(STDIN_FILENO, &c, 1) > 0)
		{
			switch (c)
			{
			case 'q':
				quit = true;
				break;
			case 'w':
				if (todo_curr > 0)
				{
					todo_curr -= 1;
				}
				break;
			case 's':
				if (todo_curr + 1 < sizeof(todos) / sizeof(*todos))
				{
					todo_curr += 1;
				}
				break;
			default:
				break;
			}
		}
	}

	fputs(ANSI_ESC_KILL_SCREEN, stderr);
	ansi_esc_cursor_pos(0, 0);
	fputs(ANSI_ESC_CURSOR_SHOW, stderr);
	fflush(stderr);
	return 0;
}
