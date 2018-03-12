
    /**
     * @file NRE_VAO.hpp
     * @brief Declaration of Engine's GL's Object : VAO
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include "../../Generic/NRE_Type.hpp"
    #include "../BufferObject/IBO/IVBO/NRE_IVBO.hpp"
    #include "../BufferObject/IBO/ITBO/NRE_ITBO.hpp"

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
             * @class VAO
             * @brief GL's Object : Manage the storage of functions' call, like for VBO
             */
            class VAO {
                private:
                    GLuint id;

                public:
                    //## Constructor ##//
                    VAO();
                    VAO(bool const& generate);

                    //## Copy-Constructor ##//
                    VAO(VAO const& arr);

                    //## Convertor ##//

                    //## Deconstructor ##//
                    ~VAO();

                    //## Getter ##//
                    GLuint const& getID() const;

                    //## Setter ##//
                    void setID(GLuint const& id);

                    //## Methods ##//
                    void generateID();
                    void deleteID();
                    void reload();
                    void bind() const;
                    void unbind() const;
                    void access(NBO const& buffer, GLenum const& vertexType, bool const& enableVAA = true) const;

                    //## Access Operator ##//

                    //## Assignment Operator ##//

                    //## Shortcut Operator ##//

                    //## Arithmetic Operator ##//

                    //## Comparison Operator ##//

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
            };

            inline std::ostream& operator<<(std::ostream &stream, VAO const& arr) {
                stream << "(" << arr.getID() << ")";
                return stream;
            }

        };
    };
