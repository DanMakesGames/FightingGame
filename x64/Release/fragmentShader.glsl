#version 330

// Constants
const int MAX_POINT_LIGHTS = 100;

in vec3 fragPosition;
in vec3 fragNormal;

uniform vec3 AmbientColor=vec3(0.1);
uniform vec3 LightDirection=normalize(vec3(0,1,0));
uniform vec3 LightColor=vec3(0,0.3,0);
uniform vec3 DiffuseColor=vec3(1);

out vec3 finalColor;

uniform vec3 LightDirection0=normalize(vec3(-1,0,0));
uniform vec3 LightColor0=vec3(0.3, 0.0, 0.0);

// lights (inspired by a tutorial.)
struct BaseLight
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct Attenuation
{
	float constant;
	float linear;
	float exp;
};

struct PointLight
{
	BaseLight base;
	vec3 position;
	Attenuation atten;
};

layout (std140) uniform LightBlock
{
	int numberPointLights;
	PointLight pointLights[MAX_POINT_LIGHTS];
};

void main() {
	// Compute irradiance (sum of ambient & direct lighting)
	//vec3 irradiance=AmbientColor + LightColor * max(0,dot(LightDirection,fragNormal)) + LightColor0 * max(0,dot(LightDirection0,fragNormal));
	vec3 irradiance=AmbientColor;
	
	for(int index = 0; index < numberPointLights; index++)
	{
		vec3 lightDir = normalize(fragPosition - pointLights[index].position);
		irradiance += pointLights[index].base.color * max(0, dot(lightDir,fragNormal));
	}
	
	// Diffuse reflectance
	vec3 reflectance=irradiance * DiffuseColor;

	// Gamma correction
	gl_FragColor=vec4(sqrt(reflectance),1);
}
