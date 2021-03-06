
    /**
     * @file NRE_World.hpp
     * @brief Declaration of Engine's World's Object : World
     * @author Louis ABEL
     * @version 1.0
     */

    #pragma once

    #include <algorithm>
    #include <unordered_map>
    #include "Region/NRE_Region.hpp"

    /**
     * @namespace NRE
     * @brief The global NearlyRealEngine's namespace
     */
    namespace NRE {
        /**
         * @namespace World
         * @brief Engine's World's Module
         */
        namespace World {

            /**
             * @class World
             * @brief World's Object : A collection of chunk
             */
            class World {
                private:
                    std::unordered_map<Maths::Point2D<GLint>, Chunk*> chunkMap;         /**< World chunk hash map */
                    std::unordered_map<Maths::Point2D<GLint>, Region*> loadRegionMap;   /**< World loading region hash map */
                    std::unordered_map<Maths::Point2D<GLint>, Region*> saveRegionMap;   /**< World saving region hash map */
                    std::queue<Chunk*> constructionQueue;                               /**< The construction queue to load chunk on fly while rendering */
                    Maths::Vector2D<GLuint> hExtent;                                    /**< World half extent */
                    Maths::Vector2D<GLint> shift;                                       /**< World shift vector from (0, 0) */
                    FastNoise soilGenerator;                                            /**< FastNoise generator used for soil generation */
                    FastNoise moistureGenerator;                                        /**< FastNoise generator used for moisture generation */
                    bool *voxelMergingGlobalCache;                                      /**< Specific pointer to a global cache used for chunk mesh construction process */

                public:
                    //## Constructor ##//
                        /**
                         * Default Constructor
                         */
                        World();
                        /**
                         * Construct a world witha his size (half extent) and a base shift
                         * @param hExtent the world half extent
                         * @param shift   the world shift
                         */
                        World(Maths::Vector2D<GLuint> const& hExtent, Maths::Vector2D<GLuint> const& shift);

                    //## Copy-Constructor ##//
                        /**
                         * No copy allowed
                         * @param w the world to copy the content
                         */
                        World(World const& w) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move w into this, leaving w empty
                         * @param w the world to move
                         */
                        World(World && w);

                    //## Convertor ##//

                    //## Deconstructor ##//
                        /**
                         * World Deconstructor
                         */
                        ~World();

                    //## Getter ##//
                        /**
                         * Specific Chunk getter
                         * @param  p the chunk's coordinates
                         * @return   the corresponding chunk
                         */
                        Chunk* const& getChunk(Maths::Point2D<GLint> const& p);
                        /**
                         * Specific Chunk getter
                         * @param  x the chunk's x coordinate
                         * @param  y the chunk's y coordinate
                         * @return   the corresponding chunk
                         */
                        Chunk* const& getChunk(GLint const& x, GLint const& y);
                        /**
                         * Half Extent getter
                         * @return the half extent value
                         */
                        Maths::Vector2D<GLuint> const& getHExtent() const;
                        /**
                         * Shift getter
                         * @return the shift value
                         */
                        Maths::Vector2D<GLint> const& getShift() const;
                        /**
                         * Soil Generator getter
                         * @return the soil generator object
                         */
                        FastNoise const& getSoilGenerator() const;
                        /**
                         * Moisture Generator getter
                         * @return the Moisture generator object
                         */
                        FastNoise const& getMoistureGenerator() const;
                        /**
                         * Voxel Face Merged State getter
                         * @param  p    the voxel's coordinates
                         * @param  face the voxel's face to check
                         * @return      the face merged state
                         */
                        bool const& getVoxelMergingFace(Maths::Point3D<GLuint> const& p, int const& face) const;
                        /**
                         * Voxel Face Merged State getter
                         * @param  x    the voxel's x coordinate
                         * @param  y    the voxel's y coordinate
                         * @param  z    the voxel's z coordinate
                         * @param  face the voxel's face to check
                         * @return      the face merged state
                         */
                        bool const& getVoxelMergingFace(GLuint const& x, GLuint const& y, GLuint const& z, int const& face) const;

                    //## Setter ##//
                        /**
                         * Shift setter
                         * @param size the new shift value
                         */
                        void setShift(Maths::Vector2D<GLint> const& size);
                        /**
                         * Voxel Face Merged State setter
                         * @param  p    the voxel's coordinates
                         * @param  face the voxel's face to modify
                         * @param state the new voxel's face merged state value
                         */
                        void setVoxelMergingFace(Maths::Point3D<GLuint> const& p, int const& face, bool const& state);
                        /**
                         * Voxel Face Merged State setter
                         * @param  x    the voxel's x coordinate
                         * @param  y    the voxel's y coordinate
                         * @param  z    the voxel's z coordinate
                         * @param  face the voxel's face to modify
                         * @param state the new voxel's face merged state value
                         */
                        void setVoxelMergingFace(GLuint const& x, GLuint const& y, GLuint const& z, int const& face, bool const& state);

                    //## Methods ##//
                        /**
                         * Render all world's active chunk
                         * @param shader     the rendering shader
                         * @param modelview  the modelview matrix
                         * @param projection the projection matrix
                         * @param camera     the camera used for the view frustum, if null all chunk are visible
                         */
                        void render(Renderer::Shader const& shader, Maths::Matrix4x4<NREfloat> &modelview, Maths::Matrix4x4<NREfloat> &projection, Camera::FixedCamera* const& camera = 0);
                        /**
                         * Update chunk queue
                         * @param loadLimit the number of chunk to update in one frame
                         */
                        void update(GLuint const& loadLimit);
                        /**
                         * Reset the whole Voxel Face Merged Cache
                         */
                        void resetVoxelMergingGlobalCache();
                        /**
                         * Compute a noise from the soil generator
                         * @param  x the x coordinate
                         * @param  y the y coordinate
                         * @return   the computed noise
                         */
                        NREfloat const getSoilNoise(NREfloat const& x, NREfloat const& y) const;
                        /**
                         * Compute a noise from the moisture generator
                         * @param  x the x coordinate
                         * @param  y the y coordinate
                         * @return   the computed noise
                         */
                        NREfloat const getMoistureNoise(NREfloat const& x, NREfloat const& y) const;
                        /**
                         * Add a chunk to the load region map, construct region on fly if necessary
                         * @param chunk the chunk to add
                         */
                        void addChunkToLoadRegion(Chunk *chunk);
                        /**
                         * Add a chunk to the save region map, construct region on fly if necessary
                         * @param chunk the chunk to add
                         */
                        void addChunkToSaveRegion(Chunk *chunk);
                        /**
                         * Add a chunk with different coordinates to the save region map, construct region on fly if necessary
                         * @param chunk the chunk to add
                         * @param coord the chunk's coordinates used when the chunk will be saved
                         */
                        void addChunkToSaveRegion(Chunk *chunk, Maths::Point2D<GLint> const& coord);
                        /**
                         * Add a chunk to the construction queue
                         * @param chunk the chunk to add
                         */
                        void addChunkToConstruction(Chunk *chunk);
                        /**
                         * Update the load region map, process the first chunk in the map
                         */
                        void updateLoadRegionMap();
                        /**
                         * Update the save region map, process the first chunk in the map
                         */
                        void updateSaveRegionMap();
                        /**
                         * Update the construction queue, process the first chunk in the queue
                         */
                        void updateConstructionQueue();
                        /**
                         * Empty the load region map, process all chunk in the map
                         */
                        void emptyLoadRegionMap();
                        /**
                         * Empty the save region map, process all chunk in the map
                         */
                        void emptySaveRegionMap();
                        /**
                         * Empty the construction queue, process all chunk in the queue
                         */
                        void emptyConstructionQueue();
                        /**
                         * Flush the load region map, just erase them from the map
                         */
                        void flushLoadRegionMap();
                        /**
                         * Flush the save region map, just erase them from the map
                         */
                        void flushSaveRegionMap();
                        /**
                         * Flush the construction queue, just erase them from the queue
                         */
                        void flushConstructionQueue();
                        /**
                         * Shift all chunks from a shift vector
                         * @param shiftSize the shift vector
                         */
                        void shiftChunks(Maths::Vector2D<GLint> shiftSize);
                        /**
                         * Shift all left chunk to become the new right ones
                         */
                        void shiftChunksRight();
                        /**
                         * Shift all right chunk to become the new left ones
                         */
                        void shiftChunksLeft();
                        /**
                         * Shift all back chunk to become the new front ones
                         */
                        void shiftChunksFront();
                        /**
                         * Shift all front chunk to become the new back ones
                         */
                        void shiftChunksBack();

                    //## Access Operator ##//

                    //## Assignment Operator ##//
                        /**
                         * No copy allowed
                         * @param w the world to copy into this
                         * @return the reference of himself
                         */
                        World& operator=(World const& w) = delete;
                        /**
                         * Move assigment of w into this, leaving w empty
                         * @param w the world to move into this
                         * @return the reference of himself
                         */
                        World& operator=(World && w);

                    //## Shortcut Operator ##//

                    //## Arithmetic Operator ##//

                    //## Comparison Operator ##//

                    //## BitWise Operator ##//

                    //## Shift Operator ##//

                private:
                    static int DEFAULT_SOIL_SEED;       /**< The default soil generator seed */
                    static int DEFAULT_MOISTURE_SEED;   /**< The default moisture generator seed */
            };

            /**
             * Compute the voxel cache 1D index from 4D coordinates
             * @param  x    the voxel's x coordinate
             * @param  y    the voxel's y coordinate
             * @param  z    the voxel's z coordinate
             * @param  face the voxel's face to check
             * @return      the computed index using array operation function
             */
            GLuint getVoxelCacheIndex(GLuint const& x, GLuint const& y, GLuint const& z, GLuint const& face);

        };
    };
