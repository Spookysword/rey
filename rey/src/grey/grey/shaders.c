#include "grey/grey/shaders.h"

const char* colorVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"out vec4 color;\n"
"uniform vec2 viewport;\n"
"uniform vec3 offset;\n"
"void main() {\n"
"   gl_Position = vec4((aPos.x - viewport.x) / viewport.x - (offset.x / viewport.x), (aPos.y + viewport.y) / viewport.y + (offset.y / viewport.y), aPos.z, 1.0);\n"
"	color = aColor;\n"
"}\0";
const char* colorFragmentShader = "#version 330 core\n"
"in vec4 color;\n"
"void main() {\n"
"	gl_FragColor = color;\n"
"}\0";
const char* textureVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec4 color;\n"
"out vec2 TexCoord;\n"
"uniform vec2 viewport;\n"
"uniform vec3 offset;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4((aPos.x - viewport.x) / viewport.x - (offset.x / viewport.x), (aPos.y + viewport.y) / viewport.y + (offset.y / viewport.y), aPos.z, 1.0);\n"
"	color = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\0";
const char* textureFragmentShader = "#version 330 core\n"
"in vec4 color;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D currentTexture;\n"
"void main()\n"
"{\n"
"	if (texture(currentTexture, TexCoord).a < 0.5) discard;\n"
"	gl_FragColor = texture(currentTexture, TexCoord) * color;\n"
"}\0";
const char* fontVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec4 color;\n"
"out vec2 TexCoord;\n"
"uniform vec2 viewport;\n"
"uniform vec3 offset;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4((aPos.x - viewport.x) / viewport.x - (offset.x / viewport.x), (aPos.y + viewport.y) / viewport.y + (offset.y / viewport.y), aPos.z, 1.0);\n"
"	color = aColor;\n"
"	TexCoord = aTexCoord;\n"
"}\0";
const char* fontFragmentShader = "#version 330 core\n"
"in vec4 color;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D currentTexture;\n"
"void main()\n"
"{\n"
"	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(currentTexture, TexCoord).r);\n"
"	gl_FragColor = color * sampled;\n"
"}\0";

const char* texture3DVertexShader = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec4 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"layout (location = 3) in vec3 aNormal;\n"
"out vec4 color;\n"
"out vec2 TexCoord;\n"
"out vec3 normal;\n"
"out vec3 worldPos;\n"
"uniform vec3 offset;\n"
"uniform mat4 transformProj;\n"
"uniform mat4 transform;\n"
"void main() {\n"
"   gl_Position = transformProj*vec4(aPos.x - offset.x, aPos.y + offset.y, aPos.z, 1.0);\n"
"	color = aColor;\n"
"	TexCoord = aTexCoord;\n"
"	normal = (transform * vec4(aNormal, 0.0)).xyz;\n"
"	worldPos = (transform * vec4(aPos, 1.0)).xyz;\n"
"}\0";
const char* texture3DFragmentShader = "#version 330 core\n"
"in vec4 color;\n"
"in vec2 TexCoord;\n"
"in vec3 normal;\n"
"in vec3 worldPos;\n"
"uniform sampler2D currentTexture;\n"
"void main() {\n"
"	vec3 viewPos = vec3(0.);\n"
"	vec3 lightPos = vec3(2., 4., -5.);\n"
"	vec3 lightColor = vec3(1.0, 1.0, 0.9);\n"
"	float ambientStrength = 0.3;\n"
"	vec3 ambient = ambientStrength * lightColor;\n"
"	vec3 norm = normalize(normal);\n"
"	vec3 lightDir = normalize(lightPos - worldPos);\n"
"	float diff = max(dot(norm, lightDir), -0.03);\n"
"	vec3 diffuse = diff * lightColor;\n"
"	float specularStrength = 1.5;\n"
"	vec3 viewDir = normalize(viewPos - worldPos);\n"
"	vec3 reflectDir = reflect(-lightDir, norm);\n"
"	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);\n"
"	vec3 specular = specularStrength * spec * lightColor;\n"
"	\n"
"	\n"
"	gl_FragColor = vec4((specular+ambient+diffuse)*(color*texture(currentTexture, TexCoord)).xyz, 1.0f);\n"
"}\0";