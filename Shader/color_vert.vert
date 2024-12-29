#version 460

layout(set = 0, binding = 0, std140) uniform buf
{
    mat4 mvp;
} ubuf;

layout(location = 0) out vec3 v_color;
layout(location = 1) in vec3 color;
layout(location = 0) in vec4 position;

void main()
{
    v_color = color;
    gl_Position = ubuf.mvp * position;
    gl_PointSize = 2.0;
}
/*
C:\Users\ngdtu\source\repos\glslang\glslang\out\build\x64-Debug\StandAlone
glslangValidator -V -S vert "C:\Users\ngdtu\source\repos\RopView\Source\Shader\color_vert.vert" -o "C:\Users\ngdtu\source\repos\RopView\Source\Shader\color_vert_1.spv"
*/