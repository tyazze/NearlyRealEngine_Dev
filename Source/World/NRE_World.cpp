
    #include "NRE_World.hpp"

    namespace NRE {
        namespace World {

            int World::DEFAULT_SOIL_SEED = 6'032'018;
            int World::DEFAULT_MOISTURE_SEED = 21'032'018;

            World::World() : World(Maths::Vector2D<GLuint>(0, 0), Maths::Vector2D<GLint>(0, 0)) {
            }

            World::World(Maths::Vector2D<GLuint> const& hExtent, Maths::Vector2D<GLuint> const& shift) : chunkMap((hExtent.getX() * 2 + 1) * (hExtent.getY() * 2 + 1)), hExtent(hExtent), shift(shift), voxelMergingGlobalCache(0) {
                FastNoise worldGen, worldGen2;
                worldGen.SetNoiseType(FastNoise::Simplex);
                worldGen.SetSeed(DEFAULT_SOIL_SEED);
                worldGen.SetFrequency(0.004);
                worldGen2.SetNoiseType(FastNoise::Simplex);
                worldGen2.SetSeed(DEFAULT_MOISTURE_SEED);
                soilGenerator = worldGen;
                moistureGenerator = worldGen2;

                voxelMergingGlobalCache = new bool[Chunk::SIZE_X * Chunk::SIZE_Y * Chunk::SIZE_Z * FACE_NUM];

                for (int x = -getHExtent().getX(); x <= static_cast <GLint> (getHExtent().getX()); x = x + 1) {
                    for (int y = -getHExtent().getY(); y <= static_cast<GLint> (getHExtent().getY()); y = y + 1) {
                        Maths::Point2D<GLint> tmp(x + getShift().getX(), y + getShift().getY());
                        chunkMap[tmp] = new Chunk(tmp, true);
                    }
                }
            }

            World::World(World const& w) : chunkMap(w.getChunkMap()), loadRegionMap(w.getLoadRegionMap()), saveRegionMap(w.getSaveRegionMap()), constructionStack(w.getConstructionStack()), hExtent(w.getHExtent()), shift(w.getShift()), soilGenerator(w.getSoilGenerator()), moistureGenerator(w.getMoistureGenerator()), voxelMergingGlobalCache(w.getVoxelMergingGlobalCache()) {
            }

            World::~World() {
                delete[] voxelMergingGlobalCache;
                for (auto &it : chunkMap) {
                    addChunkToSaveRegion(it.second);
                }
                emptySaveRegionMap();
                for (const auto &it : chunkMap) {
                    delete it.second;
                }
            }

            std::unordered_map<Maths::Point2D<GLint>, Chunk*> const& World::getChunkMap() const {
                return chunkMap;
            }

            std::unordered_map<Maths::Point2D<GLint>, Region*> const& World::getLoadRegionMap() const {
                return loadRegionMap;
            }

            std::unordered_map<Maths::Point2D<GLint>, Region*> const& World::getSaveRegionMap() const {
                return saveRegionMap;
            }

            std::stack<Chunk*> const& World::getConstructionStack() const {
                return constructionStack;
            }

            Chunk* const& World::getChunk(Maths::Point2D<GLint> const& p) {
                return chunkMap.find(p)->second;
            }

            Chunk* const& World::getChunk(GLint const& x, GLint const& y) {
                return getChunk(Maths::Point2D<GLint>(x, y));
            }

            Maths::Vector2D<GLuint> const& World::getHExtent() const {
                return hExtent;
            }

            Maths::Vector2D<GLint> const& World::getShift() const {
                return shift;
            }

            FastNoise const& World::getSoilGenerator() const {
                return soilGenerator;
            }

            FastNoise const& World::getMoistureGenerator() const {
                return moistureGenerator;
            }

            bool* World::getVoxelMergingGlobalCache() const {
                return voxelMergingGlobalCache;
            }

            bool const& World::getVoxelMergingFace(Maths::Point3D<GLuint> const& p, int const& face) const {
                return getVoxelMergingFace(p.getX(), p.getY(), p.getZ(), face);
            }

            bool const& World::getVoxelMergingFace(GLuint const& x, GLuint const& y, GLuint const& z, int const& face) const {
                return voxelMergingGlobalCache[getVoxelCacheIndex(x, y, z, face)];
            }

            void World::setChunkMap(std::unordered_map<Maths::Point2D<GLint>, Chunk*> const& map) {
                chunkMap = map;
            }

            void World::setLoadRegionMap(std::unordered_map<Maths::Point2D<GLint>, Region*> const& map) {
                loadRegionMap = map;
            }

            void World::setSaveRegionMap(std::unordered_map<Maths::Point2D<GLint>, Region*> const& map) {
                saveRegionMap = map;
            }

            void World::setConstructionStack(std::stack<Chunk*> const& stack) {
                constructionStack = stack;
            }

            void World::setChunk(Maths::Point2D<GLint> const& p, Chunk* const& chunk) {
                chunkMap[p] = chunk;
            }

            void World::setChunk(GLint const& x, GLint const& y, Chunk* const& chunk) {
                setChunk(Maths::Point2D<GLint>(x, y), chunk);
            }

            void World::setHExtent(Maths::Vector2D<GLuint> const& size) {
                hExtent = size;
            }

            void World::setShift(Maths::Vector2D<GLint> const& size) {
                shift = size;
            }

            void World::setSoilGenerator(FastNoise const& gen) {
                soilGenerator = gen;
            }

            void World::setMoistureGenerator(FastNoise const& gen) {
                moistureGenerator = gen;
            }

            void World::setVoxelMergingGlobalCache(bool* (&cache)) {
                voxelMergingGlobalCache = cache;
            }
            void World::setVoxelMergingFace(Maths::Point3D<GLuint> const& p, int const& face, bool const& state) {
                setVoxelMergingFace(p.getX(), p.getY(), p.getZ(), face, state);
            }

            void World::setVoxelMergingFace(GLuint const& x, GLuint const& y, GLuint const& z, int const& face, bool const& state) {
                voxelMergingGlobalCache[getVoxelCacheIndex(x, y, z, face)] = state;
            }

            void World::constructChunksMesh() {
                for (const auto &it : chunkMap) {
                    it.second->constructMesh(this);
                }
            }

            void World::render(Renderer::Shader const& shader, Maths::Matrix4x4<NREfloat> &modelview, Maths::Matrix4x4<NREfloat> &projection, Camera::FixedCamera* const& camera) {
                for (auto &it : chunkMap) {
                    if (!it.second->isLoaded()) {
                        addChunkToLoadRegion(it.second);
                    }
                    if (!it.second->isConstructed()) {
                        addChunkToConstruction(it.second);
                    }
                    if (it.second->isLoaded() && it.second->isConstructed()) {
                        it.second->render(shader, modelview, projection, camera);
                    }
                }
                emptyLoadRegionMap();
                emptyConstructionStack();
            }

            void World::resetVoxelMergingGlobalCache() {
                std::fill(voxelMergingGlobalCache, voxelMergingGlobalCache + (Chunk::SIZE_X * Chunk::SIZE_Y * Chunk::SIZE_Z * FACE_NUM), false);
            }

            NREfloat const World::getSoilNoise(NREfloat const& x, NREfloat const& y) const {
                return (getSoilGenerator().GetNoise(x, y) + 1.0) / 2.0;
            }

            NREfloat const World::getMoistureNoise(NREfloat const& x, NREfloat const& y) const {
                return (getMoistureGenerator().GetNoise(x, y) + 1.0) / 2.0;
            }

            void World::addChunkToLoadRegion(Chunk *chunk) {
                Maths::Point2D<GLint> coord;
                if (chunk->getCoord().getX() < 0) {
                    coord.setX((chunk->getCoord().getX() / 16) -1);
                } else {
                    coord.setX((chunk->getCoord().getX() / 16));
                }
                if (chunk->getCoord().getY() < 0) {
                    coord.setY((chunk->getCoord().getY() / 16) -1);
                } else {
                    coord.setY((chunk->getCoord().getY() / 16));
                }
                if (loadRegionMap.count(coord) == 0) {
                    loadRegionMap[chunk->getCoord()] = new Region(chunk);
                } else {
                    auto it = loadRegionMap.find(coord);
                    it->second->add(chunk);
                }
            }

            void World::addChunkToSaveRegion(Chunk *chunk) {
                addChunkToSaveRegion(chunk, chunk->getCoord());
            }

            void World::addChunkToSaveRegion(Chunk *chunk, Maths::Point2D<GLint> const& coord) {
                Maths::Point2D<GLint> regionCoord;
                if (chunk->getCoord().getX() < 0) {
                    regionCoord.setX((chunk->getCoord().getX() / 16) -1);
                } else {
                    regionCoord.setX((chunk->getCoord().getX() / 16));
                }
                if (chunk->getCoord().getY() < 0) {
                    regionCoord.setY((chunk->getCoord().getY() / 16) -1);
                } else {
                    regionCoord.setY((chunk->getCoord().getY() / 16));
                }
                if (saveRegionMap.count(regionCoord) == 0) {
                    saveRegionMap[regionCoord] = new Region(chunk);
                } else {
                    auto it = saveRegionMap.find(regionCoord);
                    it->second->add(chunk, coord);
                }
            }

            void World::addChunkToConstruction(Chunk *chunk) {
                constructionStack.push(chunk);
            }

            void World::emptyLoadRegionMap() {
                for (auto &it : loadRegionMap) {
                    it.second->load(this);
                }
                for (auto &it : loadRegionMap) {
                    delete it.second;
                }
                loadRegionMap.erase(loadRegionMap.begin(), loadRegionMap.end());
            }

            void World::emptySaveRegionMap() {
                for (auto &it : saveRegionMap) {
                    it.second->save();
                }
                for (auto &it : saveRegionMap) {
                    delete it.second;
                }
                saveRegionMap.erase(saveRegionMap.begin(), saveRegionMap.end());
            }

            void World::emptyConstructionStack() {
                size_t limit = constructionStack.size();
                for (GLuint i = 0; i < limit; i = i + 1) {
                    constructionStack.top()->constructMesh(this);
                    constructionStack.top()->setConstructed(true);
                    constructionStack.pop();
                }
            }

            void World::shiftChunks(Maths::Vector2D<GLint> shiftSize) {
                if (shiftSize.getX() > 0) {
                    while (shiftSize.getX() > 0) {
                        for (GLint y = -getHExtent().getY(); y <= static_cast <GLint> (getHExtent().getY()); y = y + 1) {
                            Maths::Point2D<GLint> coord(-(getHExtent().getX()) + getShift().getX(), y + getShift().getY());
                            Maths::Point2D<GLint> tmp = coord;
                            tmp.setX(getHExtent().getX() + getShift().getX() + 1);
                            addChunkToSaveRegion(getChunk(coord), coord);
                            getChunk(coord)->setCoord(tmp);
                            getChunk(coord)->reload();
                            Chunk* adr = getChunk(coord);
                            chunkMap.erase(coord);
                            chunkMap[tmp] = adr;
                        }
                        shift.setX(getShift().getX() + 1);
                        shiftSize.setX(shiftSize.getX() - 1);
                    }
                }
                emptySaveRegionMap();
                if (shiftSize.getX()  < 0) {
                    while (shiftSize.getX() < 0) {
                        for (GLint y = -getHExtent().getY(); y <= static_cast <GLint> (getHExtent().getY()); y = y + 1) {
                            Maths::Point2D<GLint> coord(getHExtent().getX() + getShift().getX(), y + getShift().getY());
                            Maths::Point2D<GLint> tmp = coord;
                            tmp.setX(-(getHExtent().getX() - getShift().getX() + 1));
                            addChunkToSaveRegion(getChunk(coord), coord);
                            getChunk(coord)->setCoord(tmp);
                            getChunk(coord)->reload();
                            Chunk* adr = getChunk(coord);
                            chunkMap.erase(coord);
                            chunkMap[tmp] = adr;
                        }
                        shift.setX(getShift().getX() - 1);
                        shiftSize.setX(shiftSize.getX() + 1);
                    }
                }
                emptySaveRegionMap();
                if (shiftSize.getY() > 0) {
                    while (shiftSize.getY() > 0) {
                        for (GLint x = -getHExtent().getX(); x <= static_cast <GLint> (getHExtent().getX()); x = x + 1) {
                            Maths::Point2D<GLint> coord(x + getShift().getX(), -(getHExtent().getY()) + getShift().getY());
                            Maths::Point2D<GLint> tmp = coord;
                            tmp.setY(getHExtent().getY() + getShift().getY() + 1);
                            addChunkToSaveRegion(getChunk(coord), coord);
                            getChunk(coord)->setCoord(tmp);
                            getChunk(coord)->reload();
                            Chunk* adr = getChunk(coord);
                            chunkMap.erase(coord);
                            chunkMap[tmp] = adr;
                        }
                        shift.setY(getShift().getY() + 1);
                        shiftSize.setY(shiftSize.getY() - 1);
                    }
                }
                emptySaveRegionMap();
                if (shiftSize.getY() < 0) {
                    while (shiftSize.getY() < 0) {
                        for (GLint x = -getHExtent().getX(); x <= static_cast <GLint> (getHExtent().getX()); x = x + 1) {
                            Maths::Point2D<GLint> coord(x  + getShift().getX(), getHExtent().getY() + getShift().getY());
                            Maths::Point2D<GLint> tmp = coord;
                            tmp.setY(-(getHExtent().getY() - getShift().getY() + 1));
                            addChunkToSaveRegion(getChunk(coord), coord);
                            getChunk(coord)->setCoord(tmp);
                            getChunk(coord)->reload();
                            Chunk* adr = getChunk(coord);
                            chunkMap.erase(coord);
                            chunkMap[tmp] = adr;
                        }
                        shift.setY(getShift().getY() - 1);
                        shiftSize.setY(shiftSize.getY() + 1);
                    }
                }
                emptySaveRegionMap();
            }

            GLuint getVoxelCacheIndex(GLuint const& x, GLuint const& y, GLuint const& z, GLuint const& face) {
                return Array::get1DIndexFrom4D(x, y, z, face, Maths::Vector4D<GLuint>(Chunk::SIZE, FACE_NUM));
            }

        };
    };
