#include "chess/fen.h"
#include "engine.h"
#include "munit/munit.h"
#include "protocols/uci.h"
#include "test/utils.h"
#include "utils.h"

void
test_engine_call_uci_empty(struct Engine *engine)
{
	engine_call_uci(engine, "   ");
	engine_call_uci(engine, "");
	engine_call_uci(engine, "\n \t ");
	{
		struct Lines *lines = file_line_by_line(engine->config.output);
		munit_assert_uint(lines_count(lines), ==, 0);
	}
}

void
test_engine_call_uci_cmd_d(struct Engine *engine)
{
	engine_call_uci(engine, "d lichess");
	engine_call_uci(engine, "d");
	{
		struct Lines *lines = file_line_by_line(engine->config.output);
		size_t n_lines = lines_count(lines);
		char *fen = exit_if_null(malloc(FEN_SIZE));
		fen_from_position(fen, &POSITION_INIT, ' ');
		munit_assert_uint(n_lines, >, FILES_COUNT);
		munit_assert_not_null(strstr(lines_nth(lines, 0), "lichess.org"));
		bool fen_was_found = false;
		for (size_t i = 1; i < n_lines; i++) {
			fen_was_found = fen_was_found || strstr(lines_nth(lines, i), fen);
		}
		munit_assert_true(fen_was_found);
		free(fen);
	}
}

void
test_engine_call_uci_cmd_go_perft(struct Engine *engine)
{
	engine_call_uci(engine, "go perft");
	{
		struct Lines *lines = file_line_by_line(engine->config.output);
		munit_assert_not_null(strstr(lines_nth(lines, 0), "ERROR"));
		lines_delete(lines);
	}
}

void
test_engine_call_uci_cmd_isready(struct Engine *engine)
{
	engine_call_uci(engine, "isready");
	{
		struct Lines *lines = file_line_by_line(engine->config.output);
		munit_assert_uint(lines_count(lines), ==, 1);
		munit_assert_string_equal(lines_nth(lines, 0), "readyok");
		lines_delete(lines);
	}
}

void
test_engine_call_uci_cmd_position(struct Engine *engine)
{
	const Square e4 = square_new(char_to_file('e'), char_to_rank('4'));
	{
		struct Piece piece_at_e4 = position_piece_at_square(&engine->board, e4);
		munit_assert_uint(piece_at_e4.type, !=, PIECE_TYPE_PAWN);
	}
	engine_call_uci(engine, "position current moves e2e4");
	{
		struct Piece piece_at_e4 = position_piece_at_square(&engine->board, e4);
		munit_assert_uint(piece_at_e4.type, ==, PIECE_TYPE_PAWN);
		struct Lines *lines = file_line_by_line(engine->config.output);
		munit_assert_uint(lines_count(lines), ==, 0);
		lines_delete(lines);
	}
	engine_call_uci(engine, "position startpos");
	{
		struct Piece piece_at_e4 = position_piece_at_square(&engine->board, e4);
		munit_assert_uint(piece_at_e4.type, ==, PIECE_TYPE_NONE);
		struct Lines *lines = file_line_by_line(engine->config.output);
		munit_assert_uint(lines_count(lines), ==, 0);
		lines_delete(lines);
	}
}

void
test_engine_call_uci_cmd_quit(struct Engine *engine)
{
	{
		munit_assert_uint(engine->status, !=, STATUS_EXIT);
	}
	engine_call_uci(engine, "quit");
	{
		munit_assert_uint(engine->status, ==, STATUS_EXIT);
	}
}

void
test_engine_call_uci_cmd_uci(struct Engine *engine)
{
	engine_call_uci(engine, "uci");
	{
		struct Lines *lines = file_line_by_line(engine->config.output);
		for (size_t i = 0; i < lines_count(lines) - 1; i++) {
			char *first_token = strtok_whitespace(lines_nth(lines, i));
			munit_assert_true(strcmp(first_token, "id") == 0 ||
			                  strcmp(first_token, "option") == 0);
		}
		munit_assert_string_equal(lines_nth(lines, -1), "uciok");
		lines_delete(lines);
	}
}

void
test_engine_call_uci_cmd_debug(struct Engine *engine)
{
	{
		ENGINE_LOGF(engine, "VALENTINA\n");
		struct Lines *lines = file_line_by_line(engine->config.output);
		munit_assert_uint(lines_count(lines), ==, 0);
		lines_delete(lines);
	}
	engine_call_uci(engine, "debug on");
	{
		ENGINE_LOGF(engine, "VALERIA\n");
		struct Lines *lines = file_line_by_line(engine->config.output);
		munit_assert_uint(lines_count(lines), >, 0);
		lines_delete(lines);
	}
}

void
test_engine_call_uci_unknown_cmd(struct Engine *engine)
{
	engine_call_uci(engine, "foobar");
	{
		struct Lines *lines = file_line_by_line(engine->config.output);
		munit_assert_uint(lines_count(lines), ==, 1);
		munit_assert_not_null(strstr(lines_nth(lines, 0), "ERROR"));
		lines_delete(lines);
	}
}
