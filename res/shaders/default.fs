#version 330 core

uniform sampler2D TEX_SAMPLER;

in vec2 fTexCoords;

void main()
{
    gl_FragColor = texture(TEX_SAMPLER, fTexCoords);
}
