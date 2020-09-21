#include "ModelGroup.h"

ModelGroup::ModelGroup(int Tsize, std::string& dirName, std::string& KfName, float x, float y, float z) {
	this->dirName = dirName;
	this->KfName = KfName;
	this->TableSize = Tsize;
	this->CurrentFrame = 0;
	this->NextFrame = (Tsize > 0) ? 1 : 0;

	for (int i = 0; i < Tsize; i++)
	{
		std::cout << this->dirName + "\\" + this->KfName + std::to_string(i*5) + ".obj" << std::endl;
		this->ModelT.push_back(ModelCtrl(x, y, z));
		this->ModelT[i].loadModel(this->dirName + "\\" + this->KfName + std::to_string(i*5) + ".obj");
	}	
}

void ModelGroup::Draw(GLuint * texture)
{
	this->ModelT[CurrentFrame].drawLLD(texture);
}

int ModelGroup::GetCurKF()
{
	return this->CurrentFrame;
}

void ModelGroup::goToNextKF()
{
	int NF = this->NextFrame;
	this->CurrentFrame = NF;
	if (NF + 1 == TableSize) {
		NF = 0;
	}
	else {
		NF += 1;
	}
	this->NextFrame = NF;
}

void ModelGroup::interpolation(float time, GLuint* texture)
{
	sp->use();
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(this->ModelT[this->CurrentFrame].getModelPosition()));
	glUniform1f(sp->u("time"), time);
	glUniform1i(sp->u("keyframe"), 1);

	float* CF = ModelT[this->CurrentFrame].getVerticesLLD();
	float* NF = ModelT[this->NextFrame].getVerticesLLD();
	float* CFnormals = ModelT[this->CurrentFrame].getNormalsLLD();
	float* NFnormals = ModelT[this->NextFrame].getNormalsLLD();
	float* Textures = ModelT[this->NextFrame].getTexturesLLD();
	int VertexNumber = ModelT[this->CurrentFrame].getVertexCount();

	// vertex positions at current frame
	glEnableVertexAttribArray(sp->a("vertex1"));
	glVertexAttribPointer(sp->a("vertex1"), 4, GL_FLOAT, false, 0, CF);


	// vertex positions at next frame
	glEnableVertexAttribArray(sp->a("vertex2"));
	glVertexAttribPointer(sp->a("vertex2"), 4, GL_FLOAT, false, 0, NF);



	glEnableVertexAttribArray(sp->a("normal1"));
	glVertexAttribPointer(sp->a("normal1"), 4, GL_FLOAT, false, 0, CFnormals);


	glEnableVertexAttribArray(sp->a("normal2"));
	glVertexAttribPointer(sp->a("normal2"), 4, GL_FLOAT, false, 0, NFnormals);

	glEnableVertexAttribArray(sp->a("texture"));
	glVertexAttribPointer(sp->a("texture"), 2, GL_FLOAT, false, 0, Textures);
	glUniform1i(sp->u("tex"), 4);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, *texture);


	glDrawArrays(GL_TRIANGLES, 0, VertexNumber);

	glDisableVertexAttribArray(sp->a("vertex1"));
	glDisableVertexAttribArray(sp->a("vertex2"));
	glDisableVertexAttribArray(sp->a("normal1"));
	glDisableVertexAttribArray(sp->a("normal2"));
	glDisableVertexAttribArray(sp->a("texture"));

}