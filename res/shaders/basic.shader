#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texColor;

out vec2 vTexCoord;
out float vTexColor;

uniform mat4 uMVP;

void main(){
    gl_Position = uMVP * position;
    vTexCoord = texCoord;
    vTexColor = texColor;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTexCoord;
in float vTexColor;

uniform sampler2D uTexture;

vec4 toGrayscale(in vec4 color)
{
  float average = (color.r + color.g + color.b) / 3.0;
  return vec4(average, average, average, 1.0);
}

vec4 colorize(in vec4 grayscale, in vec4 color){
    return (grayscale * color);
}

void main(){
    vec4 uColors[8];
    uColors[0] = vec4(0.01, 0.03, 0.095, 1.0);
    uColors[1] = vec4(0.0, 1.0, 1.0, 1.0);
    uColors[2] = vec4(0.0, 0.0, 1.0, 1.0);
    uColors[3] = vec4(1.0, 0.6, 0.0, 1.0);
    uColors[4] = vec4(1.0, 1.0, 0.0, 1.0);
    uColors[5] = vec4(0.0, 1.0, 0.0, 1.0);
    uColors[6] = vec4(0.6, 0.0, 1.0, 1.0);
    uColors[7] = vec4(1.0, 0.0, 0.0, 1.0);
    
    vec4 uColor = uColors[int(vTexColor)];

    color = colorize(toGrayscale(texture(uTexture, vTexCoord)), uColor);
}