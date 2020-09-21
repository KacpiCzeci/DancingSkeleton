#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec4 lp[4];
uniform vec4 lp_dir[4];
uniform float lp_anglein[4];
uniform float lp_angleout[4];
uniform vec4 sun;
uniform int keyframe;
uniform float time;

in vec4 vertex;
in vec4 vertex1;
in vec4 vertex2;

in vec4 normal;
in vec4 normal1;
in vec4 normal2;

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
	vec4 temp_v;
	vec4 temp_n;

	if(keyframe == 1) {
			temp_v = mix(vertex1, vertex2, time);
			temp_n = mix(normal1, normal2, time);
	}
	else {
		temp_v = vertex;
		temp_n = normal;
	}

	int i = 0;
	for(i; i<4; i++) {
		distance[i] = length(V*lp[i] - V*M*temp_v);
		l[i] = normalize(V*lp[i] - V*M*temp_v);
		n[i] = normalize(V*M*temp_n);
		v[i] = normalize(vec4(0, 0, 0, 1) - V*M*temp_v); // vec4 eye position;
		
		dir[i] = normalize(V*lp_dir[i]);
		
		anglein[i] = lp_anglein[i];
		angleout[i] = lp_angleout[i];
	}

	itexture = texture;

	gl_Position=P*V*M*temp_v;
}