#include "ansi_esc.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void ansi_esc_cursor_pos(uint32_t x, uint32_t y)
{
	fprintf(stderr, ANSI_ESC_CSI "%" PRIu32 ";%" PRIu32 "H", x + 1, y + 1);
}
