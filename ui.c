#include "ui.h"
#include "ansi_esc.h"
#include <stdio.h>
#include <stdlib.h>

const struct AttrPair highlight_pair = {
    .on = ANSI_ESC_FG_BLACK ANSI_ESC_BG_WHITE,
    .off = ANSI_ESC_RESET,
};

const struct AttrPair regular_pair = {
    .on = "",
    .off = "",
};

extern void UiBegin(struct Ui* ui, size_t row, size_t col)
{
	ui->row = row;
	ui->col = col;
}

extern void UiBeginList(struct Ui* ui, Id id)
{
	if (ui->in_list)
	{
		fputs("nested lists are not allowed\r\n", stderr);
		abort();
	}
	ui->in_list = true;
	ui->list_curr = id;
}

extern void UiListElement(struct Ui* ui, const char* text, Id id)
{
	if (!ui->in_list)
	{
		fputs("ListElement called from outside of a list\r\n", stderr);
		abort();
	}

	UiLabel(ui, text, id == ui->list_curr ? highlight_pair : regular_pair);
}

extern void UiLabel(struct Ui* ui, const char* text, struct AttrPair pair)
{
	ansi_esc_cursor_pos((uint32_t)ui->row, (uint32_t)ui->col);
	fputs(pair.on, stderr);
	fputs(text, stderr);
	fputs(pair.off, stderr);
	ui->row += 1;
}

extern void UiEndList(struct Ui* ui)
{
	ui->in_list = false;
}

extern void UiEnd(struct Ui* ui)
{
	(void)ui;
}
