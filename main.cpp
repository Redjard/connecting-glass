// #define DEBUG_CONSOLE // Uncomment this if you want a debug console to start. You can use the Console class to print. You can use Console::inStrings to get input.

#include <4dm.h>

using namespace fdm;

// Initialize the DLLMain
initDLL

#define funnyLogic(thisBlockType, blockToCheck) \
((BlockInfo::Blocks[thisBlockType].opaque && !BlockInfo::Blocks[blockToCheck].opaque) || \
(!BlockInfo::Blocks[thisBlockType].opaque && blockToCheck != thisBlockType && !BlockInfo::Blocks[blockToCheck].opaque))

#define funnyLogic2(thisBlockType, blockToCheck) (!BlockInfo::Blocks[thisBlockType].opaque && thisBlockType == blockToCheck)

const int glassCol = 32;
const int startCol = 84;
const int tlbrCol = startCol;
const int brCol = startCol + 1;
const int blbrCol = startCol + 2;
const int tlqbrCol = startCol + 3;
const int tnblbrCol = startCol + 4;
const int trqblCol = startCol + 5;
const int tnbrCol = startCol + 6;
const int tlqCol = startCol + 7;
const int tnCol = startCol + 8;
const int trqCol = startCol + 9;
const int tqCol = startCol + 10;
const int lrCol = startCol + 11;
const int empty = startCol - 1;
const int allDots = startCol - 2;
const int threeDots = startCol - 3;
const int cols = 96;
const int rows = 16;

static bool glassTiling = true;

// kill me please. i wanna *tidal wave jumpscare*
void tilingLol(glm::u8vec4* tuv, const bool closeTo[9])
{
    //  **
    //  *#~
    //   ~
    if (closeTo[0] &&
        closeTo[1] &&
        closeTo[3] &&
        !closeTo[5] &&
        !closeTo[7])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = trqCol;
            tuv[i].y = 1 - tuv[i].y;
        }
    //   **
    //  ~#*
    //   ~
    else if (closeTo[2] &&
            closeTo[1] &&
            closeTo[5] &&
            !closeTo[3] &&
            !closeTo[7])
            for (int i = 0; i < 8; i++)
            {
                tuv[i].w = tlqCol;
                tuv[i].y = 1 - tuv[i].y;
            }
    //   ~
    //  ~#*
    //   **
    else if (
        !closeTo[1] &&
        !closeTo[3] &&
        closeTo[5] &&
        closeTo[7] &&
        closeTo[8])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tlqCol;
        }
    //   ~
    //  *#~
    //  **
    else if (
        !closeTo[1] &&
        !closeTo[5] &&
        closeTo[3] &&
        closeTo[7] &&
        closeTo[6])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = trqCol;
        }
    //   *
    //  *#~
    //   ~
    else if (closeTo[1] &&
        closeTo[3] &&
        !closeTo[5] &&
        !closeTo[7])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = trqblCol;
            tuv[i].y = 1 - tuv[i].y;
        }
    //   *
    //  ~#*
    //   ~
    else if (closeTo[1] &&
        closeTo[5] &&
        !closeTo[3] &&
        !closeTo[7])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tlqbrCol;
            tuv[i].y = 1 - tuv[i].y;
        }
    //   ~
    //  ~#*
    //   *
    else if (
        !closeTo[1] &&
        !closeTo[3] &&
        closeTo[5] &&
        closeTo[7])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tlqbrCol;
        }
    //   ~
    //  *#~
    //   *
    else if (
        !closeTo[1] &&
        !closeTo[5] &&
        closeTo[3] &&
        closeTo[7])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = trqblCol;
        }
    //   *
    //  ~#~
    //   *
    else if (closeTo[7] &&
        closeTo[1] &&
        !closeTo[3] &&
        !closeTo[5])
        for (int i = 0; i < 8; i++)
            tuv[i].w = lrCol;
    //   *
    //  ~#~
    //   
    else if (closeTo[1] &&
        !closeTo[3] &&
        !closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tqCol;
            tuv[i].y = 1 - tuv[i].y;
        }
    //   
    //  ~#~
    //   *
    else if (closeTo[7] &&
        !closeTo[3] &&
        !closeTo[5])
        for (int i = 0; i < 8; i++)
            tuv[i].w = tqCol;
    //   ~
    //  *#*
    //   ~
    else if (closeTo[3] &&
        closeTo[5] &&
        !closeTo[7] &&
        !closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = lrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;
        }
    //   ~
    //  *#
    //   ~
    else if (closeTo[3] &&
        !closeTo[7] &&
        !closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tqCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
        }
    //   
    //   #*
    //   
    else if (closeTo[5] &&
        !closeTo[7] &&
        !closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tqCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;
        }
    //  ***
    //  *#*
    //  ***
    else if (closeTo[3] &&
        closeTo[5] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[2] &&
        closeTo[8] &&
        closeTo[0] &&
        closeTo[6]
        )
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = empty;
        }
    //   *
    //  *#*
    //   *
    else if (closeTo[3] &&
        closeTo[5] &&
        closeTo[7] &&
        closeTo[1] &&
        !closeTo[2] &&
        !closeTo[8] &&
        !closeTo[0] &&
        !closeTo[6]
        )
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = allDots;
        }

        //  ***
        //  *#*
        //  ~*~
    else if (closeTo[2] && closeTo[0] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[3] &&
        closeTo[5] &&
        !closeTo[6] && !closeTo[8])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = blbrCol;
        }
        //  ~*~
        //  *#*
        //  ***
    else if (!closeTo[2] && !closeTo[0] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[3] &&
        closeTo[5] &&
        closeTo[6] && closeTo[8])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = blbrCol;

            tuv[i].y = 1 - tuv[i].y;
        }
        //  ~**
        //  *#*
        //  ~**
    else if (!closeTo[0] && !closeTo[6] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[3] &&
        closeTo[5] &&
        closeTo[2] && closeTo[8])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = blbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
        }
        //  **~
        //  *#*
        //  **~
    else if (!closeTo[2] && !closeTo[8] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[3] &&
        closeTo[5] &&
        closeTo[6] && closeTo[0])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = blbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;
        }
    //  ~**
    //  *#*
    //  ~*~
    else if (closeTo[3] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[2] &&
        closeTo[5] &&
        !closeTo[6] &&
        !closeTo[0] &&
        !closeTo[8])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = threeDots;
        }
    //  **~
    //  *#*
    //  ~*~
    else if (closeTo[5] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[0] &&
        closeTo[3] &&
        !closeTo[8] &&
        !closeTo[2] &&
        !closeTo[6])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = threeDots;

            tuv[i].x = 1 - tuv[i].x;
        }
    //  ~*~
    //  *#*
    //  ~**
    else if (closeTo[3] &&
        closeTo[1] &&
        closeTo[7] &&
        closeTo[8] &&
        closeTo[5] &&
        !closeTo[0] &&
        !closeTo[6] &&
        !closeTo[2])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = threeDots;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
        }
    //  ~*~
    //  *#*
    //  **~
    else if (closeTo[5] &&
        closeTo[1] &&
        closeTo[7] &&
        closeTo[6] &&
        closeTo[3] &&
        !closeTo[2] &&
        !closeTo[8] &&
        !closeTo[0])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = threeDots;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;
        }
    //   **
    //  *#*
    //  ~*
    else if (closeTo[3] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[2] &&
        closeTo[5] &&
        !closeTo[6])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = brCol;

            tuv[i].x = 1 - tuv[i].x;
        }
    //  **
    //  *#*
    //   *~
    else if (closeTo[5] &&
        closeTo[7] &&
        closeTo[1] &&
        closeTo[0] &&
        closeTo[3] &&
        !closeTo[8])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = brCol;
        }
    //  ~*
    //  *#*
    //   **
    else if (closeTo[3] &&
        closeTo[1] &&
        closeTo[7] &&
        closeTo[8] &&
        closeTo[5] &&
        !closeTo[0])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = brCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
            tuv[i].x = 1 - tuv[i].x;
        }
    //   *~
    //  *#*
    //  **
    else if (closeTo[5] &&
        closeTo[1] &&
        closeTo[7] &&
        closeTo[6] &&
        closeTo[3] &&
        !closeTo[2])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = brCol;
            tuv[i].y = 1 - tuv[i].y;
        }
    //   *~
    //  ~#*
    //   **
    else if (closeTo[5] &&
        closeTo[7] &&
        closeTo[1] &&
        !closeTo[2] &&
        closeTo[8] &&
        !closeTo[3])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].x = 1 - tuv[i].x;
        }
    //  ~*
    //  *#~
    //  **
    else if (closeTo[3] &&
        closeTo[7] &&
        closeTo[1] &&
        !closeTo[0] &&
        closeTo[6] &&
        !closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
            tuv[i].x = 1 - tuv[i].x;
        }
    //  ~*
    //  *#~
    //  ~*
    else if (closeTo[3] &&
        closeTo[7] &&
        closeTo[1] &&
        !closeTo[0] &&
        !closeTo[6] &&
        !closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnblbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
            tuv[i].x = 1 - tuv[i].x;
        }
    //   *~
    //  ~#*
    //   *~
    else if (closeTo[5] &&
        closeTo[7] &&
        closeTo[1] &&
        !closeTo[2] &&
        !closeTo[8] &&
        !closeTo[3])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnblbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;
        }
    //  **
    //  *#~
    //  **
    else if (!closeTo[5] && closeTo[0] && closeTo[6] && closeTo[3] &&
        closeTo[7] &&
        closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
        }
    //   **
    //  ~#*
    //   **
    else if (!closeTo[3] && closeTo[2] && closeTo[8] && closeTo[5] &&
        closeTo[7] &&
        closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;
        }

        //   *
        //  *#~
        //  **
    else if (!closeTo[5] && closeTo[6] && closeTo[3] &&
        closeTo[7] &&
        closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
            tuv[i].x = 1 - tuv[i].x;
        }
        //   *
        //  ~#*
        //   **
    else if (!closeTo[3] && closeTo[8] && closeTo[5] &&
        closeTo[7] &&
        closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;
            tuv[i].x = 1 - tuv[i].x;
        }
        //  **
        //  *#~
        //   *
    else if (!closeTo[5] && closeTo[0] && closeTo[3] &&
        closeTo[7] &&
        closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;

            tuv[i].y = 1 - tuv[i].y;
        }
        //   **
        //  ~#*
        //   *
    else if (!closeTo[3] && closeTo[2] && closeTo[5] &&
        closeTo[7] &&
        closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;
            uint8_t oldX = tuv[i].x;
            tuv[i].x = tuv[i].y;
            tuv[i].y = oldX;
        }
    //   ~
    //  *#*
    //  ~*~
    else if (closeTo[7] &&
        closeTo[3] &&
        closeTo[5] &&
        !closeTo[8] &&
        !closeTo[6] &&
        !closeTo[1])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnblbrCol;
        }
    //  ~*~
    //  *#*
    //   ~
    else if (closeTo[1] &&
        closeTo[3] &&
        closeTo[5] &&
        !closeTo[2] &&
        !closeTo[0] &&
        !closeTo[7])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnblbrCol;

            tuv[i].y = 1 - tuv[i].y;
        }
    //   ~
    //  *#*
    //  ***
    else if (!closeTo[1] && closeTo[6] && closeTo[8] && closeTo[7] &&
        closeTo[3] &&
        closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnCol;
        }
    //  ***
    //  *#*
    //   ~
    else if (!closeTo[7] && closeTo[0] && closeTo[2] && closeTo[1] &&
        closeTo[3] &&
        closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnCol;

            tuv[i].y = 1 - tuv[i].y;
        }

        //   ~
        //  *#*
        //  **~
    else if (!closeTo[8] && !closeTo[1] && closeTo[6] && closeTo[7] &&
        closeTo[3] &&
        closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;
        }
        //  **~
        //  *#*
        //   ~
    else if (!closeTo[2] && !closeTo[7] && closeTo[0] && closeTo[1] &&
        closeTo[3] &&
        closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;

            tuv[i].y = 1 - tuv[i].y;
        }
        //   ~
        //  *#*
        //  ~**
    else if (!closeTo[1] && !closeTo[6] && closeTo[8] && closeTo[7] &&
        closeTo[3] &&
        closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;

            tuv[i].x = 1 - tuv[i].x;
        }
        //  ~**
        //  *#*
        //   ~
    else if (!closeTo[0] && !closeTo[7] && closeTo[2] && closeTo[1] &&
        closeTo[3] &&
        closeTo[5])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tnbrCol;

            tuv[i].x = 1 - tuv[i].x;

            tuv[i].y = 1 - tuv[i].y;
        }
        //  ~**
        //  *#*
        //  **~
    else if (!closeTo[0] && !closeTo[8] && closeTo[1] && closeTo[2] && closeTo[3] && closeTo[5] && closeTo[6] && closeTo[7])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tlbrCol;
        }
        //  **~
        //  *#*
        //  ~**
    else if (!closeTo[2] && !closeTo[6] && closeTo[1] && closeTo[0] && closeTo[3] && closeTo[5] && closeTo[8] && closeTo[7])
        for (int i = 0; i < 8; i++)
        {
            tuv[i].w = tlbrCol;

            tuv[i].x = 1 - tuv[i].x;
        }
}

// yea i rewrote the whole fucking mesh generation, deal with it. (it was totally done for this mod and totally not for a custom blocks experiment mo~ i mean 4dm 0.3 alpha)
$hook(void, Chunk, generateMeshSection, fdm::Chunk::ChunkMesh& mesh, uint8_t startY, bool smoothLighting, bool shadows, bool lights)
{
    //original(self, mesh, startY, smoothLighting, shadows, lights);
    //return;

    int sectionY = std::max((int)startY, 1);

    BlockInfo::VertLighting lighting[8];

    for (int blockIndex = 0; blockIndex < 8 * 8 * 8; blockIndex++)
    {
        int blockX = ((blockIndex >> 6) & 7) + 1;
        int blockZ = ((blockIndex >> 3) & 7) + 1;
        int blockW = (blockIndex & 7) + 1;

        // lava plane
        if (!BlockInfo::Blocks[self->blocks[blockX][blockZ][blockW][1]].opaque)
        {
            // reset light values
            for (int i = 0; i < 8; i++)
            {
                lighting[i].ambient = 0xFF;
                lighting[i].shadow = 0xFF;
                lighting[i].glow = { 0xFF,0xFF,0xFF };
            }
            // get light values
            if (smoothLighting)
                self->getSmoothLighting({ blockX, 0, blockZ, blockW }, 3, lighting, shadows, lights);
            else
                self->getLighting({ blockX, 0, blockZ, blockW }, 3, lighting, shadows, lights);
            // add side
            mesh.addMeshSide(BlockInfo::cube_verts_y, BlockInfo::Blocks[BlockInfo::LAVA].tuv_top, { blockX, 1, blockZ, blockW }, lighting);
        }

        for (int blockY = sectionY; blockY < sectionY + 16; blockY++)
        {
            const uint8_t blockType = self->blocks[blockX][blockZ][blockW][blockY];

            if (blockType == BlockInfo::AIR || blockType == BlockInfo::BARRIER || blockType == BlockInfo::CHUNK_BORDER)
                continue;
            
            glm::ivec4 block = glm::ivec4(blockX, blockY, blockZ, blockW);


            if (BlockInfo::Blocks[blockType].plant)
            {
                BlockInfo::VertLighting lightingA[16];
                for (int i = 0; i < 16; i++)
                {
                    lightingA[i].ambient = 0xC0;
                    lightingA[i].shadow = 0xFF;
                    lightingA[i].glow = { 0,0,0 };
                }
                if (smoothLighting)
                    self->getSmoothLighting({ blockX, glm::max(0, blockY - 1), blockZ, blockW }, 3, lightingA, shadows, lights);
                else
                    self->getLighting({ blockX, glm::max(0, blockY - 1), blockZ, blockW }, 3, lightingA, shadows, lights);

                if (blockY < fdm::Chunk::HEIGHT - 1 && BlockInfo::Blocks[self->blocks[blockX][blockZ][blockW][blockY + 1]].opaque)
                {
                    if (smoothLighting)
                        self->getSmoothLighting({ blockX, blockY + 1, blockZ, blockW }, 2, lightingA + 8, shadows, lights);
                    else
                        self->getLighting({ blockX, blockY + 1, blockZ, blockW }, 2, lightingA + 8, shadows, lights);
                }
                else
                {
                    if (smoothLighting)
                        self->getSmoothLighting({ blockX, blockY, blockZ, blockW }, 3, lightingA + 8, shadows, lights);
                    else
                        self->getLighting({ blockX, blockY, blockZ, blockW }, 3, lightingA + 8, shadows, lights);
                }

                mesh.addMeshPlant(BlockInfo::plant_full_verts, BlockInfo::Blocks[blockType].tuv_full_block, { blockX, blockY, blockZ, blockW }, lightingA);
            }
            else
            {
                if (funnyLogic(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY]))
                {
                    // reset light values
                    for (int i = 0; i < 8; i++)
                    {
                        lighting[i].ambient = 0xC0;
                        lighting[i].shadow = 0xFF;
                        lighting[i].glow = { 0,0,0 };
                    }
                    // get light values
                    if (smoothLighting)
                        self->getSmoothLighting(block, 0, lighting, shadows, lights);
                    else
                        self->getLighting(block, 0, lighting, shadows, lights);

                    glm::u8vec4 tuv_side[8];
                    memcpy(tuv_side, BlockInfo::Blocks[blockType].tuv_side, sizeof(tuv_side));
                    if (glassTiling && blockType == BlockInfo::GLASS)
                    {
                        bool closeTo[9]
                        {
                            funnyLogic2(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY + 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY + 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY + 1]),
                            funnyLogic2(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY]),
                            funnyLogic2(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY - 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY - 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY - 1])
                        };

                        tilingLol(tuv_side, closeTo);
                    }
                    // add side
                    mesh.addMeshSide(BlockInfo::cube_verts_x, tuv_side, { blockX, blockY, blockZ, blockW }, lighting);
                }
                if (funnyLogic(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY]))
                {
                    // reset light values
                    for (int i = 0; i < 8; i++)
                    {
                        lighting[i].ambient = 0xC0;
                        lighting[i].shadow = 0xFF;
                        lighting[i].glow = { 0,0,0 };
                    }
                    // get light values
                    if (smoothLighting)
                        self->getSmoothLighting(block, 1, lighting, shadows, lights);
                    else
                        self->getLighting(block, 1, lighting, shadows, lights);

                    glm::u8vec4 tuv_side[8];
                    memcpy(tuv_side, BlockInfo::Blocks[blockType].tuv_side, sizeof(tuv_side));
                    if (glassTiling && blockType == BlockInfo::GLASS)
                    {
                        bool closeTo[9]
                        {
                            funnyLogic2(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY + 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY + 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY + 1]),
                            funnyLogic2(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY]),
                            funnyLogic2(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY - 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY - 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY - 1])
                        };

                        tilingLol(tuv_side, closeTo);
                    }
                    // add side
                    mesh.addMeshSide(BlockInfo::cube_verts_x, tuv_side, { blockX + 1, blockY, blockZ, blockW }, lighting);
                }
                if (funnyLogic(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY]))
                {
                    // reset light values
                    for (int i = 0; i < 8; i++)
                    {
                        lighting[i].ambient = 0xC0;
                        lighting[i].shadow = 0xFF;
                        lighting[i].glow = { 0,0,0 };
                    }
                    // get light values
                    if (smoothLighting)
                        self->getSmoothLighting(block, 4, lighting, shadows, lights);
                    else
                        self->getLighting(block, 4, lighting, shadows, lights);

                    glm::u8vec4 tuv_side[8];
                    memcpy(tuv_side, BlockInfo::Blocks[blockType].tuv_side, sizeof(tuv_side));
                    if (glassTiling && blockType == BlockInfo::GLASS)
                    {
                        bool closeTo[9]
                        {
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY + 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY + 1]), funnyLogic2(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY + 1]),
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY]),
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY - 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY - 1]), funnyLogic2(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY - 1])
                        };

                        tilingLol(tuv_side, closeTo);
                    }
                    // add side
                    mesh.addMeshSide(BlockInfo::cube_verts_z, tuv_side, { blockX, blockY, blockZ, blockW }, lighting);
                }
                if (funnyLogic(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY]))
                {
                    // reset light values
                    for (int i = 0; i < 8; i++)
                    {
                        lighting[i].ambient = 0xC0;
                        lighting[i].shadow = 0xFF;
                        lighting[i].glow = { 0,0,0 };
                    }
                    // get light values
                    if (smoothLighting)
                        self->getSmoothLighting(block, 5, lighting, shadows, lights);
                    else
                        self->getLighting(block, 5, lighting, shadows, lights);

                    glm::u8vec4 tuv_side[8];
                    memcpy(tuv_side, BlockInfo::Blocks[blockType].tuv_side, sizeof(tuv_side));
                    if (glassTiling && blockType == BlockInfo::GLASS)
                    {
                        bool closeTo[9]
                        {
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY + 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY + 1]), funnyLogic2(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY + 1]),
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY]),
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY - 1]), funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY - 1]), funnyLogic2(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY - 1])
                        };

                        tilingLol(tuv_side, closeTo);
                    }
                    // add side
                    mesh.addMeshSide(BlockInfo::cube_verts_z, tuv_side, { blockX, blockY, blockZ + 1, blockW }, lighting);
                }
                if (funnyLogic(blockType, self->blocks[blockX][blockZ][blockW - 1][blockY]))
                {
                    // reset light values
                    for (int i = 0; i < 8; i++)
                    {
                        lighting[i].ambient = 0xC0;
                        lighting[i].shadow = 0xFF;
                        lighting[i].glow = { 0,0,0 };
                    }
                    // get light values
                    if (smoothLighting)
                        self->getSmoothLighting(block, 6, lighting, shadows, lights);
                    else
                        self->getLighting(block, 6, lighting, shadows, lights);
                    // add side
                    mesh.addMeshSide(BlockInfo::cube_verts_w, BlockInfo::Blocks[blockType].tuv_side, { blockX, blockY, blockZ, blockW }, lighting);
                }
                if (funnyLogic(blockType, self->blocks[blockX][blockZ][blockW + 1][blockY]))
                {
                    // reset light values
                    for (int i = 0; i < 8; i++)
                    {
                        lighting[i].ambient = 0xC0;
                        lighting[i].shadow = 0xFF;
                        lighting[i].glow = { 0,0,0 };
                    }
                    // get light values
                    if (smoothLighting)
                        self->getSmoothLighting(block, 7, lighting, shadows, lights);
                    else
                        self->getLighting(block, 7, lighting, shadows, lights);
                    // add side
                    mesh.addMeshSide(BlockInfo::cube_verts_w, BlockInfo::Blocks[blockType].tuv_side, { blockX, blockY, blockZ, blockW + 1 }, lighting);
                }
                if (blockY == 127 || funnyLogic(blockType, self->blocks[blockX][blockZ][blockW][blockY + 1]))
                {
                    // reset light values
                    for (int i = 0; i < 8; i++)
                    {
                        lighting[i].ambient = 0xFF;
                        lighting[i].shadow = 0xFF;
                        lighting[i].glow = { 0,0,0 };
                    }
                    // get light values
                    if (smoothLighting)
                        self->getSmoothLighting(block, 3, lighting, shadows, lights);
                    else
                        self->getLighting(block, 3, lighting, shadows, lights);

                    glm::u8vec4 tuv_top[8];
                    memcpy(tuv_top, BlockInfo::Blocks[blockType].tuv_top, sizeof(tuv_top));
                    if (glassTiling && blockType == BlockInfo::GLASS)
                    {
                        bool closeTo[9]
                        {
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ + 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX + 1][blockZ + 1][blockW][blockY]),
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY]),
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ - 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX + 1][blockZ - 1][blockW][blockY])
                        };

                        tilingLol(tuv_top, closeTo);
                    }

                    // add side
                    mesh.addMeshSide(BlockInfo::cube_verts_y, tuv_top, { blockX, blockY + 1, blockZ, blockW }, lighting);
                }
                if (blockY > 0 && funnyLogic(blockType, self->blocks[blockX][blockZ][blockW][blockY - 1]))
                {
                    // reset light values
                    for (int i = 0; i < 8; i++)
                    {
                        lighting[i].ambient = 0x80;
                        lighting[i].shadow = 0xFF;
                        lighting[i].glow = { 0,0,0 };
                    }
                    // get light values
                    if (smoothLighting)
                        self->getSmoothLighting(block, 2, lighting, shadows, lights);
                    else
                        self->getLighting(block, 2, lighting, shadows, lights);

                    glm::u8vec4 tuv_bottom[8];
                    memcpy(tuv_bottom, BlockInfo::Blocks[blockType].tuv_bottom, sizeof(tuv_bottom));

                    if (glassTiling && blockType == BlockInfo::GLASS)
                    {
                        bool closeTo[9]
                        {
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ + 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX][blockZ + 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX + 1][blockZ + 1][blockW][blockY]),
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX][blockZ][blockW][blockY]),     funnyLogic2(blockType, self->blocks[blockX + 1][blockZ][blockW][blockY]),
                            funnyLogic2(blockType, self->blocks[blockX - 1][blockZ - 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX][blockZ - 1][blockW][blockY]), funnyLogic2(blockType, self->blocks[blockX + 1][blockZ - 1][blockW][blockY])
                        };

                        tilingLol(tuv_bottom, closeTo);
                    }

                    // add side
                    mesh.addMeshSide(BlockInfo::cube_verts_y, tuv_bottom, { blockX, blockY, blockZ, blockW }, lighting);
                }
            }
        }
    }
}

$hook(void, StateTitleScreen, init, StateManager& s)
{
    ResourceManager::loadArrayTexture( fdm::stl::string("../../") + getModPath(modID) + "/tiles.png", cols, rows);
    ResourceManager::textures->at("tiles.png")->ID = ResourceManager::textures->at( fdm::stl::string("../../") + getModPath(modID) + "/tiles.png")->ID;

    original(self, s);
}

// settings (omg first ever public open-sourced mod with custom settings?????!/?!?!?!?!?/1/1/?!//1?!/!/1/!?)
using namespace fdm::gui;

CheckBox glassTilingCB;

void glassTilingCBCallback(void* user, bool checked)
{
    glassTiling = checked;

    // update chunks pls
    StateSettings::instanceObj->lightingOptionsChanged = true;
}

$hook(void, StateSettings, init, StateManager& s)
{
    original(self, s);

    glassTilingCB = CheckBox{};
    glassTilingCB.text = "Glass Tiling";
    glassTilingCB.alignX(ALIGN_CENTER_X);
    glassTilingCB.alignY(ALIGN_TOP);
    glassTilingCB.offsetY(self->lightsCheckBox.yOffset + 50);
    glassTilingCB.checked = glassTiling;
    glassTilingCB.callback = glassTilingCBCallback;

    self->mainContentBox.addElement(&glassTilingCB);
}

#include <fstream>

$hook(void, StateSettings, load, GLFWwindow* window)
{
    original(self, window);

    std::ifstream settingsFile("settings.json");
    if (!settingsFile.is_open()) return;
    nlohmann::json settings = nlohmann::json::parse(settingsFile);
    settingsFile.close();

    if (!settings.contains("glassTiling") || !settings["glassTiling"].is_boolean())
        settings["glassTiling"] = true;
    glassTiling = settings["glassTiling"];
}

$hook(void, StateSettings, save)
{
    original(self);

    // read current settings file
    std::ifstream settingsFileR("settings.json");
    if (!settingsFileR.is_open()) return;

    nlohmann::json settings = nlohmann::json::parse(settingsFileR);
    settingsFileR.close();

    // set glassTiling to its real value
    settings["glassTiling"] = glassTiling;

    // write back to the settings file
    std::ofstream settingsFileW("settings.json");
    if (!settingsFileW.is_open()) return;

    settingsFileW << settings.dump(2); // add some funny 2 space formatting (kill me) that the original game doesnt do but i do in both this mod and 4dmodloader!!!

    settingsFileW.close();
}

$hook(void, StateIntro, init, StateManager& s)
{
	original(self, s);

    // initialize opengl stuff
    glewExperimental = true;
    glewInit();
    glfwInit();
}