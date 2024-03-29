#version 430 core

in vec3 lightDirV;
in vec3 vNormalV;

uniform vec3 ambientColour;
uniform vec3 diffuseColour;

uniform vec3 lightColour = {1,1,1};
uniform vec3 emissiveColour = {0,0,0};
uniform vec3 specularColour = {0.0f,0.0f,0.0f};
uniform float shininess     = 50.0f;
uniform float alpha         = 1.0f;

out vec4 fragColour;

void main()
{
	vec3 lightDir = normalize( lightDirV );
	vec3 vNormal = normalize( vNormalV );

	vec3 diffuse = diffuseColour * lightColour * max( dot( vNormal, lightDir ), 0);

	fragColour = vec4( emissiveColour + ambientColour + diffuse, alpha);
}