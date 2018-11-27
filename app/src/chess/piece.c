/**
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "chess/piece.h"
#include <assert.h>
#include <ctype.h>

char
piece_to_char(enum Piece piece)
{
	assert(piece <= PIECE_MAX);
	assert(piece != PIECE_NONE);
	return "pnbrk.q"[piece];
}

enum Piece
char_to_piece(char c)
{
	switch (tolower(c)) {
		case 'p':
			return PIECE_PAWN;
		case 'n':
			return PIECE_KNIGHT;
		case 'b':
			return PIECE_BISHOP;
		case 'r':
			return PIECE_ROOK;
		case 'k':
			return PIECE_KING;
		case 'q':
			return PIECE_QUEEN;
		default:
			return PIECE_NONE;
	}
}