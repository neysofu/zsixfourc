#include "engine.h"
#include "agent.h"
#include "cache/cache.h"
#include "chess/position.h"
#include "utils.h"
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void
init_subsystems(void)
{
	init_genrand64(0xd895643full);
	p_libsys_init();
	// UCI (and CECP as well, for that matter) is a line-oriented protocol; so
	// we want to turn line buffering on.
	setvbuf(stdin, NULL, _IOLBF, 0);
	setvbuf(stdout, NULL, _IOLBF, 0);
}

struct Engine *
engine_new(void)
{
	struct Engine *engine = exit_if_null(malloc(sizeof(struct Engine)));
	*engine = (struct Engine){
		.board = POSITION_INIT,
		.time_controls = { NULL, NULL },
		.cache = NULL,
		.agent = agent_new(),
		.seed = 0xcfca130b,
		.output = stdout,
		.debug = false,
		.move_selection_noise = 0.005,
		.contempt = 0.65,
		.selectivity = 0.5,
		.status = STATUS_IDLE,
		.exit_status = EXIT_SUCCESS,
	};
	return engine;
}

struct Engine *
engine_new_tmp(void) {
	struct Engine *engine = engine_new();
	char template[] = "/tmp/fileXXXXXX";
	int fd = mkstemp(template);
	if (fd == -1) {
		puts("bad");
		exit(1);
	}
	engine->output = fdopen(fd, "w+");
	return engine;
}

void
engine_delete(struct Engine *engine)
{
	time_control_delete(engine->time_controls[COLOR_WHITE]);
	time_control_delete(engine->time_controls[COLOR_BLACK]);
	cache_delete(engine->cache);
	agent_delete(engine->agent);
	free(engine);
}

void
engine_debugf(struct Engine *engine,
              const char *filename,
              size_t line_num,
              const char *function_name,
              ...)
{
	assert(engine);
	assert(filename);
	assert(function_name);
	if (!engine->debug) {
		return;
	}
	printf("info string ");
#ifndef NDEBUG
	printf("%s:%zu @ %s -- ", filename, line_num, function_name);
#endif
	va_list args;
	va_start(args, function_name);
	vprintf(va_arg(args, const char *), args);
	va_end(args);
}
