#include "overlay.h"
#include <raylib.h>
#include "logging.h"
#include <math.h>

static int sw, sh;

void overlay_init(int screen_width, int screen_height) {
    sw = screen_width;
    sh = screen_height;
    
    InitWindow(sw, sh, "AR Overlay - Ground Station");

    SetTargetFPS(60);
    LOG_INFO("Window initialized: %dx%d", sw, sh);
}

void overlay_draw(const PosePacket *pose) {
    BeginDrawing();
    ClearBackground(BLACK);

    float center_x = sw / 2.0f;
    float center_y = sh / 2.0f;
    float len = 150.0f; // Length of the heading line
    float rad = pose->heading * DEG2RAD; // Convert heading to radians
    float end_x = center_x + len * sinf(rad);
    float end_y = center_y - len * cosf(rad);

    DrawCircle(center_x, center_y, 8, YELLOW); // Draw center point
    DrawLineEx((Vector2){center_x, center_y}, (Vector2){end_x, end_y}, 3.0f, GREEN); // Draw heading line

    DrawText(TextFormat("Heading: %.1f°", pose->heading), 10, 10, 20, WHITE); // Display heading
    DrawText(TextFormat("Lat: %.6f  Lon: %.6f", pose->lat, pose->lon), 10, 35, 20, WHITE); // Display latitude and longitude
    DrawFPS(sw - 80, 10); // Display FPS in top-right corner

    EndDrawing();
}

void overlay_close(void) {
    CloseWindow();
    LOG_INFO("Window closed");
}