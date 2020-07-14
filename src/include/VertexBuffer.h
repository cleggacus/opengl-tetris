#pragma once

class VertexBuffer{
    private:
        unsigned int mRendererId;
    public:
        VertexBuffer(const void* data, unsigned int size, const bool isStatic = false);
        ~VertexBuffer();

        void bind() const;
        void unBind() const;
        void populateData(const void* data, unsigned int size, unsigned int offset = 0);
};