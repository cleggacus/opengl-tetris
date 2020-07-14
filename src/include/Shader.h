#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "../vendor/glm/glm.hpp"

using namespace std;

struct ShaderProgramSource{
    string VertexSource;
    string FragmentSource;
};

class Shader{
    private:
        string mFilePath;
        unordered_map<string, int> mUniformLocationCache;
        unsigned int mRendererId;
        ShaderProgramSource parseShader(const string& filepath);
        int getUniformLocation(const string& name);
        unsigned int compileShader(unsigned int type, const string& source);
        unsigned int createShader(const string& vertexShader, const string& fragmentShader);
    public:
        Shader(const string& filepath);
        ~Shader();

        void bind() const;
        void unBind() const;

        void setUniform4f(const string& name, float v0, float v1, float v2, float v3);
        void setUniformMat4f(const string& name, const glm::mat4& matrix);
        void setUniform1i(const string& name, int value);
        void setUniform1iv(const string& name, int values[]);
        void setUniform1f(const string& name, float value);
};