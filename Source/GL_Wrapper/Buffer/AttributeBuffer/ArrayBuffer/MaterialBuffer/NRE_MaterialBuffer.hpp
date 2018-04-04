
    /**
     * @file NRE_VertexBuffer.hpp
     * @brief Declaration of Engine's GL's Object : MaterialBuffer
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include "../NRE_ArrayBuffer.hpp"

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
             * @class MaterialBuffer
             * @brief GL's Object : A specialized ArrayBuffer for vertex material id managing
             */
            class MaterialBuffer : public ArrayBuffer {
                private:

                public:
                    //## Constructor ##//
                    MaterialBuffer();
                    MaterialBuffer(bool const& generate);

                    //## Copy-Constructor ##//
                    MaterialBuffer(MaterialBuffer const& buf);

                    //## Convertor ##//

                    //## Deconstructor ##//
                    ~MaterialBuffer();

                    //## Getter ##//
                    GLint const getTypeSize() const;
                    GLint const getSize() const;
                    GLenum const getType() const;
                    GLint const getIndex() const;

                    //## Setter ##//

                    //## Methods ##//

                    //## Access Operator ##//

                    //## Assignment Operator ##//

                    //## Shortcut Operator ##//

                    //## Arithmetic Operator ##//

                    //## Comparison Operator ##//

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
                    static GLint INDEX;
                    static GLenum TYPE;
                    static GLint TYPESIZE;
                    static GLint SIZE;
            };

        };
    };