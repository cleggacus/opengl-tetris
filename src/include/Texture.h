#pragma once

#include "Renderer.h"

class Texture{
    private:
        unsigned int mRendererId;
        string mFilePath;
        unsigned char* mLocalBuffer;
        int mWidth, mHeight, mBPP;
    public:
        Texture(const string& path);
        ~Texture();

        void bind(unsigned int slot = 0) const;
        void unBind() const;

        inline int getWidth() const {return mWidth;};
        inline int getHeight() const {return mHeight;};
};