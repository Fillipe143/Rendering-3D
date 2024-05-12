#include <cmath>
#include <cstddef>
#include <cstdio>
#include <raylib.h>

const int screen_width = 960;
const int screen_height = 720;

const int target_fps = 60;
const int log_level = LOG_WARNING;

void setup();
void loop();

int main() {
    SetTraceLogLevel(log_level);
    InitWindow(screen_width, screen_height, "Rotating Cube");
    SetTargetFPS(target_fps);

    setup();
    while (!WindowShouldClose()) loop();
    CloseWindow();

    return 0;
}

const Vector3 CUBE_VERTEX[] = {
    { -1, -1, -1 },
    { -1, -1, 1 },
    { -1, 1, -1 },
    { -1, 1, 1 },
    { 1, -1, -1 },
    { 1, -1, 1 },
    { 1, 1, -1 },
    { 1, 1, 1 },
};

void setup() {
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

void draw_cube(Vector3 position, float size, Vector3 angle, Color color) {
    Vector2 vertexes[8];
    for (size_t i = 0; i < sizeof(CUBE_VERTEX) / sizeof(Vector3); i++) {
        Vector3 vertex = CUBE_VERTEX[i];
        vertex = rotate_x(vertex, angle.x);
        vertex = rotate_y(vertex, angle.y);
        vertex = rotate_z(vertex, angle.z);

        vertex.x *= size / 2;
        vertex.y *= size / 2;
        vertex.z *= size / 2;

        vertex.x += position.x;
        vertex.y += position.y;
        vertex.z += position.z;

        vertexes[i] = projection(vertex);
    }

    DrawLine(vertexes[0].x, vertexes[0].y, vertexes[1].x, vertexes[1].y, color);
    DrawLine(vertexes[0].x, vertexes[0].y, vertexes[2].x, vertexes[2].y, color);
    DrawLine(vertexes[0].x, vertexes[0].y, vertexes[4].x, vertexes[4].y, color);

    DrawLine(vertexes[1].x, vertexes[1].y, vertexes[3].x, vertexes[3].y, color);
    DrawLine(vertexes[1].x, vertexes[1].y, vertexes[5].x, vertexes[5].y, color);

    DrawLine(vertexes[2].x, vertexes[2].y, vertexes[3].x, vertexes[3].y, color);
    DrawLine(vertexes[2].x, vertexes[2].y, vertexes[6].x, vertexes[6].y, color);

    DrawLine(vertexes[4].x, vertexes[4].y, vertexes[6].x, vertexes[6].y, color);
    DrawLine(vertexes[4].x, vertexes[4].y, vertexes[5].x, vertexes[5].y, color);

    DrawLine(vertexes[7].x, vertexes[7].y, vertexes[3].x, vertexes[3].y, color);
    DrawLine(vertexes[7].x, vertexes[7].y, vertexes[5].x, vertexes[5].y, color);
    DrawLine(vertexes[7].x, vertexes[7].y, vertexes[6].x, vertexes[6].y, color);
}

Vector3 angle = { 15 * M_PIf / 180, 0, 0 };
int hue = 0;
void loop() {
    BeginDrawing();
    ClearBackground(BLACK);
    draw_cube({ screen_width / 2.0f, screen_height / 2.0f }, 100, angle, ColorFromHSV(hue, 1, 1));
    angle.y += 0.01;
    angle.x += 0.05;

    angle.y = fmodf(angle.y, 2 * M_PIf);
    angle.x = fmodf(angle.y, 2 * M_PIf);
    hue = (hue + 1) % 360;

    EndDrawing();
}
