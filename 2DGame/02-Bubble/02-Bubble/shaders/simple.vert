#version 330

uniform mat4 projection, modelview, cameraView;

in vec2 position;

void main()
{
	// Transform position from pixel coordinates to clipping coordinates
	gl_Position = projection * cameraView * modelview * vec4(position, 0.0, 1.0);
}
