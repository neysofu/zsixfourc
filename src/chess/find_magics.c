#include "chess/find_magics.h"
#include "chess/bb.h"
#include "mt-64/mt-64.h"
#include "utils.h"
#include "debug.h"
#include <assert.h>
#include <libpopcnt/libpopcnt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Magic MAGICS[SQUARES_COUNT] = { 0 };

Bitboard
slider_attacks(Square sq, Bitboard occupancy, const short delta[4][2])
{
	Bitboard bb = 0;
	for (int i = 0; i < 4; i++) {
		int df = delta[i][0];
		int dr = delta[i][1];
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

Bitboard
bb_rook(Square sq, Bitboard occupancy)
{
	const short rook_offsets[4][2] = { { -1, 0 }, { 0, -1 }, { 0, 1 }, { 1, 0 } };
	return slider_attacks(sq, occupancy, rook_offsets);
}

Bitboard
bb_sparse_random(void)
{
	return genrand64_int64() & genrand64_int64() & genrand64_int64();
}

Bitboard
bb_premask_rook(Square sq)
{
	Bitboard x = rank_to_bb(square_rank(sq)) & ~file_to_bb(0) & ~file_to_bb(7);
	Bitboard y = file_to_bb(square_file(sq)) & ~rank_to_bb(0) & ~rank_to_bb(7);
	return (x ^ y) & ~square_to_bb(sq);
}

Bitboard
bb_premask_bishop(Square sq)
{
	return (square_a1h8_diagonal(sq) | square_a8h1_diagonal(sq)) & ~0xff818181818181ffull;
}

struct BitboardSubsetIter
{
	Bitboard original;
	Bitboard subset;
};

Bitboard *
bb_subset_iter(struct BitboardSubsetIter *iter)
{
	// https://www.chessprogramming.org/Traversing_Subsets_of_a_Set
	iter->subset = (iter->subset - iter->original) & iter->original;
	if (iter->subset == 0) {
		return NULL;
	} else {
		return &(iter->subset);
	}
}

size_t
find_start_of_attacks_table(Bitboard attacks_table[])
{
	for (size_t i = 0; i < 4096; i++) {
		if (attacks_table[i]) {
			return i;
		}
	}
	return 4095;
}

size_t
find_end_of_attacks_table(Bitboard attacks_table[])
{
	for (size_t i = 4095; i > 0; i--) {
		if (attacks_table[i]) {
			return i;
		}
	}
	return 0;
}

void
magic_find(struct Magic *magic, Square square, Bitboard *attacks_table)
{
	size_t attacks_table_size = sizeof(Bitboard) * 4096;
	magic->premask = bb_premask_rook(square);
	magic->rshift = 64 - popcount64(magic->premask);
	while (true) {
		memset(attacks_table, 0, attacks_table_size);
		magic->multiplier = bb_sparse_random();
		struct BitboardSubsetIter subset_iter = {
			.original = magic->premask,
			.subset = 0,
		};
		bool found_collisions = false;
		Bitboard *subset = NULL;
		while ((subset = bb_subset_iter(&subset_iter))) {
			size_t i = (*subset * magic->multiplier) >> magic->rshift;
			Bitboard *val = attacks_table + i;
			Bitboard attacks = bb_rook(square, *subset);
			if (*val && *val != attacks) {
				found_collisions = true;
				break;
			} else {
				*val = attacks;
			}
		}
		if (!found_collisions) {
			break;
		}
	}
	magic->start = find_start_of_attacks_table(attacks_table);
	magic->end = find_end_of_attacks_table(attacks_table);
}

void
magic_find_bishop(struct Magic *magic, Square square, Bitboard *attacks_table)
{
	size_t attacks_table_size = sizeof(Bitboard) * 4096;
	magic->premask = bb_premask_bishop(square);
	bb_print(magic->premask);
	magic->rshift = 64 - popcount64(magic->premask);
	while (true) {
		memset(attacks_table, 0, attacks_table_size);
		magic->multiplier = bb_sparse_random();
		struct BitboardSubsetIter subset_iter = {
			.original = magic->premask,
			.subset = 0,
		};
		bool found_collisions = false;
		Bitboard *subset = NULL;
		while ((subset = bb_subset_iter(&subset_iter))) {
			size_t i = (*subset * magic->multiplier) >> magic->rshift;
			Bitboard *val = attacks_table + i;
			Bitboard attacks = bb_bishop(square, *subset);
			if (*val && *val != attacks) {
				found_collisions = true;
				break;
			} else {
				*val = attacks;
			}
		}
		if (!found_collisions) {
			debug_printf("finished bishop\n");
			break;
		}
	}
	magic->start = find_start_of_attacks_table(attacks_table);
	magic->end = find_end_of_attacks_table(attacks_table);
}
