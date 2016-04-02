#version 330 core

out vec4 out_Color4;
in float out_alpha;

void main(void)
{
	out_Color4 = vec4(1, 1, 1, 1);
	out_Color4.a = out_alpha;
}