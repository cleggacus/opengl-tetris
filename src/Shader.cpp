#include "include/Shader.h"
#include "include/Renderer.h"

#include <GL/glew.h>
#include <fstream> 
#include <sstream> 

Shader::Shader(const string& filepath) : mFilePath(filepath), mRendererId(0){
    ShaderProgramSource source = parseShader(filepath);
    mRendererId = createShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader(){
    glCall(glDeleteProgram(mRendererId));
}

int Shader::getUniformLocation(const string& name){
    if(mUniformLocationCache.find(name) != mUniformLocationCache.end())
        return mUniformLocationCache[name];

    glCall(int location = glGetUniformLocation(mRendererId, name.c_str()));

    if(location == -1)
        cout << "Warning : uniform " << name << " doesnt exist\n";
    
    mUniformLocationCache[name] = location;

    return location;
}

void Shader::bind() const{
    glCall(glUseProgram(mRendererId));
}

void Shader::unBind() const{
    glCall(glUseProgram(0));
}

void Shader::setUniform4f(const string& name, float v0, float v1, float v2, float v3){
    glCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const string& name, const glm::mat4& matrix){
    glCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

void Shader::setUniform1i(const string& name, int value){
    glCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1iv(const string& name, int values[]){
    glCall(glUniform1iv(getUniformLocation(name), sizeof(values)/sizeof(values[0]), values));
}

void Shader::setUniform1f(const string& name, float value){
    glCall(glUniform1f(getUniformLocation(name), value));
}

ShaderProgramSource Shader::parseShader(const string& filepath){
    ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    string line;
    stringstream ss[2];

    ShaderType type = ShaderType::NONE;

    while(getline(stream, line)){
        if(line.find("#shader") != string::npos){
            if(line.find("vertex") != string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != string::npos)
                type = ShaderType::FRAGMENT;
        }else{
            ss[(int)type] << line << "\n";
        }
    }

    return {
        ss[0].str(),
        ss[1].str()
    };
}

unsigned int Shader::compileShader(unsigned int type, const string& source){
    glCall(unsigned int id = glCreateShader(type));
    const char* src = source.c_str();
    glCall(glShaderSource(id, 1, &src, nullptr));
    glCall(glCompileShader(id));

    int result;
    glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if(result == GL_FALSE){
        int length;
        glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        glCall(glGetShaderInfoLog(id, length, &length, message));
        cout << message << "\n";
        glCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

unsigned int Shader::createShader(const string& vertexShader, const string& fragmentShader){
    glCall(unsigned int program = glCreateProgram());
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glCall(glAttachShader(program, vs));
    glAttachShader(program, fs);

    glCall(glLinkProgram(program));
    glCall(glValidateProgram(program));

    glCall(glDeleteShader(vs));
    glCall(glDeleteShader(fs));

    return program;
}