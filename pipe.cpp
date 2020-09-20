#include "pipe.h"

Pipe::Pipe(float l, std::vector<float> b) {
	length = l;
	begin = b;
	M_pipe = glm::mat4(1.0f);
};

void Pipe::createPipe(int steps, float radius1, float radius2) {
	std::vector<float> vertstop;
	std::vector<float> vertsbottom;

	for (int i = 0; i <= steps; i++) {
		vertstop.push_back(radius1 * cos(2 * PI * i / steps));
		vertstop.push_back(radius1 * sin(2 * PI * i / steps));
	};
	for (int i = 0; i < vertstop.size() - 2; i += 2) {
		verts.insert(verts.end(), begin.begin(), begin.end());
		textcoords.insert(textcoords.end(), { 0.5f, 0.5f });
		
		for (int j = 0; j <= 2; j += 2) {
			verts.push_back(begin[0] + vertstop[i + j]);
			textcoords.push_back(0.5f + vertstop[i + j] / 2);
			
			verts.push_back(begin[1] + vertstop[(i + j + 1)]);
			textcoords.push_back(0.5f + vertstop[i + j + 1] / 2);
			
			verts.push_back(begin[2] + 0.0f);
			verts.push_back(begin[3]);
		}
	}

	glm::vec3 a, b, c;
	int size = (int)verts.size();
	for (int i = 0; i < verts.size(); i += 12) {
		a = glm::vec3(verts[i + 8] - verts[i], verts[i + 9] - verts[i + 1], verts[i + 10] - verts[i + 2]);
		b = glm::vec3(verts[i + 4] - verts[i], verts[i + 5] - verts[i + 1], verts[i + 6] - verts[i + 2]);
		c = glm::normalize(glm::cross(b, a));

		for (int j = 0; j < 3; j++) {
			normals.push_back(c.x);
			normals.push_back(c.y);
			normals.push_back(c.z);
			normals.push_back(0.0f);
		}
	}

	begin[2] = begin[2]-length;

	for (int i = 0; i <= steps; i++) {
		vertsbottom.push_back(radius2 * cos(2 * PI * i / steps));
		vertsbottom.push_back(radius2 * sin(2 * PI * i / steps));
	};
	for (int i = 0; i < vertsbottom.size() - 2; i += 2) {
		verts.insert(verts.end(), begin.begin(), begin.end());
		textcoords.insert(textcoords.end(), { 0.5f, 0.5f });
		
		for (int j = 0; j <= 2; j += 2) {
			verts.push_back(begin[0] + vertsbottom[i + j]);
			textcoords.push_back(0.5f + vertsbottom[i + j] / 2);

			verts.push_back(begin[1] + vertsbottom[(i + j + 1)]);
			textcoords.push_back(0.5f + vertsbottom[i + j + 1] / 2);

			verts.push_back(begin[2] + 0.0f);
			verts.push_back(begin[3]);
		}
	}

	float l = 0.0f; 

	for (int i = 0; i < vertstop.size() - 2; i += 2) {
		
		verts.push_back(begin[0] + vertstop[i]);
		textcoords.push_back(l);
		verts.push_back(begin[1] + vertstop[i + 1]);
		textcoords.push_back(1.0f);
		verts.push_back(begin[2] + length);
		verts.push_back(1.0f);

		verts.push_back(begin[0] + vertstop[i + 2]);
		textcoords.push_back(l + 1.0f/steps);
		verts.push_back(begin[1] + vertstop[i + 3]);
		textcoords.push_back(1.0f);
		verts.push_back(begin[2] + length);
		verts.push_back(1.0f);

		verts.push_back(begin[0] + vertsbottom[i]);
		textcoords.push_back(l);
		verts.push_back(begin[1] + vertsbottom[i + 1]);
		textcoords.push_back(0.0f);
		verts.push_back(begin[2]);
		verts.push_back(1.0f);


		verts.push_back(begin[0] + vertstop[i + 2]);
		textcoords.push_back(l + 1.0f/steps);
		verts.push_back(begin[1] + vertstop[i + 3]);
		textcoords.push_back(1.0f);
		verts.push_back(begin[2] + length);
		verts.push_back(1.0f);

		verts.push_back(begin[0] + vertsbottom[i + 2]);
		textcoords.push_back(l + 1.0f/steps);
		verts.push_back(begin[1] + vertsbottom[i + 3]);
		textcoords.push_back(0.0f);
		verts.push_back(begin[2]);
		verts.push_back(1.0f);

		verts.push_back(begin[0] + vertsbottom[i]);
		textcoords.push_back(l);
		verts.push_back(begin[1] + vertsbottom[i + 1]);
		textcoords.push_back(0.0f);
		verts.push_back(begin[2]);
		verts.push_back(1.0f);


		l += 1.0f / steps;
	}

	for (int i = size; i < verts.size(); i += 12) {
		a = glm::vec3(verts[i + 8] - verts[i], verts[i + 9] - verts[i + 1], verts[i + 10] - verts[i + 2]);
		b = glm::vec3(verts[i + 4] - verts[i], verts[i + 5] - verts[i + 1], verts[i + 6] - verts[i + 2]);
		c = glm::normalize(glm::cross(a, b));

		for (int j = 0; j < 3; j++) {
			normals.push_back(c.x);
			normals.push_back(c.y);
			normals.push_back(c.z);
			normals.push_back(0.0f);
		}
	}
}

std::vector<float> Pipe::returnPipeVertices() {
	return verts;
}
std::vector<float> Pipe::returnPipeNormals() {
	return normals;
}

std::vector<float> Pipe::returnPipeTextcoords() {
	return textcoords;
}

glm::mat4 Pipe::returnMatrice() {
	return M_pipe;
}

void Pipe::setMatrice(glm::mat4 matrice) {
	M_pipe = matrice;
};

Pipe::~Pipe() {
}
