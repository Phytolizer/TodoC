#include "ansi_esc.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

char* ansi_esc_cursor_pos(uint32_t x, uint32_t y)
{
	int n = snprintf(NULL, 0, ANSI_ESC_CSI "%" PRIu32 ";%" PRIu32 "H", x, y);
	if (n <= 0)
	{
		return NULL;
	}

	char* result = calloc(n + 1, 1);
	snprintf(result, n + 1, ANSI_ESC_CSI "%" PRIu32 ";%" PRIu32 "H", x, y);
	return result;
}
