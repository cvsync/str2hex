/*-
 * Copyright (c) 2014 MAEKAWA Masahide @ M-Systems, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>

int
main(void)
{
	uint8_t u8, tmp;
	int isHigh, pos, ch;

	u8 = 0x00;
	isHigh = 1;
	pos = 0;

	for (;;) {
		ch = fgetc(stdin);
		if ((ch == '\n') || (ch == EOF))
			break;
		if (isspace(ch) || (ch == ':'))
			continue;
		if (!isxdigit(ch))
			exit(EXIT_FAILURE);
		if (isdigit(ch))
			tmp = (uint8_t)(ch - '0');
		else
			tmp = (uint8_t)(tolower(ch) - 'a' + 10);
		if (isHigh) {
			u8 = (uint8_t)(tmp << 4);
			isHigh = 0;
		} else {
			u8 |= tmp;
			(void)printf("0x%02x,", u8);
			pos++;
			if (pos < 8) {
				(void)putchar(' ');
			} else {
				(void)putchar('\n');
				pos = 0;
			}
			isHigh = 1;
		}
	}
	if (pos != 0)
		(void)putchar('\n');

	exit(EXIT_SUCCESS);
}
