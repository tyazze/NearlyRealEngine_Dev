
    #include "NRE_IBO.hpp"

    namespace NRE {
        namespace GL {

            IBO::IBO() {
            }

            IBO::IBO(bool const& generate) : VBO::VBO(generate) {
                if (generate) {
                    generateID();
                }
            }

            IBO::IBO(IBO const& buf) : VBO::VBO(buf), index(buf.getIndexBuffer()) {
            }

            IBO::~IBO() {
                index.deleteID();
            }

            IndexBuffer const& IBO::getIndexBuffer() const {
                return index;
            }

            void IBO::setIndexBuffer(IndexBuffer const& buf) {
                index = buf;
            }

            void IBO::generateID() {
                VBO::generateID();
                index.generateID();
            }

            void IBO::deleteID() {
                index.deleteID();
                VBO::deleteID();
            }

            void IBO::reload() {
                VBO::reload();
                index.reload();
            }

            void IBO::allocate(size_t const& typeSize, size_t const& nbVertex, size_t const& nbIndex, GLenum const& usage) {
                index.allocate(IndexBuffer::SIZE * nbIndex, usage);
                VBO::allocate(typeSize, nbVertex, usage);
            }

            void IBO::update(GLintptr const& offset, size_t const& typeSize, size_t const& nbVertex, size_t const& nbIndex, GLvoid* const& vData, GLvoid* const& cData, GLvoid* const& nData, GLvoid* const& iData) {
                index.update(offset, IndexBuffer::SIZE * nbIndex, iData);
                VBO::update(offset, typeSize, nbVertex, vData, cData, nData);
            }

            void IBO::allocateAndFill(size_t typeSize, size_t const& nbVertex, size_t const& nbIndex, GLenum const& usage, GLvoid* const& vData, GLvoid* const& cData, GLvoid* const& nData, GLvoid* const& iData) {
                index.allocateAndFill(IndexBuffer::SIZE * nbIndex, usage, iData);
                VBO::allocateAndFill(typeSize, nbVertex, usage, vData, cData, nData);
            }

            void IBO::access(GLenum const& vertexType, bool const& enableVAA) const {
                VBO::access(vertexType, enableVAA);
                getIndexBuffer().bind();
                    glVertexAttribPointer(3, 3, IndexBuffer::TYPE, GL_FALSE, 0, 0);
                    if (enableVAA) {
                        glEnableVertexAttribArray(3);
                    }
                getIndexBuffer().unbind();
            }

        };
    };