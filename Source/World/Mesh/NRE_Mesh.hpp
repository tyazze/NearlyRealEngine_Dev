
    /**
     * @file NRE_Mesh.hpp
     * @brief Declaration of Engine's World's Object : Mesh
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include "../Voxel/PackedVertex/NRE_PackedVertex.hpp"
    #include "../Chunk/NRE_Chunk.hpp"
    #include <vector>
    #include <unordered_map>

    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {
        /**
         * @namespace World
         * @brief Engine's Voxel's Type's Module
         */
        namespace World {

            /**
             * @class Mesh
             * @brief World's Object : Manage object's rendering while creating their mesh with optimization
             */
            class Mesh {
                private:
                    Chunk* target;
                    std::vector<GLint> vData;
                    std::vector<GLfloat> cData;
                    std::vector<GLbyte> nData;
                    std::vector<GLuint> iData;
                    std::unordered_map<NRE::Voxel::PackedVertex, size_t> map;

                public:
                    //## Constructor ##//
                    Mesh();
                    Mesh(Chunk* const& target);

                    //## Copy-Constructor ##//
                    Mesh(Mesh const& mesh);

                    //## Convertor ##//

                    //## Deconstructor ##//
                    ~Mesh();

                    //## Getter ##//
                    Chunk* const& getTarget() const;
                    std::vector<GLint> const& getVData() const;
                    std::vector<GLfloat> const& getCData() const;
                    std::vector<GLbyte> const& getNData() const;
                    std::vector<GLuint> const& getIData() const;
                    GLint* getVPointer();
                    GLfloat* getCPointer();
                    GLbyte* getNPointer();
                    GLuint* getIPointer();
                    std::unordered_map<NRE::Voxel::PackedVertex, size_t> const& getMap() const;

                    //## Setter ##//
                    void setTarget(Chunk* const& target);
                    void setVData(std::vector<GLint> const& data);
                    void setCData(std::vector<GLfloat> const& data);
                    void setNData(std::vector<GLbyte> const& data);
                    void setIData(std::vector<GLuint> const& data);
                    void setMap(std::unordered_map<NRE::Voxel::PackedVertex, size_t> const& map);

                    //## Methods ##//
                    void addVertex(Maths::Point3D<GLint> const& v);
                    void addColor(Color::RGB const& c);
                    void addNormal(Maths::Vector3D<GLbyte> const& n);
                    void addIndex(GLuint const& index);
                    void constructMesh();
                    void addVoxel(Maths::Point3D<GLuint> const& voxCoord, Maths::Point3D<GLint> const& realCoord, bool const (&face)[6]);
                    void addPackedVertex(Maths::Point3D<GLint> const (&p)[4], Color::RGB const& voxColor, GLuint const& face, size_t const& cCode);
                    bool const getSimilarVertexIndex(NRE::Voxel::PackedVertex const& packed, std::unordered_map<NRE::Voxel::PackedVertex, size_t> const& map, GLuint &result) const;

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