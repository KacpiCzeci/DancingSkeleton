#include "reflector.h";
#include "pipe.h"
#include "reflector_const.h"

Reflector::Reflector(glm::mat4 M) {
	M_handle = M;
	M_base = glm::translate(M, glm::vec3(0.0f, -8.0f, 0.0f));
	light.position = glm::translate(M, glm::vec3(0.0f,2.0f,-20.0f));
	light.direction = glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	light.anglein = cos(PI / 12);
	light.angleout = cos(PI / 6);
	speed_handle = PI/2;
	speed_base = PI;
	angle_handle = 0.0f;
	angle_base = 0.0f;
	this->createHandle();
	this->createBase();
}

void Reflector::Move(float timestamp) {
	
	angle_handle += 0.5 * speed_handle * timestamp;
	
	if (angle_handle >= PI / 3) {
		angle_handle = PI / 3;
		speed_handle = -speed_handle;
	}
	else if (angle_handle <= -PI / 3) {
		angle_handle = -PI / 3;
		speed_handle = -speed_handle;
	}
	
	angle_base += 0.5 * speed_base * timestamp;

	if (angle_base >= 0) {
		angle_base = 0;
		speed_base = -speed_base;
	}
	else if (angle_base <= -PI/2) {
		angle_base = -PI/2;
		speed_base = -speed_base;
	}
};

void Reflector::createHandle() {
	vertices_handle.insert(vertices_handle.begin(), v_h.begin(), v_h.end());

	textcords_handle.insert(textcords_handle.begin(), t_h.begin(), t_h.end());

	glm::vec3 a,b,c;
	for (int i = 0; i < vertices_handle.size(); i += 12) {
		a = glm::vec3(vertices_handle[i + 8] - vertices_handle[i], vertices_handle[i + 9] - vertices_handle[i + 1], vertices_handle[i + 10] - vertices_handle[i + 2]);
		b = glm::vec3(vertices_handle[i + 4] - vertices_handle[i], vertices_handle[i + 5] - vertices_handle[i + 1], vertices_handle[i + 6] - vertices_handle[i + 2]);
		c = glm::normalize(glm::cross(a, b));

		for (int j = 0; j < 3; j++) {
			normals_handle.push_back(c.x);
			normals_handle.push_back(c.y);
			normals_handle.push_back(c.z);
			normals_handle.push_back(0.0f);
		}
	}
}

void Reflector::createBase() {
	vertices_base.insert(vertices_base.begin(), v_b.begin(), v_b.end());

	textcords_base.insert(textcords_base.begin(), t_b.begin(), t_b.end());

	glm::vec3 a, b, c;
	for (int i = 0; i < vertices_base.size(); i += 12) {
		a = glm::vec3(vertices_base[i + 8] - vertices_base[i], vertices_base[i + 9] - vertices_base[i + 1], vertices_base[i + 10] - vertices_base[i + 2]);
		b = glm::vec3(vertices_base[i + 4] - vertices_base[i], vertices_base[i + 5] - vertices_base[i + 1], vertices_base[i + 6] - vertices_base[i + 2]);
		c = glm::normalize(glm::cross(a, b));

		for (int j = 0; j < 3; j++) {
			normals_base.push_back(c.x);
			normals_base.push_back(c.y);
			normals_base.push_back(c.z);
			normals_base.push_back(0.0f);
		}
	}

	Pipe p1(35.0f, { 0.0f, 2.0f, 15.0f, 1.0f });
	p1.createPipe(360, 5.0f, 5.0f);
	std::vector<float> temp = p1.returnPipeVertices();
	vertices_base.insert(vertices_base.end(), temp.begin(), temp.end());
	temp.clear();
	temp = p1.returnPipeNormals();
	normals_base.insert(normals_base.end(), temp.begin(), temp.end());
	temp.clear();
	temp = p1.returnPipeTextcoords();
	textcords_base.insert(textcords_base.end(), temp.begin(), temp.end());

	Pipe p2(10.0f, { 0.0f, 2.0f, -10.0f, 1.0f });
	p2.createPipe(8, 5.0f, 7.0f);
	temp.clear();
	temp = p2.returnPipeVertices();
	vertices_base.insert(vertices_base.end(), temp.begin(), temp.end());
	temp.clear();
	temp = p2.returnPipeNormals();
	normals_base.insert(normals_base.end(), temp.begin(), temp.end());
	temp = p2.returnPipeTextcoords();
	textcords_base.insert(textcords_base.end(), temp.begin(), temp.end());
}

void Reflector::changeMatricehandle() {
	M_handle = glm::scale(M_handle, glm::vec3(0.1f, 0.1f, 0.1f));
	M_handle = glm::rotate(M_handle, angle_handle, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Reflector::drawHandle(std::vector<GLuint> texture) {
	sp->use();
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M_handle));

	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, (float*)vertices_handle.data());
	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, (float*)normals_handle.data());
	glEnableVertexAttribArray(sp->a("texture"));
	glVertexAttribPointer(sp->a("texture"), 2, GL_FLOAT, false, 0, (float*)textcords_handle.data());
	glUniform1i(sp->u("tex"), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glDrawArrays(GL_TRIANGLES, 0, vertices_handle.size()/4);
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texture"));
}

void Reflector::changeMatricebase() {
	M_base = glm::translate(M_handle, glm::vec3(0.0f, -8.0f, 0.0f));
	M_base = glm::rotate(M_base, angle_base, glm::vec3(1.0f, 0.0f, 0.0f));
	light.position = glm::translate(M_handle, glm::vec3(0.0f, 2.0f, -20.0f));
	light.position = glm::rotate(light.position, angle_base, glm::vec3(1.0f, 0.0f, 0.0f));
	light.direction = light.position * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
}

void Reflector::drawBase(std::vector<GLuint> texture) {
	sp->use();
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M_base));

	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, (float*)vertices_base.data());
	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, (float*)normals_base.data());
	glEnableVertexAttribArray(sp->a("texture"));
	glVertexAttribPointer(sp->a("texture"), 2, GL_FLOAT, false, 0, (float*)textcords_base.data());
	glUniform1i(sp->u("tex"), 3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture[3]);


	glDrawArrays(GL_TRIANGLES, 0, vertices_base.size() / 4);
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texture"));
}

void Reflector::setMatrice(glm::mat4 M) {
	M_handle = M;
	M_base = glm::translate(M, glm::vec3(0.0f, -8.0f, 0.0f));
	light.position = glm::translate(M, glm::vec3(0.0f, 2.0f, -20.0f));
	light.direction = light.position * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
	light.direction.w = 0.0f;
}

glm::vec4 Reflector::returnLightdir() {
	return light.direction;
}

glm::mat4 Reflector::returnMatrice() {
	return M_handle;
}

glm::vec4 Reflector::returnLight() {
	return light.position * glm::vec4(0.0f, 2.0f, -20.0f, 1.0f);
}

float Reflector::returnAnglein() {
	return light.anglein;
}
float Reflector::returnAngleout() {
	return light.angleout;
}

Reflector::~Reflector() {

}