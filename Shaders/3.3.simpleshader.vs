#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout (location = 1) in vec4 aColor; // the color variable has attribute position 1
out vec4 ourColor; // output a color to the fragment shader

void main()
{
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
}