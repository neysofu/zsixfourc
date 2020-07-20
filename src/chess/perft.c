#include "chess/movegen.h"
#include "chess/bb.h"
#include "chess/color.h"
#include "chess/fen.h"
#include "chess/position.h"
#include "globals.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>

size_t
position_perft(FILE *stream, struct Board *pos, size_t depth)
{
	if (depth == 0) {
		fputs("1\n", stream);
		return 1;
	} else if (depth > MAX_DEPTH) {
		fprintf(stream, "<depth limit exceeded>\n");
		return 0;
	}
	struct Move *moves = exit_if_null(malloc(sizeof(struct Move) * MAX_MOVES));
	size_t root_moves_count = gen_legal_moves(moves, pos);
	size_t result = 0;
	for (size_t i = 0; i < root_moves_count; i++) {
		struct Board board = *pos;
		position_do_move_and_flip(&board, moves + i);
		size_t children_count = position_improved_perft(&board, depth - 1);
		result += children_count;
		char mv_as_str[MOVE_STRING_MAX_LENGTH] = { '\0' };
		move_to_string(moves[i], mv_as_str);
		fprintf(stream, "%s: %zu\n", mv_as_str, children_count);
	}
	fprintf(stream, "\nNodes searched: %zu\n\n", result);
	// FIXME
	// free(moves);
	return result;
}

struct SearchStack
{
	struct SearchStackPlie *plies;
	int desired_depth;
	int current_depth;
	struct Board board;
};

struct SearchStackPlie
{
	struct Move generator;
	struct Move *moves;
	int children_count;
	int child_i;
};

void
search_stack_plie_init(struct SearchStackPlie *plie)
{
	plie->children_count = 0;
	plie->child_i = 0;
	plie->moves = exit_if_null(malloc(220 * sizeof(struct Move)));
}

struct SearchStack
search_stack_new(size_t depth)
{
	struct SearchStack stack;
	stack.plies = exit_if_null(malloc((depth + 3) * sizeof(struct SearchStackPlie)));
	stack.desired_depth = depth;
	stack.current_depth = 0;
	for (int i = 0; i < (int)(depth + 3); i++) {
		search_stack_plie_init(stack.plies + i);
	}
	return stack;
}

struct SearchStackPlie *
search_stack_last(struct SearchStack *stack)
{
	return stack->plies + stack->current_depth;
}

void
search_stack_delete(struct SearchStack *stack)
{
	for (int i = 0; i < stack->desired_depth; i++) {
		free(stack->plies[i].moves);
	}
	free(stack->plies);
}

void
search_stack_pop(struct SearchStack *stack)
{
	struct SearchStackPlie *last_plie = search_stack_last(stack);
	stack->current_depth--;
	position_undo_move_and_flip(&stack->board, &last_plie->generator);
}

void
search_stack_push(struct SearchStack *stack)
{
	struct SearchStackPlie *last_plie = search_stack_last(stack);
	struct Move generator = last_plie->moves[last_plie->child_i++];
	stack->current_depth++;
	position_do_move_and_flip(&stack->board, last_plie->moves);
	last_plie = search_stack_last(stack);
	size_t moves_count = gen_legal_moves(last_plie->moves, &stack->board);
	last_plie->generator = generator;
	last_plie->children_count = moves_count;
	last_plie->child_i = 0;
}

size_t
position_improved_perft(struct Board *pos, int depth)
{
	if (depth == 0) {
		return 1;
	}
	depth--;
	size_t nodes_count = 0;
	struct SearchStack stack = search_stack_new(depth);
	stack.board = *pos;
	stack.plies[0].generator = MOVE_IDENTITY;
	stack.plies[0].children_count = gen_legal_moves(stack.plies[0].moves, pos);
	while (true) {
		struct SearchStackPlie *last_plie = search_stack_last(&stack);
		if (last_plie->child_i == last_plie->children_count) {
			if (stack.current_depth == 0) {
				break;
			} else {
				search_stack_pop(&stack);
			}
		} else if (stack.current_depth == stack.desired_depth) {
			last_plie->child_i++;
			nodes_count++;
		} else {
			search_stack_push(&stack);
		}
	}
	return nodes_count;
}
