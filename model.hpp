#define GLM_FORCE_RADIANS

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include "shaderprogram.h"
#include "lodepng.h"
#include <vector>

const float PI = 3.1415;

class Mesh{
private:
  std::vector<glm::vec4> verts; // vertices
  std::vector<glm::vec4> norms; // normal vectors
  std::vector<glm::vec2> texCoords; // texturing coordinates
  std::vector<unsigned int> indices; // indices to draw correct triangles
  std::vector<glm::vec4> tangents; // przestrzeń styczna (for normal mapping)
public:
  Mesh(const aiScene* scene, int nr);
  void draw(GLFWwindow* window, glm::mat4 V, glm::mat4 P, glm::mat4 M, std::vector<GLuint> textures);
  void draw_part(GLFWwindow* window, glm::mat4 V, glm::mat4 P, glm::mat4 M, GLuint texture);
};

class Model{
private:
  std::vector<Mesh> meshes;
  std::vector<GLuint> textures;
  void load(const std::string& filename); // load from obj file
  bool whole; // whole - multiple textures for all meshes, not whole - one texture for each mesh
public:
  Model(){};
  Model(const std::string& obj_filename, bool _whole);
  void draw(GLFWwindow* window,float angle_x,float angle_y, glm::vec3 position, glm::mat4 V, glm::vec3 scale); //shader musi już istnieć
  void readTexture(const char* filename); // read texture from png file
  void readTextures(std::vector<const char*> filenames); // read all needed textures
};
