
    /**
     * @file NRE_IndexBuffer.hpp
     * @brief Declaration of Engine's GL's Object : IndexBuffer
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include "../NRE_Buffer.hpp"
    #include "../../../../Generic/NRE_Type.hpp"

    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {
        /**
         * @namespace GL
         * @brief Engine's OpenGL's Wrapper's Module
         */
        namespace GL {

            /**
             * @class IndexBuffer
             * @brief GL's Object : A specialized buffer for Index
             */
            class IndexBuffer : public Buffer {
                private:

                public:
                    //## Constructor ##//
                    IndexBuffer();
                    IndexBuffer(bool const& generate);

                    //## Copy-Constructor ##//

                    //## Convertor ##//

                    //## Deconstructor ##//
                    ~IndexBuffer();

                    //## Getter ##//

                    //## Setter ##//

                    //## Methods ##//
                    void generateID() override;
                    void deleteID() override;
                    void reload() override;
                    void allocate(GLsizeiptr const& size, GLenum const& usage, GLenum const& target = GL_ELEMENT_ARRAY_BUFFER) override;
                    void update(GLintptr const& offset, GLsizeiptr const& size, GLvoid* const& data, GLenum const& target = GL_ELEMENT_ARRAY_BUFFER) override;
                    void bind(GLenum const& target = GL_ELEMENT_ARRAY_BUFFER) const override;
                    void unbind(GLenum const& target = GL_ELEMENT_ARRAY_BUFFER) const override;

                    //## Access Operator ##//

                    //## Assignment Operator ##//

                    //## Shortcut Operator ##//

                    //## Arithmetic Operator ##//

                    //## Comparison Operator ##//

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
            };

        };
    };