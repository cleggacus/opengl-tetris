#pragma once

class IndexBuffer{
    private:
        unsigned int mRendererId;
        unsigned int mCount;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);
        ~IndexBuffer();

        void bind() const;
        void unBind() const;

        inline unsigned int getCount() const { return mCount; }
};