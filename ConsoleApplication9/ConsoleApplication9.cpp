#include <iostream>
#include <stdio.h>
#include <math.h>
#include <windows.h>






struct vec2
{
    float x, y;

    vec2(float value) : x(value), y(value) {}
    vec2(float _x, float _y) : x(_x), y(_y) {}

    vec2 operator+(vec2 const& other) { return vec2(x + other.x, y + other.y); }
    vec2 operator-(vec2 const& other) { return vec2(x - other.x, y - other.y); }
    vec2 operator*(vec2 const& other) { return vec2(x * other.x, y * other.y); }
    vec2 operator/(vec2 const& other) { return vec2(x / other.x, y / other.y); }


};

struct vec3
{
    float x, y, z;

    vec3(float _value) : x(_value), y(_value), z(_value) {};
    vec3(float _x, vec2 const& v) : x(_x), y(v.x), z(v.y) {};
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};

    vec3 operator+(vec3 const& other) { return vec3(x + other.x, y + other.y, z + other.z); }
    vec3 operator-(vec3 const& other) { return vec3(x - other.x, y - other.y, z - other.z); }
    vec3 operator*(vec3 const& other) { return vec3(x * other.x, y * other.y, z * other.z); }
    vec3 operator/(vec3 const& other) { return vec3(x / other.x, y / other.y, z / other.z); }
    vec3 operator-() { return vec3(-x, -y, -z); }

};

float clamp(float volue, float min, float max) { return fmax(fmin(volue, max), min); }
float length(vec2 const& v) { return sqrt(v.x * v.x + v.y * v.y); }
float length(vec3 v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
vec3 norm(vec3 v) { return v / length(v); }
float dot(vec3 const& a, vec3 const& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

vec2 sphere(vec3 ro, vec3 rd, float r) {
    float b = dot(ro, rd);
    float c = dot(ro, ro) - r * r;
    float h = b * b - c;
    if (h < 0.0) return vec2(-1.0);
    h = sqrt(h);
    return vec2(-b - h, -b + h);
}


void SetWindow(int Width, int Height)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(Handle, coord);
    SetConsoleWindowInfo(Handle, TRUE, &Rect);
}


void main()
{
    int w = 120;
    int h = 30;
    SetWindow(w, h);
    float aspect = (float)w / h;
    float pixelAspect = 11.0f / 24.0f;
    char gradient[] = " .:!/r(l1Z4H9W8$@";
    int gradientSize = std::size(gradient) - 2;

    char* screen = new char[w * h + 1];
    screen[w * h] = '\0';

    for (int t = 0; t < 100000000; t++) {
        vec3 light = norm(vec3(sin(t * 0.001), cos(t * 0.001), -1.0));
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                vec2 uv = vec2(i, j) / vec2(w, h) * 2.0f - 1.0f;
                uv.x *= aspect * pixelAspect;
                vec3 ro = vec3(-2, 0, 0);
                vec3 rd = norm(vec3(1, uv));
                char pixel = ' ';
                int color = 0;
                vec2 intersection = sphere(ro, rd, 1);
                if (intersection.x > 0) {
                    vec3 itPoint = ro + rd * intersection.x;
                    vec3 n = norm(itPoint);
                    float diff = dot(n, light);
                    color = (int)(diff * 20);
                }
                color = clamp(color, 0, gradientSize);
                pixel = gradient[color];
                screen[i + j * w] = pixel;
            }
        }
        printf(screen);
    }

    getchar();

}
