#pragma once
#include "protocol.h"
#include <stdbool.h>

bool gps_fake_init(const char *replay_file);
bool gps_fake_next(PosePacket *out);
void gps_fake_close(void);
