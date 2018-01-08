#version 330 core

//Based on the tutorial code from https://open.gl/framebuffers

in vec2 textureCoordsOut;

out vec4 colour;

uniform sampler2D texture1;

float getEnhancedColour(float colour)
{
	return colour * 1.5f;
}

void main()
{
	vec4 top = texture(texture1, vec2(textureCoordsOut.x, textureCoordsOut.y + 1.0f /400.0f));
	vec4 bottom = texture(texture1, vec2(textureCoordsOut.x, textureCoordsOut.y - 1.0f /400.0f));
	vec4 left = texture(texture1, vec2(textureCoordsOut.x + 1.0f /400.0f, textureCoordsOut.y));
	vec4 right = texture(texture1, vec2(textureCoordsOut.x - 1.0f /400.0f, textureCoordsOut.y));
	vec4 topleft = texture(texture1, vec2(textureCoordsOut.x + 1.0f /400.0f, textureCoordsOut.y + 1.0f /400.0f));
	vec4 topright = texture(texture1, vec2(textureCoordsOut.x + 1.0f /400.0f, textureCoordsOut.y + 1.0f /400.0f));
	vec4 bottomleft = texture(texture1, vec2(textureCoordsOut.x - 1.0f /400.0f, textureCoordsOut.y - 1.0f /400.0f));
	vec4 bottomright = texture(texture1, vec2(textureCoordsOut.x - 1.0f /400.0f, textureCoordsOut.y - 1.0f /400.0f));



	vec4 sx = -topleft - 2 * left - bottomleft + topright + 2 * right + bottomright;
	vec4 sy = -topleft - 2 * top - topright + bottomleft + 2 * bottom + bottomright;
	vec4 sobel = sqrt(sx * sx + sy * sy);

	colour = sobel;
}