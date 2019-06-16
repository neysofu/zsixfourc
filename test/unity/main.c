/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "Unity/src/unity.h"

extern void
test_cache_single_key_retrieval(void);
extern void
test_char_to_file(void);
extern void
test_char_to_piece(void);
extern void
test_color(void);
extern void
test_fen_conversion(void);
extern void
test_fen_init(void);
extern void
test_file_to_char(void);
extern void
test_jsonrpc_compliance(void);
extern void
test_piece_to_char(void);

int
main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_cache_single_key_retrieval);
	RUN_TEST(test_char_to_file);
	RUN_TEST(test_char_to_piece);
	RUN_TEST(test_color);
	RUN_TEST(test_fen_conversion);
	RUN_TEST(test_fen_init);
	RUN_TEST(test_file_to_char);
	RUN_TEST(test_jsonrpc_compliance);
	RUN_TEST(test_piece_to_char);
	return UNITY_END();
}