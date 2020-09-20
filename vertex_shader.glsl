#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp[4];
uniform vec4 lp_dir[4];
uniform float lp_anglein[4];
uniform float lp_angleout[4];
uniform vec4 sun;

in vec4 vertex;
in vec4 normal;
in vec2 texture;

out float distance[4];
out vec2 itexture;
out vec4 l[4];
out vec4 n[4];
out vec4 v[4];
out vec4 dir[4];
out float anglein[4];
out float angleout[4];

void main(void) {
	

	int i = 0;
	for(i; i<4; i++) {
		distance[i] = length(V*lp[i] - V*M*vertex);
		l[i] = normalize(V*lp[i] - V*M*vertex);
		n[i] = normalize(V*M*normal);
		v[i] = normalize(vec4(0, 0, 0, 1) - V*M*vertex); // vec4 eye position;
		
		dir[i] = normalize(V*lp_dir[i]);
		
		anglein[i] = lp_anglein[i];
		angleout[i] = lp_angleout[i];
	}

	itexture = texture;

	gl_Position=P*V*M*vertex;
}