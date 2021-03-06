#include "mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) : m_vVertices(vertices), m_vIndices(indices), m_vTextures(textures)
{
	int pointers[] = {3, 3, 2};
	m_nVAO = createVertexInfo(
		&m_vVertices[0], m_vVertices.size() * sizeof(Vertex), pointers,
		&m_vIndices[0], (int)(m_vIndices.size() * sizeof(GLuint)));
}

void Mesh::update(Controller *controller)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	for (GLuint i = 0; i < m_vTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		string number;
		string name = m_vTextures[i].type;
		if (name == "texture_diffuse")
			number = to_string(diffuseNr++);
		else if (name == "texutre_specular")
			number = to_string(specularNr++);

		controller->m_pShader->setFloat(("material." + name + number).c_str(), (float)i);
		glBindTexture(GL_TEXTURE_2D, m_vTextures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(m_nVAO);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_vIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
