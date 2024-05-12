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
Vector3 angle;
void draw_sphere(Vector3 position, float radius, Color color, int resolution = 100) {
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
            vertex.y += position.y - radius;
            vertex.z += position.z;

            Vector2 n_vertex = projection(vertex);
            DrawCircle(n_vertex.x, n_vertex.y, 1, color);
        }
    }
}

void loop() {
    BeginDrawing();
    ClearBackground(BLACK);
    draw_sphere({ screen_width / 2.0f, screen_width / 2.0f, 0 }, 100, WHITE, 30);
    angle.y += 0.01;
    EndDrawing();
}
