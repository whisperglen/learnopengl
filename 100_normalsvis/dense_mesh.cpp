
#include "normals_vis.h"
#include "stb/stb_image.h"

#include <vector>

struct Vertex {
	float x, y, z;        // Position
	float nx, ny, nz;     // Normal
	float u, v;           // TexCoords
};

struct sample_data dense_mesh_sample(1, 1, 1, 1, 2);

static int dense_mesh_do_init()
{
	int resolution = 2000;
	float size = 10;


	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	float step = size / (float)resolution;
	float startX = -size / 2.0f; // Center the plane at 0,0,0
	float startZ = -size / 2.0f;

	// 1. Generate Vertices
	// We loop through rows (z) and columns (x)
	// Need resolution + 1 vertices to make 'resolution' number of cells
	for (int z = 0; z <= resolution; ++z) {
		for (int x = 0; x <= resolution; ++x) {
			Vertex v;

			// Position (X, 0, Z) - Flat plane initially
			v.x = startX + x * step;
			v.y = 0.0f;
			v.z = startZ + z * step;

			// Normal - Points straight up (0, 1, 0)
			v.nx = 0.0f;
			v.ny = 1.0f;
			v.nz = 0.0f;

			// Texture Coordinates (0.0 to 1.0)
			v.u = (float)x / (float)resolution;
			v.v = (float)z / (float)resolution;

			vertices.push_back(v);
		}
	}

	// 2. Generate Indices (Topology)
	// We create 2 triangles for every grid square
	for (int z = 0; z < resolution; ++z) {
		for (int x = 0; x < resolution; ++x) {
			// Calculate index of the vertex in the 1D array
			int currentRow = z * (resolution + 1);
			int nextRow = (z + 1) * (resolution + 1);

			// The indices of the 4 corners of the current quad
			int topLeft = currentRow + x;
			int topRight = topLeft + 1;
			int bottomLeft = nextRow + x;
			int bottomRight = bottomLeft + 1;

			// Triangle 1 (Bottom-Left, Top-Right, Top-Left)
			indices.push_back(bottomLeft);
			indices.push_back(topRight);
			indices.push_back(topLeft);

			// Triangle 2 (Bottom-Left, Bottom-Right, Top-Right)
			indices.push_back(bottomLeft);
			indices.push_back(bottomRight);
			indices.push_back(topRight);
		}
	}

	dense_mesh_sample.allocate();

	dense_mesh_sample.index_count = (int)indices.size();

	//textures
	//stbi_set_flip_vertically_on_load(true);

	//float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	//glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor); //use this for GL_CLAMP_TO_BORDER

	int width, height, nrChannels;
	unsigned char* data;
	data = stbi_load(".\\textures\\corvus_fit_normal_1.png", &width, &height, &nrChannels, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dense_mesh_sample.textures[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (nrChannels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	data = stbi_load(".\\textures\\corvus_fit.png", &width, &height, &nrChannels, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dense_mesh_sample.textures[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, (nrChannels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	//geometry

	glBindVertexArray(dense_mesh_sample.VAOs[0]);

	glBindBuffer(GL_ARRAY_BUFFER, dense_mesh_sample.VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dense_mesh_sample.EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, nx)));
	glEnableVertexAttribArray(1);
	// texture coords attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, u)));
	glEnableVertexAttribArray(2);

	programCompilation(RSRC("dense_mesh_vertex.glsl"), RSRC("dense_mesh_fragment.glsl"), dense_mesh_sample.programs[0]);

	glUseProgram(dense_mesh_sample.programs[0]);
	glUniform1i(glGetUniformLocation(dense_mesh_sample.programs[0], "texture1"), 1);
	//glUniform1i(glGetUniformLocation(dense_mesh_sample.programs[0], "texture2"), 1);

	glUniform1i(glGetUniformLocation(dense_mesh_sample.programs[0], "normalMap"), 0);

	glBindVertexArray(0);

	dense_mesh_sample.initialised = 1;

	return 0;
}

int dense_mesh()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (!dense_mesh_sample.initialised)
	{
		RET_ON_FAIL(dense_mesh_do_init());
	}

	glUseProgram(dense_mesh_sample.programs[0]);

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, -5));
	glm::mat4 viewMatrix = getViewMatrix();
	glm::mat4 projectionMatrix = getProjMatrix();
	glm::vec3 camPos = getCameraPosition();
	glm::vec3 lightPos = glm::vec3(0, 0, 5);

	glUniform1f(glGetUniformLocation(dense_mesh_sample.programs[0], "displacementStrength"), 0.5f);
	glUniformMatrix4fv(glGetUniformLocation(dense_mesh_sample.programs[0], "model"), 1, 0, (const GLfloat*) & modelMatrix);
	glUniformMatrix4fv(glGetUniformLocation(dense_mesh_sample.programs[0], "view"), 1, 0, (const GLfloat*) & viewMatrix);
	glUniformMatrix4fv(glGetUniformLocation(dense_mesh_sample.programs[0], "projection"), 1, 0, (const GLfloat*) & projectionMatrix);
	glUniform3fv(glGetUniformLocation(dense_mesh_sample.programs[0], "lightPos"), 1, (const GLfloat*) & lightPos);
	glUniform3fv(glGetUniformLocation(dense_mesh_sample.programs[0], "viewPos"), 1, (const GLfloat*) & camPos);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, dense_mesh_sample.textures[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, dense_mesh_sample.textures[1]);

	glBindVertexArray(dense_mesh_sample.VAOs[0]);
	glDrawElements(GL_TRIANGLES, dense_mesh_sample.index_count, GL_UNSIGNED_INT, 0);

	return 0;
}