#include "ModelCtrl.h"

ModelCtrl::ModelCtrl(float x, float y, float z) {
    this->ModelPosition = glm::mat4(1.0f);
    this->ModelPosition = glm::translate(this->ModelPosition, glm::vec3(x, y, z));
    this->ModelPosition = glm::scale(this->ModelPosition, glm::vec3(0.6, 0.6, 0.6));
}

void ModelCtrl::loadModel(const std::string &path){
	Assimp::Importer importer;
    this->path = path;
    const aiScene* scene = importer.ReadFile(this->path,
        aiProcess_Triangulate |
        aiProcess_FlipUVs);
    processNode(scene->mRootNode, scene);
    setupForLLD(1.0f,0.0f,0.0f,1.0f);
}
void ModelCtrl::processNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->meshes.push_back(processMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene);
    }

}
Mesh ModelCtrl::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;

        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    std::cout << "mesh set" << std::endl;
    return Mesh(vertices, indices, textures);
}

void ModelCtrl::setupForLLD(float colR, float colG, float colB, float colAlpha) {
    //z wektora siatek iterujemy po kolejnych siatkach
    for  (int i = 0;  i < this->meshes.size(); i++){
        Mesh temp = this->meshes[i];
        //dla ka¿dej siatki iterujemy po wszystkich wierzcho³kach wchodz¹cych w jej sk³ad
        for (int k = 0; k < temp.vertices.size(); k++){
            //przepisujemy koordynaty z ka¿dego wierzcho³ka
            for (int j = 0; j < 3; j++)
            {
               this->verticesLLD.push_back(temp.vertices[k].Position[j]);
               this->normalsLLD.push_back(temp.vertices[k].Normal[j]);
            }
            this->verticesLLD.push_back(1.0f);
            this->normalsLLD.push_back(0.0f);
            //przepisujemy koordynaty tekstur
            for (int j = 0; j < 2; j++) {
                this->texCordsLLD.push_back(temp.vertices[k].TexCoords[j]);
            }
        }
    }
    this->vertexCount = verticesLLD.size() / 4;
    for (int i = 0; i < vertexCount; i++) {
        this->colorLLD.push_back(colR);
        this->colorLLD.push_back(colG);
        this->colorLLD.push_back(colB);
        this->colorLLD.push_back(colAlpha);
    }
    std::cout << "reload done" << std::endl;
}

void ModelCtrl::drawLLD(GLuint* texture) {

    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(this->ModelPosition));
        
    float* vertexLLD = &this->verticesLLD[0];
    float* normalLLD = &this->normalsLLD[0];
    float* texCordLLD = &this->texCordsLLD[0];
    float* colorLLD = &this->colorLLD[0];

    sp->use();
    glEnableVertexAttribArray(sp->a("vertex"));
    glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, vertexLLD);
    glEnableVertexAttribArray(sp->a("normal"));
    glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, normalLLD);
    glEnableVertexAttribArray(sp->a("texture"));
    glVertexAttribPointer(sp->a("texture"), 2, GL_FLOAT, false, 0, texCordLLD);

    glUniform1i(sp->u("tex"), 4);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, *texture);
    
    glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("normal"));
    glDisableVertexAttribArray(sp->a("texture"));
}




