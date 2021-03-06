
    #include "NRE_VertexBuffer.hpp"

    namespace NRE {
        namespace GL {

            GLint VertexBuffer::INDEX = 0;
            GLint VertexBuffer::SIZE = 3;

            VertexBuffer::VertexBuffer() {
            }

            VertexBuffer::VertexBuffer(bool const& generate) : ArrayBuffer::ArrayBuffer(generate) {
            }

            VertexBuffer::VertexBuffer(VertexBuffer && buf) : ArrayBuffer::ArrayBuffer(std::move(buf)) {
            }

            VertexBuffer::~VertexBuffer() {
            }

            GLint const VertexBuffer::getTypeSize() const {
                return sizeof(GLint);
            }

            GLint const VertexBuffer::getSize() const {
                return SIZE;
            }

            GLenum const VertexBuffer::getType() const {
                return GL_INT;
            }

            GLint const VertexBuffer::getIndex() const {
                return INDEX;
            }

            VertexBuffer& VertexBuffer::operator=(VertexBuffer && buf) {
                ArrayBuffer::operator=(std::move(buf));
                return *this;
            }

        };
    };
