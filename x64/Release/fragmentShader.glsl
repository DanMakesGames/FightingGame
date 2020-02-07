#version 330

in vec3 fragPosition;
in vec3 fragNormal;

uniform vec3 AmbientColor=vec3(0.1);
uniform vec3 LightDirection=normalize(vec3(0,1,0));
uniform vec3 LightColor=vec3(0,0.3,0);
uniform vec3 DiffuseColor=vec3(1);

out vec3 finalColor;

uniform vec3 LightDirection0=normalize(vec3(-1,0,0));
uniform vec3 LightColor0=vec3(0.3, 0.0, 0.0);

void main() {
	// Compute irradiance (sum of ambient & direct lighting)
	vec3 irradiance=AmbientColor + LightColor * max(0,dot(LightDirection,fragNormal)) + LightColor0 * max(0,dot(LightDirection0,fragNormal));

	// Diffuse reflectance
	vec3 reflectance=irradiance * DiffuseColor;

	// Gamma correction
	gl_FragColor=vec4(sqrt(reflectance),1);
}
