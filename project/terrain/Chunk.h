#ifndef CHUNK_H
#define CHUNK_H

#include <glm/vec2.hpp>

#include <memory>

#include "Grid/Grid.h"
#include "ScalarFrameBuffer.h"

#include "ScreenQuad/ScreenQuad.h"
#include "Texture.h"
#include "Tree/Tree.h"

class Chunk;

typedef std::shared_ptr<Chunk> SharedChunk;

class Chunk
{
public:
    Chunk(const glm::vec2& offset, const glm::vec2& size);
    void update(float delta_s);
    void finish();
    int setAttrs(int res, SharedTexture hmap, const Grid& terrain, const Grid& water, const Grid& grass);
    void addTrees(Material& trunc, Material& leaves);
    void drawTerrain(float time, const glm::mat4 &view, const glm::mat4 &projection, Material& mat, bool shad = false);
    void drawGrass(float time, const glm::mat4 &view, const glm::mat4 &projection,Material& mat);
    void drawWater(float time, const glm::mat4 &view, const glm::mat4 &projection,Material& mat);
    void drawTruncs(float time, const glm::mat4& view, const glm::mat4& projection,Material& mat);
    void drawLeaves(float time, const glm::mat4& view, const glm::mat4& projection,Material& mat);
    void setFrameID(long id);
    glm::ivec2 key() const;
    long frameID() { return mFrameId;}
    const SharedTexture& hMap() const {return mHmap;}
    const glm::vec2& pos() const {return mOffset;}
    const glm::vec2& size() const {return mSize;}
    int res() const {return mRes;}
    ~Chunk();
private:
    std::uniform_real_distribution<float> mRand;
    std::default_random_engine mEng;
    std::vector<Tree> mTrees;
    SharedTexture mHmap;
    SharedTexture mNextHmap;
    ScalarFrameBuffer mNoiseBuffer;
    const Grid* mTerrain;
    const Grid* mWater;
    const Grid* mGrass;
    long mFrameId;
    int mRes;
    glm::vec2 mOffset;
    glm::vec2 mSize;
    glm::mat4 mModel;

    //ChunkGenerator::Job* mTexJob;
    //ChunkFuture mTexFuture;
};

#endif // CHUNK_H
