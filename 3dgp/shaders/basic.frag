// FRAGMENT SHADER

#version 330


in vec4 color;
out vec4 outColor;

// Materials
uniform vec3 materialAmbient;
uniform vec3 materialDiffuse;
uniform vec3 materialSpecular;
uniform float shininess;

// View Matrix
uniform mat4 matrixView;

uniform sampler2D texture0;
uniform sampler2D texture1;

in vec4 position;
in vec3 normal;

in vec2 texCoord0;
in vec2 texCoord1;

struct POINT
{
vec3 position;
vec3 diffuse;
vec3 specular;
};
uniform POINT lightPoint1, lightPoint2;

vec4 PointLight(POINT light)
{
	//calculate point light

	vec4 color = vec4(0, 0, 0, 0);
	vec3 L = normalize(matrixView * vec4(light.position,1) - position).xyz;
	float NdotL = dot (normal, L);
	color += vec4(materialDiffuse * light.diffuse, 1) * max(NdotL, 0);

	vec3 V = normalize(-position.xyz);
	vec3 R = reflect(-L, normal);
	float RdotV = dot(R, V);
	color += vec4(materialSpecular * light.specular * pow(max(RdotV,0), shininess), 1);

	float dist = length(matrixView * vec4(light.position, 1) - position);
	float att = 1 / (0.03 * dist * dist);

	return color * att;
}

void main(void)
{
outColor = color;

outColor += PointLight(lightPoint1);
outColor += PointLight(lightPoint2);

outColor += texture(texture0, texCoord0);
outColor += texture(texture1, texCoord1);
}