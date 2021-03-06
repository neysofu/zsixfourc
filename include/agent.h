/* SPDX-License-Identifier: GPL-3.0-only */

#ifndef ZULOID_AGENT_H
#define ZULOID_AGENT_H

struct Agent;

struct Agent *
agent_new(void);

void
agent_delete(struct Agent *agent);

#endif
