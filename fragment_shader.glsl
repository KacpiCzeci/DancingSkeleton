#version 330

uniform sampler2D tex;

out vec4 pixelColor;

in float distance[4];
in vec2 itexture;
in vec4 l[4];
in vec4 n[4];
in vec4 v[4];
in vec4 dir[4];
in float anglein[4];
in float angleout[4];

void main(void) {
	
	vec4 color = texture(tex, itexture);

	vec4 ambient = 0.2 * vec4(1, 1, 1, 0) * color;
	float attenuation;

	float diffuseL;
	vec4 diffuse = vec4(0, 0, 0, 0);
	float specularL;
	vec4 specular = vec4(0, 0, 0, 0);
	vec4 L, N, V;
	vec4 r;
	vec4 ndir;
	float cosDir;
	float spot;

		
	
	int i = 0;
	vec4 temp = vec4(0,0,0,0);

	for(i=0; i<4; i++) {

		L = normalize(l[i]);
		N = normalize(n[i]);
		V = normalize(v[i]);
		ndir = normalize(dir[i]);

		attenuation = clamp(20/distance[i], 0, 1);

		cosDir = dot(-L, ndir);
		spot = smoothstep(angleout[i], anglein[i], cosDir);
		//spot = clamp((cosDir-angleout[i])/(anglein[i]-angleout[i]), 0 ,1);

		diffuseL = clamp(dot(N, L), 0, 1);
		diffuse += attenuation * spot * diffuseL  * color * vec4(1, 1, 1, 1); // Kd * diffuseL * light

		r = reflect(-L, N);
		specularL = pow(clamp(dot(r, V), 0, 1), 25); // power shininess
		specular +=  attenuation * spot * vec4(1, 1, 1, 1) * specularL;

	}

	pixelColor = ambient + diffuse + specular;
	pixelColor.a = 1.0f;
	
}