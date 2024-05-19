#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    //FragColor = texture(texture1, TexCoord);
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.6);
    //vec2 tc = vec2(-TexCoord.x, TexCoord.y);
    //FragColor = mix(texture(texture1, TexCoord), texture(texture2, tc), 0.6);
}