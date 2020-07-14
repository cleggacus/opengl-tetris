#include "include/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const string& path) : mFilePath(path), mLocalBuffer(nullptr), mWidth(0), mHeight(0), mBPP(0){
    stbi_set_flip_vertically_on_load(1);
    mLocalBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);

    if(mLocalBuffer == nullptr){
        cout<< "Error: [stb_image] cant load texture from file: " + path << "\n";
    }

    glCall(glGenTextures(1, &mRendererId));
    glCall(glBindTexture(GL_TEXTURE_2D, mRendererId));

    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mLocalBuffer));
    glCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(mLocalBuffer)
        stbi_image_free(mLocalBuffer);
}

Texture::~Texture(){
    glCall(glDeleteTextures(1, &mRendererId));
}

void Texture::bind(unsigned int slot) const{
    glCall(glActiveTexture(GL_TEXTURE0 + slot));
    glCall(glBindTexture(GL_TEXTURE_2D, mRendererId));
}

void Texture::unBind() const{
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}