#include "scene.h"
#include "floor.h"


Scene::Scene() {
	M_Scene = glm::mat4(1.0f);
	this->createScene();
}

void Scene::createScene() {
	vertices = {
		10.0f, -2.0f, -10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,
		10.0f, -2.0f, 10.0f, 1.0f,

		10.0f, -2.0f, 10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,
		10.0f, -5.0f, 10.0f, 1.0f,

		//
		10.0f, -2.0f, 10.0f, 1.0f,
		10.0f, -5.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, 10.0f, 1.0f,

		-10.0f, -2.0f, 10.0f, 1.0f,
		10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, 10.0f, 1.0f,

		//
		-10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f,

		-10.0f, -2.0f, -10.0f, 1.0f,
		-10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f,

		//
		-10.0f, -2.0f, -10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,

		-10.0f, -2.0f, -10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,
		10.0f, -2.0f, -10.0f, 1.0f,

		//
		10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -2.0f, -10.0f, 1.0f,
		10.0f, -2.0f, -10.0f, 1.0f,

		-10.0f, -2.0f, 10.0f, 1.0f,
		-10.0f, -2.0f, -10.0f, 1.0f,
		10.0f, -2.0f, 10.0f, 1.0f,

		//
		10.0f, -5.0f, 10.0f, 1.0f,
		10.0f, -5.0f, -10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f,

		-10.0f, -5.0f, 10.0f, 1.0f,
		10.0f, -5.0f, 10.0f, 1.0f,
		-10.0f, -5.0f, -10.0f, 1.0f
	};

	textcords = {
		0.0f, 0.15f,
		0.0f, 0.0f,
		1.0f, 0.15f,

		1.0f, 0.15f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		//
		1.0f, 0.15f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.15f,
		1.0f, 0.15f,
		0.0f, 0.0f,

		//
		1.0f, 0.15f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 0.15f,
		1.0f, 0.15f,
		0.0f, 0.0f,

		//
		0.0f, 0.15f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 0.15f,
		1.0f, 0.0f,
		1.0f, 0.15f,

		//
		1.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 1.0f,

		//
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 0.0f
	};

	glm::vec3 a, b, c;
	for (int i = 0; i < vertices.size(); i += 12) {
		a = glm::vec3(vertices[i + 8] - vertices[i], vertices[i + 9] - vertices[i + 1], vertices[i + 10] - vertices[i + 2]);
		b = glm::vec3(vertices[i + 4] - vertices[i], vertices[i + 5] - vertices[i + 1], vertices[i + 6] - vertices[i + 2]);
		c = glm::normalize(glm::cross(a, b));

		for (int j = 0; j < 3; j++) {
			normals.push_back(c.x);
			normals.push_back(c.y);
			normals.push_back(c.z);
			normals.push_back(0.0f);
		}
	}

	for (int i = 0; i < 8; i++) {
		Pipe *p = new Pipe(20, { 0.0f, 0.0f, 0.0f, 1.0f });
		p->createPipe(360, 0.5f, 0.5f);
		p->setMatrice(M_Scene);
		pipes.push_back(*p);
		delete p;
	}
	pipes[6].setMatrice(glm::rotate(pipes[0].returnMatrice(), PI / 2, glm::vec3(0.0f, 1.0f, 0.0f)));
	pipes[7].setMatrice(glm::rotate(pipes[1].returnMatrice(), PI / 2, glm::vec3(0.0f, 1.0f, 0.0f)));

	pipes[0].setMatrice(glm::translate(pipes[0].returnMatrice(), glm::vec3(-10.0f, -5.0f, -10.0f))); 
	pipes[1].setMatrice(glm::translate(pipes[1].returnMatrice(), glm::vec3(10.0f, -5.0f, -10.0f)));
	pipes[2].setMatrice(glm::translate(pipes[2].returnMatrice(), glm::vec3(10.0f, -5.0f, 10.0f)));
	pipes[3].setMatrice(glm::translate(pipes[3].returnMatrice(), glm::vec3(-10.0f, -5.0f, 10.0f)));
	pipes[4].setMatrice(glm::translate(pipes[4].returnMatrice(), glm::vec3(10.0f, 14.5f, 10.0f)));
	pipes[5].setMatrice(glm::translate(pipes[5].returnMatrice(), glm::vec3(-10.0f, 14.5f, 10.0f)));
	pipes[6].setMatrice(glm::translate(pipes[6].returnMatrice(), glm::vec3(10.0f, 14.5f, 10.0f)));
	pipes[7].setMatrice(glm::translate(pipes[7].returnMatrice(), glm::vec3(-10.0f, 14.5f, 10.0f)));
	for (int i = 0; i < 8; i++) {
		if (i < 4) {
			pipes[i].setMatrice(glm::rotate(pipes[i].returnMatrice(), PI / 2, glm::vec3(1.0f, 0.0f, 0.0f)));
		}
	}

	for (int i = 0; i < 4; i++) {
		Reflector* p = new Reflector(M_Scene);
		reflectors.push_back(*p);
		delete p;
	}
}

void Scene::drawScene(float timestamp, std::vector<GLuint> texture) {

	reflectors[0].setMatrice(glm::translate(M_Scene, glm::vec3(-10.0f, 13.55f, 0.0f)));
	reflectors[0].setMatrice(glm::rotate(reflectors[0].returnMatrice(), -PI / 2, glm::vec3(0.0f, 1.0f, 0.0f)));

	reflectors[1].setMatrice(glm::translate(M_Scene, glm::vec3(10.0f, 13.55f, 0.0f)));
	reflectors[1].setMatrice(glm::rotate(reflectors[1].returnMatrice(), PI / 2, glm::vec3(0.0f, 1.0f, 0.0f)));

	reflectors[2].setMatrice(glm::translate(M_Scene, glm::vec3(0.0f, 13.55f, -10.0f)));
	reflectors[2].setMatrice(glm::rotate(reflectors[2].returnMatrice(), PI, glm::vec3(0.0f, 1.0f, 0.0f)));

	reflectors[3].setMatrice(glm::translate(M_Scene, glm::vec3(0.0f, 13.55f, 10.0f)));

	for (int i = 0; i < 4; i++) {
		reflectors[i].Move(timestamp);
		reflectors[i].changeMatricehandle();
		reflectors[i].changeMatricebase();
	}

	glm::vec4 lights[4] = { reflectors[0].returnLight(), reflectors[1].returnLight(), reflectors[2].returnLight(), reflectors[3].returnLight() };
	glm::vec4 lightsdir[4] = { reflectors[0].returnLightdir(), reflectors[1].returnLightdir(), reflectors[2].returnLightdir(), reflectors[3].returnLightdir() };
	float anglesin[4] = { reflectors[0].returnAnglein(), reflectors[1].returnAnglein(), reflectors[2].returnAnglein(), reflectors[3].returnAnglein() };
	float anglesout[4] = { reflectors[0].returnAngleout(), reflectors[1].returnAngleout(), reflectors[2].returnAngleout(), reflectors[3].returnAngleout() };

	std::vector<float> temp1, temp2, temp3;
	
	sp->use();
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M_Scene));
	glUniform4fv(sp->u("lp"), 4, glm::value_ptr(lights[0]));
	glUniform4fv(sp->u("lp_dir"), 4, glm::value_ptr(lightsdir[0]));
	glUniform1fv(sp->u("lp_anglein"), 4, anglesin);
	glUniform1fv(sp->u("lp_angleout"), 4, anglesout);


	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, (float*)vertices.data());
	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, (float*)normals.data());
	glEnableVertexAttribArray(sp->a("texture"));
	glVertexAttribPointer(sp->a("texture"), 2, GL_FLOAT, false, 0, (float*)textcords.data());
	glUniform1i(sp->u("tex"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 4);
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texture"));


	for (int i = 0; i < 8;  i++) {
		glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(pipes[i].returnMatrice()));

		glEnableVertexAttribArray(sp->a("vertex"));
		temp1 = pipes[i].returnPipeVertices();
		glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, (float*)temp1.data());
		temp2 = pipes[i].returnPipeNormals();
		glEnableVertexAttribArray(sp->a("normal"));
		glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, (float*)temp2.data());
		temp3 = pipes[i].returnPipeTextcoords();
		glEnableVertexAttribArray(sp->a("texture"));
		glVertexAttribPointer(sp->a("texture"), 2, GL_FLOAT, false, 0, (float*)temp3.data());
		glUniform1i(sp->u("tex"), 2);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture[2]);

		glDrawArrays(GL_TRIANGLES, 0, temp1.size() / 4);
		glDisableVertexAttribArray(sp->a("vertex"));
		glDisableVertexAttribArray(sp->a("normal"));
		glDisableVertexAttribArray(sp->a("texture"));

		temp1.clear();
		temp2.clear();
		temp3.clear();
	}

	for (int i = 0; i < 4; i++) {
		reflectors[i].drawHandle(texture);
		reflectors[i].drawBase(texture);
	}

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(glm::mat4(1.0f)));

	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, floor_v);
	glEnableVertexAttribArray(sp->a("normal"));
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, floor_n);
	glEnableVertexAttribArray(sp->a("texture"));
	glVertexAttribPointer(sp->a("texture"), 2, GL_FLOAT, false, 0, floor_t);
	glUniform1i(sp->u("tex"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("normal"));
	glDisableVertexAttribArray(sp->a("texture"));
}

Scene::~Scene() {

}