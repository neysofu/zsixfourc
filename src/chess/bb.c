#include "chess/bb.h"
#include "debug.h"
#include "mt-64/mt-64.h"
#include "utils.h"
#include <assert.h>
#include <libpopcnt/libpopcnt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Bitboard
bb_next_subset(Bitboard mask, Bitboard previous_subset)
{
	// https://www.chessprogramming.org/Traversing_Subsets_of_a_Set
	// https://graphics.stanford.edu/~seander/bithacks.html#CountBitsSetKernighan
	return (previous_subset - mask) & mask;
}

Bitboard BB_ATTACKS_BY_KNIGHT[SQUARES_COUNT] = { 0 };
Bitboard BB_ATTACKS_BY_KING[SQUARES_COUNT] = { 0 };

Bitboard
slider_attacks(Square sq, Bitboard occupancy, const short delta[4][2])
{
	Bitboard bb = 0;
	for (int i = 0; i < 4; i++) {
		const int df = delta[i][0];
		const int dr = delta[i][1];
		File file = square_file(sq) + df;
		Rank rank = square_rank(sq) + dr;
		while (file >= 0 && file < 8 && rank >= 0 && rank < 8) {
			bb |= square_to_bb(square_new(file, rank));
			if (square_to_bb(square_new(file, rank)) & occupancy) {
				break;
			}
			rank += dr;
			file += df;
		}
	}
	return bb;
}

// Keep in mind that both knights and kings can move in 8 different directions.
const short OFFSETS_KNIGHT[8][2] = {
	{ -2, -1 }, { -2, 1 }, { 2, -1 }, { 2, 1 }, { -1, -2 }, { -1, 2 }, { 1, -2 }, { 1, 2 },
};

const short OFFSETS_KING[8][2] = {
	{ -1, -1 }, { 0, -1 }, { 1, -1 }, { -1, 0 }, { 1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 },
};

const short OFFSETS_BISHOP[4][2] = { { 1, -1 }, { -1, 1 }, { 1, 1 }, { -1, -1 } };

const short OFFSETS_ROOK[4][2] = { { 1, 0 }, { 0, 1 }, { 0, -1 }, { -1, 0 } };

void
bb_pprint(Bitboard bb)
{
	for (Rank rank = RANK_MAX; rank >= 0; rank--) {
		for (File file = 0; file <= FILE_MAX; file++) {
			putchar(bb & square_to_bb(square_new(file, rank)) ? 'x' : '.');
			putchar(' ');
		}
		puts("");
	}
	puts("");
}

Bitboard
bb_bishop(Square sq, Bitboard occupancy)
{
	return slider_attacks(sq, occupancy, OFFSETS_BISHOP);
}

Bitboard
bb_rook(Square sq, Bitboard occupancy)
{
	return slider_attacks(sq, occupancy, OFFSETS_ROOK);
}

Bitboard
bb_attacks_by_offsets(Square sq, const short offsets[8][2])
{
	Bitboard bb = 0;
	for (size_t i = 0; i < 8; i++) {
		File f = square_file(sq) + offsets[i][0];
		Rank r = square_rank(sq) + offsets[i][1];
		if (r >= 0 && f >= 0 && r <= RANK_MAX && f <= FILE_MAX) {
			bb |= square_to_bb(square_new(f, r));
		}
	}
	return bb;
}

Bitboard
bb_rays_rook(Square sq)
{
	Bitboard x = rank_to_bb(square_rank(sq)) & ~file_to_bb(0) & ~file_to_bb(7);
	Bitboard y = file_to_bb(square_file(sq)) & ~rank_to_bb(0) & ~rank_to_bb(7);
	return x ^ y;
}

void
bb_init(void)
{
	static bool done = false;
	if (done) {
		return;
	}
	done = true;
	for (Square sq = 0; sq <= SQUARE_MAX; sq++) {
		BB_ATTACKS_BY_KNIGHT[sq] = bb_attacks_by_offsets(sq, OFFSETS_KNIGHT);
		BB_ATTACKS_BY_KING[sq] = bb_attacks_by_offsets(sq, OFFSETS_KING);
	}
}
