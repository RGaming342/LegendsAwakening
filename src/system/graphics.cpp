#include "../../include/system/graphics.h"
#include "../../include/system/file.h"

RenderObj::RenderObj(DrawType type){
	glGenVertexArrays(1, &VertexArray);
	switch(type){
		case DrawType::LINE:      { drawtype = GL_LINES; }break;
		case DrawType::LINE_LOOP: { drawtype = GL_LINE_LOOP; }break;
		case DrawType::LINE_STRIP:{ drawtype = GL_LINE_STRIP; }break;
		case DrawType::POINT:     { drawtype = GL_POINTS; }break;
		case DrawType::POLYGON:   { drawtype = GL_POLYGON; }break;
		case DrawType::QUAD:      { drawtype = GL_QUADS; }break;
		case DrawType::TRIANGLE:  { drawtype = GL_TRIANGLES; }break;
		case DrawType::TRIANGLE_FAN:{ drawtype = GL_TRIANGLE_FAN; }break;
		case DrawType::TRIANGLE_STRIP:{ drawtype = GL_TRIANGLE_STRIP; }break;
	};
}
RenderObj::~RenderObj(){
	for (const auto& pair : buffers) {
		if(pair.second.ID){
			glDeleteBuffers(1, &pair.second.ID);
		}
	}
	glDeleteVertexArrays(1, &VertexArray);
}

void RenderObj::draw(){
	glBindVertexArray(VertexArray);
	unsigned int size = 0;
	for (const auto& pair : buffers) {
		size = pair.second.size;
		break;
	}
	glDrawArrays(drawtype, 0, size);
	glBindVertexArray(0);
}
void RenderObj::setInput(int index,int bufID,int VertexSize,int SegCount,int offset,bool isInt,RenderType renderType){
	glBindVertexArray(VertexArray);
	if (buffers.find(bufID) == buffers.end()) {
		glGenBuffers(1, &buffers[bufID].ID);
		buffers[bufID].isInt = isInt;
		switch(renderType){
			case RenderType::DYNAMIC:{ buffers[bufID].type = GL_DYNAMIC_DRAW; }break;
			case RenderType::STATIC :{ buffers[bufID].type = GL_STATIC_DRAW; }break;
		};
	}
	glBindBuffer(GL_ARRAY_BUFFER, buffers[bufID].ID);
	glEnableVertexAttribArray(index);
	if (isInt) {
		glVertexAttribIPointer(index, SegCount, GL_UNSIGNED_INT, sizeof(unsigned int)*VertexSize, (const void*)(offset*sizeof(float)));
	} else {
		glVertexAttribPointer(index, SegCount, GL_FLOAT, GL_FALSE, sizeof(float)*VertexSize, (const void*)(offset*sizeof(float)));
	}
	glBindVertexArray(0);
}
void RenderObj::setData(int bufID,const std::vector<unsigned int>& data){
	glBindBuffer(GL_ARRAY_BUFFER, buffers[bufID].ID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), buffers[bufID].type);
	buffers[bufID].size = data.size();
}
void RenderObj::setData(int bufID,const std::vector<float>& data){
	glBindBuffer(GL_ARRAY_BUFFER, buffers[bufID].ID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), buffers[bufID].type);
	buffers[bufID].size = data.size();
}








Shader::~Shader(){ glDeleteProgram(programID); }
bool Shader::load(const std::string& vertexPath, const std::string& fragmentPath) {
	// Load the vertex and fragment shader code
	std::string vertexCode = loadShaderSource(vertexPath);
	std::string fragmentCode = loadShaderSource(fragmentPath);
	
	if (vertexCode.empty() || fragmentCode.empty()) {
		return true;
	}
	
	unsigned int vertexShader = compileShader(vertexCode, GL_VERTEX_SHADER);
	unsigned int fragmentShader = compileShader(fragmentCode, GL_FRAGMENT_SHADER);
	
	if (!vertexShader || !fragmentShader) {
		return true;
	}
	
	programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);
	
	checkCompileErrors(programID, "PROGRAM");
	
	if (!programID) {
		return true;
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	return false;
}
void Shader::unload() {
	glDeleteProgram(programID);
}
void Shader::use() {
	glUseProgram(programID);
}
void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}
void Shader::setVec2(const std::string& name, const glm::vec3& value) const {
	glUniform2fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setVec3(const std::string& name, const glm::vec3& value) const {
	glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
}
void Shader::setMat4(const std::string& name, const glm::mat4& value) const {
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
void Shader::setBoolArray(const std::string& name, const bool* value, size_t count) const {
	glUniform1iv(glGetUniformLocation(programID, name.c_str()), count, reinterpret_cast<const GLint*>(value));
}
void Shader::setIntArray(const std::string& name, const int* value, size_t count) const {
	glUniform1iv(glGetUniformLocation(programID, name.c_str()), count, value);
}
void Shader::setFloatArray(const std::string& name, const float* value, size_t count) const {
	glUniform1fv(glGetUniformLocation(programID, name.c_str()), count, value);
}
void Shader::setVec2Array(const std::string& name, const glm::vec2* value, size_t count) const {
	glUniform2fv(glGetUniformLocation(programID, name.c_str()), count, glm::value_ptr(value[0]));
}
void Shader::setVec3Array(const std::string& name, const glm::vec3* value, size_t count) const {
	glUniform3fv(glGetUniformLocation(programID, name.c_str()), count, glm::value_ptr(value[0]));
}
void Shader::setMat4Array(const std::string& name, const glm::mat4* value, size_t count) const {
	glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), count, GL_FALSE, glm::value_ptr(value[0]));
}
std::string Shader::loadShaderSource(const std::string& path) const {
	File shaderFile;
	shaderFile.open(path,"r");
	if (shaderFile.Err()) {
		std::cerr << "ERROR: Shader file " << path << " not found!" << std::endl;
		return "";
	}
	return shaderFile.readAll();
}
unsigned int Shader::compileShader(const std::string& source, GLenum shaderType) {
	unsigned int shader = glCreateShader(shaderType);
	const char* shaderSource = source.c_str();
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	
	checkCompileErrors(shader, shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
	
	return shader;
}
void Shader::checkCompileErrors(unsigned int& shader, const std::string& type) {
	int success;
	char infoLog[1024];
	
	if (type != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "ERROR: Shader compilation failed for " << type << " shader\n" << infoLog << std::endl;
			shader = 0;
		}
	} else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cerr << "ERROR: Program linking failed\n" << infoLog << std::endl;
			shader = 0;
		}
	}
}



Texture::~Texture(){ unload(); }
int Texture::load(std::string filename){
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (!surface) {
		return 1;
	}
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	width = surface->w;
	height = surface->h;
	
	SDL_FreeSurface(surface);
	return 0;
}
void Texture::unload(){
	if (texture != 0) {
		glDeleteTextures(1, &texture);
		texture = 0;
		width = -1;
		height = -1;
	}
}
void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D, texture);
}
void Texture::unbind(){
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::setNearFilter(int filter){
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
}
void Texture::setFarFilter(int filter){
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}
glm::ivec2 Texture::getSize(){
	return glm::ivec2(width,height);
}
GLuint Texture::getRaw(){
	return texture;
}
void Texture::setRaw(GLuint tx){
	GLint Width, Height;
	glBindTexture(GL_TEXTURE_2D, tx);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	texture = tx;
	width = Width;
	height = Height;
}



