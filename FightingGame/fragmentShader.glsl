#version 330

// Constants
const int MAX_POINT_LIGHTS = 100;
const int MAX_DIR_LIGHTS = 16;

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

uniform vec3 AmbientColor=vec3(0.1);
uniform vec3 LightDirection=normalize(vec3(0,1,0));
uniform vec3 LightColor=vec3(0,0.3,0);
uniform vec3 DiffuseColor=vec3(1);

out vec4 finalColor;

uniform vec3 LightDirection0=normalize(vec3(-1,0,0));
uniform vec3 LightColor0=vec3(0.3, 0.0, 0.0);

uniform sampler2D texSampler;
uniform int bIsTextured=0;

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

struct DirLight
{
	BaseLight base;
	vec3 dir;
};

layout (std140) uniform LightBlock
{
	int numberPointLights;
	int numberDirLights;
	PointLight pointLights[MAX_POINT_LIGHTS];
	DirLight dirLights[MAX_DIR_LIGHTS];
};

void main() {
	// Compute irradiance (sum of ambient & direct lighting)
	//vec3 irradiance=AmbientColor + LightColor * max(0,dot(LightDirection,fragNormal)) + LightColor0 * max(0,dot(LightDirection0,fragNormal));
	vec3 irradiance=AmbientColor;
	vec4 texColor;
	
	for(int index = 0; index < numberPointLights; index++)
	{
		vec3 lightDir = normalize(pointLights[index].position - fragPosition);
		irradiance += pointLights[index].base.color * max(0, dot(lightDir,fragNormal));
	}
	
	for (int index = 0; index < numberDirLights; index++)
	{
		irradiance += dirLights[index].base.color * max(0, dot(-dirLights[index].dir, fragNormal));
	}
	
	if (bIsTextured == 1)
	{
		//texColor = texture2D(texSampler, fragTexCoord.xy);
		texColor = texture2D(texSampler, vec2(0.5,0.5));
	}
	
	// Diffuse reflectance
	vec3 reflectance=irradiance * DiffuseColor;

	// Gamma correction
	finalColor = vec4(sqrt(reflectance),1) + texColor;
}
