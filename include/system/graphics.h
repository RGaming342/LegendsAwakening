#pragma once

#include <iostream>
#include <sstream>
#include <SDL2/SDL_image.h>
#include "glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <unordered_map>




enum class RenderType{
	STATIC,
	DYNAMIC
};
enum class DrawType{
	TRIANGLE,
	TRIANGLE_STRIP,
	TRIANGLE_FAN,
	LINE,
	LINE_STRIP,
	LINE_LOOP,
	POINT,
	QUAD,
	POLYGON
};
class RenderObj{
	public:
		RenderObj(DrawType type);
		~RenderObj();
		
		void draw();
		void setInput(int index,int bufID,int VertexSize,int SegCount,int offset,bool isInt,RenderType renderType);
		void setData(int bufID,const std::vector<unsigned int>& data);
		void setData(int bufID,const std::vector<float>& data);
		
	private:
		struct BufObj{ GLuint ID; GLenum type; bool isInt; unsigned int size; };
		std::unordered_map<int,BufObj> buffers;
		GLuint VertexArray;
		GLuint drawtype;
};


class Shader{
	public:
		Shader() = default;
		~Shader();
		
		bool load(const std::string& vertexPath, const std::string& fragmentPath);
		void unload();
		void use();
		
		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setFloat(const std::string& name, float value) const;
		void setVec2(const std::string& name, const glm::vec3& value) const;
		void setVec3(const std::string& name, const glm::vec3& value) const;
		void setMat4(const std::string& name, const glm::mat4& value) const;
		void setBoolArray(const std::string& name, const bool* value, size_t count) const;
		void setIntArray(const std::string& name, const int* value, size_t count) const;
		void setFloatArray(const std::string& name, const float* value, size_t count) const;
		void setVec2Array(const std::string& name, const glm::vec2* value, size_t count) const;
		void setVec3Array(const std::string& name, const glm::vec3* value, size_t count) const;
		void setMat4Array(const std::string& name, const glm::mat4* value, size_t count) const;
	private:
		unsigned int programID;
		std::string loadShaderSource(const std::string& path) const;
		unsigned int compileShader(const std::string& source, GLenum shaderType);
		void checkCompileErrors(unsigned int& shader, const std::string& type);
};

class Texture{
	public:
		const int pixel = GL_NEAREST;
		const int blend = GL_LINEAR;
		
		Texture() = default;
		Texture(Texture&& other) noexcept : texture(other.texture) {
			other.texture = 0;
		}
		Texture& operator=(Texture&& other) noexcept {
			if (this != &other) {
				texture = other.texture;
				other.texture = 0;
			}
			return *this;
		}
		~Texture();
		
		int load(std::string);
		void unload();
		void bind();
		void unbind();
		void setNearFilter(int filter);
		void setFarFilter(int filter);
		glm::ivec2 getSize();
		GLuint getRaw();
		void setRaw(GLuint);
	private:
		unsigned int texture;
		int width = -1;
		int height = -1;
};



