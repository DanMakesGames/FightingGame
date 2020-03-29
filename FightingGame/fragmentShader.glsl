#version 330

// Constants
const int MAX_POINT_LIGHTS = 100;
const int MAX_DIR_LIGHTS = 16;

in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 finalColor;

uniform sampler2D texSampler;
uniform int bIsTextured=0;

uniform vec3 eyePos;

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

// Material
struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material material;

vec4 ComputeLight(BaseLight light, vec3 normal, vec3 lightDir)
{
	vec4 ambientColor = vec4(light.color * light.ambientIntensity, 1.0f);
	float diffuseFactor = dot(normal, lightDir);
	vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * material.diffuse * max(diffuseFactor,0.0f), 1.0f);
	return ambientColor + diffuseColor;
	//return ambientColor;
	//return diffuseColor;
}

void main() 
{
	vec4 texColor = vec4(1,1,1,1);
	
	vec4 totalColor = vec4(0,0,0,0);
	
	for(int index = 0; index < numberPointLights; index++)
	{
		vec3 lightDir = normalize(pointLights[index].position - fragPosition);
		totalColor += ComputeLight(pointLights[index].base, fragNormal, lightDir);
	}
	
	for (int index = 0; index < numberDirLights; index++)
	{
		totalColor += ComputeLight(dirLights[index].base, fragNormal, -dirLights[index].dir);
	}
	
	if (bIsTextured == 1)
	{
		texColor = texture2D(texSampler, fragTexCoord.xy);
	}
	
	totalColor.w = 1.0f;
	finalColor = (texColor * totalColor) + vec4(material.ambient,1.0f);
	finalColor.w = 1.0f;
	//finalColor = texColor;
	//finalColor = (texColor * totalColor);
}
