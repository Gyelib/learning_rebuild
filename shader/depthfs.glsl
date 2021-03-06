#version 330 core

in vec3 outColor;
in vec2 outTexcoord;

uniform sampler2D texture1;

float near = 0.1;
float far = 100.0;

float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    gl_FragColor = vec4(vec3(depth), 1.0);
}
