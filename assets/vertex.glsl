#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 bColor;
layout (location = 2) in vec4 tColor;

out vec4 bcolor;
out vec4 tcolor;

void main(){
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
    bcolor = bColor;
    tcolor = tColor;
}
