#pragma once
#include "protocol.h"

void overlay_init(int screen_width, int screen_height);
void overlay_draw(const PosePacket *pose);
void overlay_close(void);
