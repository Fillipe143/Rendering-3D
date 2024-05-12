#include <cmath>
#include <raylib.h>

const int screen_width = 960;
const int screen_height = 720;

const int target_fps = 60;
const int log_level = LOG_WARNING;

void setup();
void loop();

int main() {
    SetTraceLogLevel(log_level);
    InitWindow(screen_width, screen_height, "Sphere");
    SetTargetFPS(target_fps);

    setup();
    while (!WindowShouldClose()) loop();
    CloseWindow();

    return 0;
}

void setup() {
}

float map(float x, float min_x, float max_x, float min_y, float max_y) {
    return ((x - min_x) * (max_y - min_y) / (max_x - min_x)) + min_y;
}

Vector2 projection(Vector3 vertex) {
    return { vertex.x, vertex.y };
}

Vector3 rotate_x(Vector3 vertex, float angle) {
    return {
        .x = vertex.x,
        .y = vertex.y * cosf(angle) - vertex.z * sinf(angle),
        .z = vertex.y * sinf(angle) + vertex.z * cosf(angle)
    };
}

Vector3 rotate_y(Vector3 vertex, float angle) {
    return {
        .x = vertex.x * cosf(angle) + vertex.z * sinf(angle),
        .y = vertex.y,
        .z = vertex.z * cosf(angle) - vertex.x * sinf(angle)
    };
}

Vector3 rotate_z(Vector3 vertex, float angle) {
    return {
        .x = vertex.x * cosf(angle) - vertex.y * sinf(angle),
        .y = vertex.x * sinf(angle) + vertex.y * cosf(angle),
        .z = vertex.z
    };
}
void draw_sphere(Vector3 position, float radius, Vector3 angle, Color color, int resolution = 100) {
    for (int i = 0; i < resolution; i++) {

        float lat = map(i, 0, resolution, 0, M_PI);
        for (int j = 0; j < resolution; j++) {
            float lon = map(j, 0, resolution, 0, 2 * M_PIf);

            Vector3 vertex = {
                radius * sinf(lat) * cosf(lon),
                radius * sinf(lat) * sinf(lon),
                radius * cosf(lat)
            };

            vertex = rotate_x(vertex, angle.x);
            vertex = rotate_y(vertex, angle.y);
            vertex = rotate_z(vertex, angle.z);

            vertex.x += position.x;
            vertex.y += position.y;
            vertex.z += position.z;

            Vector2 n_vertex = projection(vertex);
            DrawCircle(n_vertex.x, n_vertex.y, 1, color);
        }
    }
}

Vector3 angles[3];
int hue = 0;
void loop() {
    BeginDrawing();
    ClearBackground(BLACK);

    draw_sphere({ screen_width / 2.0f, screen_height / 2.0f - 100, 0 }, 100, angles[0], ColorFromHSV(hue, 1, 1), 30);
    draw_sphere({ screen_width / 2.0f - 110, screen_height / 2.0f + 100, 0 }, 100, angles[1], ColorFromHSV(360 - hue, 1, 1), 30);
    draw_sphere({ screen_width / 2.0f + 110, screen_height / 2.0f + 100, 0 }, 100, angles[2], ColorFromHSV((hue + 180) % 360, 1, 1), 30);

    angles[0].x = fmodf(angles[0].x + 0.01, 2 * M_PIf);

    angles[1].x = fmodf(angles[1].x + 0.01, 2 * M_PIf);
    angles[1].z = fmodf(angles[1].z + 0.01, 2 * M_PIf);

    angles[2].x = fmodf(angles[2].x + 0.01, 2 * M_PIf);
    angles[2].z = fmodf(angles[2].z + 0.01, 2 * M_PIf);
    angles[2].y = fmodf(angles[2].y + 0.01, 2 * M_PIf);

    hue = (hue + 1) % 360;
    EndDrawing();
}
