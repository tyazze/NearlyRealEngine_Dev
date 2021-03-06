
    #include "NRE_Mesh.hpp"

    namespace NRE {
        namespace World {

            Mesh::Mesh() : Mesh(0) {
            }

            Mesh::Mesh(Chunk* const& target) : target(target) {
            }

            Mesh::Mesh(Mesh && mesh) : target(std::move(mesh.getTarget())), vData(std::move(mesh.getVData())), mData(std::move(mesh.getMData())), nData(std::move(mesh.getNData())), iData(std::move(mesh.getIData())) {
            }

            Mesh::~Mesh() {
            }

            Chunk* const& Mesh::getTarget() const {
                return target;
            }

            std::vector<GLint> const& Mesh::getVData() const {
                return vData;
            }

            std::vector<GLubyte> const& Mesh::getMData() const {
                return mData;
            }

            std::vector<GLbyte> const& Mesh::getNData() const {
                return nData;
            }

            std::vector<GLuint> const& Mesh::getIData() const {
                return iData;
            }

            GLint* Mesh::getVPointer() {
                return &vData.front();
            }

            GLubyte* Mesh::getMPointer() {
                return &mData.front();
            }

            GLbyte* Mesh::getNPointer() {
                return &nData.front();
            }

            GLuint* Mesh::getIPointer() {
                return &iData.front();
            }

            void Mesh::addVertex(Maths::Point3D<GLint> const& v) {
                vData.push_back(v.getX());
                vData.push_back(v.getY());
                vData.push_back(v.getZ());
            }

            void Mesh::addMaterialID(GLubyte const& id) {
                mData.push_back(id);
            }

            void Mesh::addNormal(Maths::Vector3D<GLbyte> const& n) {
                nData.push_back(n.getX());
                nData.push_back(n.getY());
                nData.push_back(n.getZ());
            }

            void Mesh::addIndex(GLuint const& index) {
                iData.push_back(index);
            }

            void Mesh::constructMesh(World* w) {
                GLuint index;
                bool face[FACE_NUM];

                w->resetVoxelMergingGlobalCache();

                for (unsigned int x = 0; x < Chunk::SIZE_X; x = x + 1) {
                    for (unsigned int y = 0; y < Chunk::SIZE_Y; y = y + 1) {
                        for (unsigned int z = 0; z < getTarget()->getMaxSolidHeight() + 1; z = z + 1) {
                            index = getVoxelIndex(x, y, z);
                            if (getTarget()->getVoxel(index).getType() != VOID) {
                                face[XNegative] = checkVoxelXNegativeFace(w, x, y, z);
                                face[XPositive] = checkVoxelXPositiveFace(w, x, y, z);
                                face[YNegative] = checkVoxelYNegativeFace(w, x, y, z);
                                face[YPositive] = checkVoxelYPositiveFace(w, x, y, z);
                                face[ZNegative] = checkVoxelZNegativeFace(w, x, y, z);
                                face[ZPositive] = checkVoxelZPositiveFace(w, x, y, z);

                                addVoxel(w, x, y, z, x + target->getCoord().getX() * Chunk::SIZE_X, y + target->getCoord().getY() * Chunk::SIZE_Y, z, face);
                            }
                        }
                    }
                }
            }

            void Mesh::addVoxel(World* w, GLuint const& x, GLuint const& y, GLuint const& z, GLint const& rX, GLint const& rY, GLint const& rZ, bool const (&face)[6]) {
                Maths::Point3D<GLint> p[4];

                if (face[XNegative]) {
                    if (!w->getVoxelMergingFace(x, y, z, XNegative)) {

                        p[0] = {rX, rY, rZ};
                        p[1] = {rX, rY + 1, rZ};
                        p[2] = {rX, rY, rZ + 1};
                        p[3] = {rX, rY + 1, rZ + 1};

                        mergeVoxels(w, x, y, z, getTarget()->getVoxel(x, y, z).getType(), p, XNegative);
                        addPackedVertex(p, XNegative, static_cast <size_t> (target->getVoxel(x, y, z).getType()));
                    }
                }

                if (face[YNegative]) {
                    if (!w->getVoxelMergingFace(x, y, z, YNegative)) {
                        p[0] = {rX + 1, rY, rZ};
                        p[1] = {rX, rY, rZ};
                        p[2] = {rX + 1, rY, rZ + 1};
                        p[3] = {rX, rY, rZ + 1};

                        mergeVoxels(w, x, y, z, getTarget()->getVoxel(x, y, z).getType(), p, YNegative);
                        addPackedVertex(p, YNegative, static_cast <size_t> (target->getVoxel(x, y, z).getType()));
                    }
                }

                if (face[ZNegative]) {
                    if (!w->getVoxelMergingFace(x, y, z, ZNegative)) {
                        p[0] = {rX, rY, rZ};
                        p[1] = {rX + 1, rY, rZ};
                        p[2] = {rX, rY + 1, rZ};
                        p[3] = {rX + 1, rY + 1, rZ};

                        mergeVoxels(w, x, y, z, getTarget()->getVoxel(x, y, z).getType(), p, ZNegative);
                        addPackedVertex(p, ZNegative, static_cast <size_t> (target->getVoxel(x, y, z).getType()));
                    }
                }

                if (face[XPositive]) {
                    if (!w->getVoxelMergingFace(x, y, z, XPositive)) {
                        p[0] = {rX + 1, rY + 1, rZ};
                        p[1] = {rX + 1, rY, rZ};
                        p[2] = {rX + 1, rY + 1, rZ + 1};
                        p[3] = {rX + 1, rY, rZ + 1};

                        mergeVoxels(w, x, y, z, getTarget()->getVoxel(x, y, z).getType(), p, XPositive);
                        addPackedVertex(p, XPositive, static_cast <size_t> (target->getVoxel(x, y, z).getType()));
                    }
                }

                if (face[YPositive]) {
                    if (!w->getVoxelMergingFace(x, y, z, YPositive)) {
                        p[0] = {rX, rY + 1, rZ};
                        p[1] = {rX + 1, rY + 1, rZ};
                        p[2] = {rX,  rY + 1, rZ + 1};
                        p[3] = {rX + 1, rY + 1, rZ + 1};

                        mergeVoxels(w, x, y, z, getTarget()->getVoxel(x, y, z).getType(), p, YPositive);
                        addPackedVertex(p, YPositive, static_cast <size_t> (target->getVoxel(x, y, z).getType()));
                    }
                }

                if (face[ZPositive]) {
                    if (!w->getVoxelMergingFace(x, y, z, ZPositive)) {
                        p[0] = {rX + 1, rY, rZ + 1};
                        p[1] = {rX, rY, rZ + 1};
                        p[2] = {rX + 1, rY + 1, rZ + 1};
                        p[3] = {rX, rY + 1, rZ + 1};

                        mergeVoxels(w, x, y, z, getTarget()->getVoxel(x, y, z).getType(), p, ZPositive);
                        addPackedVertex(p, ZPositive, static_cast <size_t> (target->getVoxel(x, y, z).getType()));
                    }
                }
            }


            void Mesh::mergeVoxels(World* w, GLuint x, GLuint y, GLuint z, GLint const& type, Maths::Point3D<GLint> (&p)[4], int const& face) {
                GLuint index = 0;
                bool axe1More, axe2More;
                GLuint axe1Size = 1, axe2Size = 0, axe1Cpy, *axe1, *axe2, limit1, limit2;
                Maths::Point3D<GLint> *p1, *p2, *p3, *p4;
                auto setAxe1 = &Maths::Point3D<GLint>::setZ<GLint>;
                auto setAxe2 = &Maths::Point3D<GLint>::setZ<GLint>;
                auto getAxe1 = &Maths::Point3D<GLint>::getZ;
                auto getAxe2 = &Maths::Point3D<GLint>::getZ;
                auto checkFace = &Mesh::checkVoxelXNegativeFace;

                if (face == XNegative || face == XPositive) {
                    axe1 = &y, axe2 = &z; axe1Cpy = y;
                    limit1 = Chunk::SIZE_Y; limit2 = Chunk::SIZE_Z;
                    setAxe1 = &Maths::Point3D<GLint>::setY<GLint>;
                    setAxe2 = &Maths::Point3D<GLint>::setZ<GLint>;
                    getAxe1 = &Maths::Point3D<GLint>::getY;
                    getAxe2 = &Maths::Point3D<GLint>::getZ;
                    if (face == XNegative) {
                       p1 = &p[1]; p2 = &p[3], p3 = &p[2]; p4 = &p[3];
                       checkFace = &Mesh::checkVoxelXNegativeFace;
                    } else {
                       p1 = &p[0]; p2 = &p[2], p3 = &p[2]; p4 = &p[3];
                       checkFace = &Mesh::checkVoxelXPositiveFace;
                    }
                }
                if (face == YNegative || face == YPositive) {
                    axe1 = &x; axe2 = &z; axe1Cpy = x;
                    limit1 = Chunk::SIZE_X; limit2 = Chunk::SIZE_Z;
                    setAxe1 = &Maths::Point3D<GLint>::setX<GLint>;
                    setAxe2 = &Maths::Point3D<GLint>::setZ<GLint>;
                    getAxe1 = &Maths::Point3D<GLint>::getX;
                    getAxe2 = &Maths::Point3D<GLint>::getZ;
                    if (face == YNegative) {
                        p1 = &p[0]; p2 = &p[2], p3 = &p[2]; p4 = &p[3];
                        checkFace = &Mesh::checkVoxelYNegativeFace;
                    } else {
                        p1 = &p[1]; p2 = &p[3]; p3 = &p[2]; p4 = &p[3];
                        checkFace = &Mesh::checkVoxelYPositiveFace;
                    }
                }
                if (face == ZNegative || face == ZPositive) {
                    axe1 = &x, axe2 = &y; axe1Cpy = x;
                    limit1 = Chunk::SIZE_X; limit2 = Chunk::SIZE_Y;
                    setAxe1 = &Maths::Point3D<GLint>::setX<GLint>;
                    setAxe2 = &Maths::Point3D<GLint>::setY<GLint>;
                    getAxe1 = &Maths::Point3D<GLint>::getX;
                    getAxe2 = &Maths::Point3D<GLint>::getY;
                    if (face == ZNegative) {
                       p1 = &p[1]; p2 = &p[3], p3 = &p[2]; p4 = &p[3];
                       checkFace = &Mesh::checkVoxelZNegativeFace;
                    } else {
                       p1 = &p[0]; p2 = &p[2], p3 = &p[2]; p4 = &p[3];
                       checkFace = &Mesh::checkVoxelZPositiveFace;
                    }
                }

                index = getVoxelIndex(x, y, z);
                w->setVoxelMergingFace(x, y, z, face, true);
                axe1More = !(*axe1 == limit1 - 1);
                *axe1 = *axe1 + 1;

                while (axe1More) {
                    index = getVoxelIndex(x, y, z);
                    if ((this->*checkFace)(w, x, y, z)
                     && !w->getVoxelMergingFace(x, y, z, face)
                     && getTarget()->getVoxel(index).getType() == type) {
                         (p1->*setAxe1)((p1->*getAxe1)() + 1);
                         (p2->*setAxe1)((p2->*getAxe1)() + 1);
                         w->setVoxelMergingFace(x, y, z, face, true);
                        *axe1 = *axe1 + 1;
                        axe1Size = axe1Size + 1;
                    } else {
                        axe1More = false;
                    }
                    if (*axe1 == limit1) {
                        axe1More = false;
                    }
                }

                axe1More = true;
                *axe1 = axe1Cpy;
                axe2More = !(*axe2 == limit2 - 1);
                *axe2 = *axe2 + 1;
                while (axe2More) {
                    while (axe1More && axe1Size != axe2Size) {
                        index = getVoxelIndex(x, y, z);
                        if ((this->*checkFace)(w, x, y, z)
                         && !w->getVoxelMergingFace(x, y, z, face)
                         && getTarget()->getVoxel(index).getType() == type) {
                            axe2Size = axe2Size + 1;
                            *axe1 = *axe1 + 1;
                        } else {
                            axe1More = false;
                        }
                        if (*axe1 == limit1) {
                            axe1More = false;
                        }
                    }
                    if (axe2Size == axe1Size) {
                        (p3->*setAxe2)((p3->*getAxe2)() + 1);
                        (p4->*setAxe2)((p4->*getAxe2)() + 1);
                        *axe1 = axe1Cpy;
                        while (axe2Size != 0) {
                            index = getVoxelIndex(x, y, z);
                            w->setVoxelMergingFace(x, y, z, face, true);
                            axe2Size = axe2Size - 1;
                            *axe1 = *axe1 + 1;
                        }
                    } else {
                        axe2More = false;
                    }
                    axe2Size = 0;
                    axe1More = true;
                    *axe1 = axe1Cpy;
                    *axe2 = *axe2 + 1;
                    if (*axe2 == limit2) {
                        axe2More = false;
                    }
                }
            }

            void Mesh::addPackedVertex(Maths::Point3D<GLint> const (&p)[4], GLuint const& face, size_t const& cCode) {
                Maths::Vector3D<GLbyte> n;
                GLuint idx1, idx2, nIdx;

                switch (face) {
                    case (XNegative) : {
                        n = {-1, 0, 0};
                        break;
                    }
                    case (YNegative) : {
                        n = {0, -1, 0};
                        break;
                    }
                    case (ZNegative) : {
                        n = {0, 0, -1};
                        break;
                    }
                    case (XPositive) : {
                        n = {1, 0, 0};
                        break;
                    }
                    case (YPositive) : {
                        n = {0, 1, 0};
                        break;
                    }
                    case (ZPositive) : {
                        n = {0, 0, 1};
                        break;
                    }
                    default : {
                    }
                }

                addVertex(p[2]);
                addNormal(n);
                addMaterialID(cCode);
                nIdx = static_cast <GLuint> (vData.size() / 3) - 1;
                addIndex(nIdx);
                idx1 = nIdx;

                addVertex(p[1]);
                addNormal(n);
                addMaterialID(cCode);
                nIdx = static_cast <GLuint> (vData.size() / 3) - 1;
                addIndex(nIdx);
                idx2 = nIdx;

                addVertex(p[0]);
                addNormal(n);
                addMaterialID(cCode);
                nIdx = static_cast <GLuint> (vData.size() / 3) - 1;
                addIndex(nIdx);

                addVertex(p[3]);
                addNormal(n);
                addMaterialID(cCode);
                nIdx = static_cast <GLuint> (vData.size() / 3) - 1;
                addIndex(nIdx);

                iData.push_back(idx2);
                iData.push_back(idx1);
            }

            Mesh& Mesh::operator=(Mesh && mesh) {
                target = std::move(mesh.target);
                vData = std::move(mesh.vData);
                mData = std::move(mesh.mData);
                nData = std::move(mesh.nData);
                iData = std::move(mesh.iData);
                return *this;
            }

            bool Mesh::checkVoxelXNegativeFace(World* w, GLuint const& x, GLuint const& y, GLuint const& z) {
                if (x == 0) {
                    if (getTarget()->getCoord().getX() - w->getShift().getX() == -1 * static_cast <GLint> (w->getHExtent().getX())) {
                        return true;
                    } else {
                        return w->getChunk(getTarget()->getCoord().getX() - 1, getTarget()->getCoord().getY())->getVoxel(Chunk::SIZE_X - 1, y, z).getType() == VOID;
                    }
                } else {
                    return getTarget()->getVoxel(x - 1, y, z).getType() == VOID;
                }
            }

            bool Mesh::checkVoxelXPositiveFace(World* w, GLuint const& x, GLuint const& y, GLuint const& z) {
                if (x == Chunk::SIZE_X - 1) {
                    if (getTarget()->getCoord().getX() - w->getShift().getX() == static_cast <GLint> (w->getHExtent().getX())) {
                        return true;
                    } else {
                        return w->getChunk(getTarget()->getCoord().getX() + 1, getTarget()->getCoord().getY())->getVoxel(0, y, z).getType() == VOID;
                    }
                } else {
                    return getTarget()->getVoxel(x + 1, y, z).getType() == VOID;
                }
            }

            bool Mesh::checkVoxelYNegativeFace(World* w, GLuint const& x, GLuint const& y, GLuint const& z) {
                if (y == 0) {
                    if (getTarget()->getCoord().getY() - w->getShift().getY() == -1 * static_cast <GLint> (w->getHExtent().getY())) {
                        return true;
                    } else {
                        return w->getChunk(getTarget()->getCoord().getX(), getTarget()->getCoord().getY() - 1)->getVoxel(x, Chunk::SIZE_Y - 1, z).getType() == VOID;
                    }
                } else {
                    return getTarget()->getVoxel(x, y - 1, z).getType() == VOID;
                }
            }

            bool Mesh::checkVoxelYPositiveFace(World* w, GLuint const& x, GLuint const& y, GLuint const& z) {
                if (y == Chunk::SIZE_Y - 1) {
                    if (getTarget()->getCoord().getY() - w->getShift().getY() == static_cast <GLint> (w->getHExtent().getY())) {
                        return true;
                    } else {
                        return w->getChunk(getTarget()->getCoord().getX(), getTarget()->getCoord().getY() + 1)->getVoxel(x, 0, z).getType() == VOID;
                    }
                } else {
                    return getTarget()->getVoxel(x, y + 1, z).getType() == VOID;
                }
            }

            bool Mesh::checkVoxelZNegativeFace(World* w, GLuint const& x, GLuint const& y, GLuint const& z) {
                if (z == 0) {
                    return true;
                } else {
                    return getTarget()->getVoxel(x, y, z - 1).getType() == VOID;
                }
            }

            bool Mesh::checkVoxelZPositiveFace(World* w, GLuint const& x, GLuint const& y, GLuint const& z) {
                if (z == Chunk::SIZE_Z - 1) {
                    return true;
                } else {
                    return getTarget()->getVoxel(x, y, z + 1).getType() == VOID;
                }
            }

        };
    };
