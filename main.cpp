
#include <4dm.h>
using fdm::Chunk;
using fdm::BlockInfo;
using fdm::Tex2D;

template <typename type>
inline constexpr void swap(type& a, type& b) {
    type temp = a;
    a = b;
    b = temp;
}

inline constexpr BlockInfo::TYPE getBlock( const decltype(Chunk::blocks)& blocks, const glm::u8vec4& block ){
    return static_cast<BlockInfo::TYPE>( blocks[block.x][block.z][block.w][block.y] );
}

inline const std::unordered_map<glm::u8vec4,glm::u8vec4*> cube_verts = {
    {{-1, 0, 0, 0}, BlockInfo::cube_verts_x},
    {{+1, 0, 0, 0}, BlockInfo::cube_verts_x},
    {{ 0,-1, 0, 0}, BlockInfo::cube_verts_y},
    {{ 0,+1, 0, 0}, BlockInfo::cube_verts_y},
    {{ 0, 0,-1, 0}, BlockInfo::cube_verts_z},
    {{ 0, 0,+1, 0}, BlockInfo::cube_verts_z},
    {{ 0, 0, 0,-1}, BlockInfo::cube_verts_w},
    {{ 0, 0, 0,+1}, BlockInfo::cube_verts_w},
};

void meshGlassBlockSide( Chunk::ChunkMesh&, glm::u8vec4, bool planarNeighbours[3][3][3], glm::i8vec4, BlockInfo::VertLighting* );
$hook(void, Chunk, generateMeshSection, Chunk::ChunkMesh& mesh, uint8_t startY, bool smoothLighting, bool shadows, bool lights) {
    
    
    std::vector<glm::u8vec4> glassBlocks;
    
    // hide glass
    for (int blockX = 1; blockX <= 8; blockX++)
    for (int blockY = startY; blockY < startY + 16; blockY++)
    for (int blockZ = 1; blockZ <= 8; blockZ++)
    for (int blockW = 1; blockW <= 8; blockW++)
    {
        if ( self->blocks[blockX][blockZ][blockW][blockY] != BlockInfo::GLASS )
            continue;
        
        self->blocks[blockX][blockZ][blockW][blockY] = BlockInfo::AIR;
        glassBlocks.push_back({ blockX, blockY, blockZ, blockW });
    }
    
    // generate mesh without glass
    original(self, mesh, startY, smoothLighting, shadows, lights);
    
    // restore glass
    for ( auto glassBlock : glassBlocks )
        self->blocks[glassBlock.x][glassBlock.z][glassBlock.w][glassBlock.y] = BlockInfo::GLASS;
    
    // generate glass mesh
    for ( auto glassBlock : glassBlocks ) {
        
        bool neighbours[3][3][3][3];
        
        for (int Δx = -1; Δx <= 1; Δx++)
        for (int Δy = -1; Δy <= 1; Δy++)
        for (int Δz = -1; Δz <= 1; Δz++)
        for (int Δw = -1; Δw <= 1; Δw++)
            neighbours[1+Δx][1+Δy][1+Δz][1+Δw] =
                glassBlock.y+Δy > 127 ? false :
                    BlockInfo::GLASS == getBlock(self->blocks, glassBlock + glm::u8vec4({Δx, Δy, Δz, Δw}) );
        
        int faceIndex = -1;
        for ( glm::i8vec4 offset : std::initializer_list<glm::i8vec4>{
            {-1, 0, 0, 0},
            {+1, 0, 0, 0},
            { 0,-1, 0, 0},
            { 0,+1, 0, 0},
            { 0, 0,-1, 0},
            { 0, 0,+1, 0},
            { 0, 0, 0,-1},
            { 0, 0, 0,+1},
        } ) {
            
            const glm::u8vec4 neighbour = glassBlock + glm::u8vec4(offset);
            const uint8_t neighbourType = ( neighbour.y <= 127 ) ? getBlock(self->blocks, neighbour ) : BlockInfo::AIR;
            faceIndex++;
            
            if ( neighbourType == BlockInfo::GLASS || BlockInfo::Blocks[neighbourType].opaque )
                continue;
            
            // reset light values
            BlockInfo::VertLighting lighting[8];
            for (int i = 0; i < 8; i++)
            {
                lighting[i].ambient = 0xC0;
                lighting[i].shadow = 0xFF;
                lighting[i].glow = { 0,0,0 };
            }
            // get light values
            (self->*(smoothLighting ? &self->getSmoothLighting : &self->getLighting))
                (glassBlock, faceIndex, lighting, shadows, lights);
            
            int i = 0;
            bool planarNeighbours[3][3][3];
            for (int Δx = offset.x ? 0 : -1; Δx <= (offset.x ? 0 : 1); Δx++)
            for (int Δy = offset.y ? 0 : -1; Δy <= (offset.y ? 0 : 1); Δy++)
            for (int Δz = offset.z ? 0 : -1; Δz <= (offset.z ? 0 : 1); Δz++)
            for (int Δw = offset.w ? 0 : -1; Δw <= (offset.w ? 0 : 1); Δw++)
            {
                /*
                    look at this map to hwy based on surface normal:
                        x - zyw
                        y - xzw
                        z - xyw
                        w - xyz
                    
                    there is no order in this. This has flipped chirality, the directions aren't in order either, wtf?
                */
                if (offset.x)  // whyyyy mash whyyyyyy
                    swap(Δy,Δz);
                
                planarNeighbours[i/3/3][(i/3)%3][i%3] = neighbours[1+Δx][1+Δy][1+Δz][1+Δw];  // map to hwy
                i++;
                
                if (offset.x)  // whyyyy mash whyyyyyy
                    swap(Δy,Δz);
            }
            
            meshGlassBlockSide( mesh, max(glassBlock,neighbour), planarNeighbours, offset, lighting );
        }
    }
}

void makeCell(glm::ivec3, Chunk::ChunkMesh& mesh, glm::i8vec4 offset, glm::u8vec4 _side_origin, BlockInfo::VertLighting* _lighting);
void meshGlassBlockSide( Chunk::ChunkMesh& mesh, glm::u8vec4 _side_origin, bool planarNeighbours[3][3][3], glm::i8vec4 _offset, BlockInfo::VertLighting* _lighting ){
    // coords are  ( h, w, y )  arbitrarily to show these are not world coords
    
    // remove elements that would be covered by larger (higher dim) elements
    for (int h = -1; h <= 1; h++)
    for (int w = -1; w <= 1; w++)
    for (int y = -1; y <= 1; y++)
    {
        if (planarNeighbours[1+h][1+w][1+y])
            continue;
        
        // if there is an empty spot, a border, in a more central position, this makes borders in the more cornery positions unnecessary
        for (int h2 = h ? h : -1; h2 <= (h ? h : 1); h2++)
        for (int w2 = w ? w : -1; w2 <= (w ? w : 1); w2++)
        for (int y2 = y ? y : -1; y2 <= (y ? y : 1); y2++)
        {
            planarNeighbours[1+h2][1+w2][1+y2] = true;
        }
        // restore the "center" responsible
        planarNeighbours[1+h][1+w][1+y] = false;
    }
    
    for (int h = -1; h <= 1; h++)
    for (int w = -1; w <= 1; w++)
    for (int y = -1; y <= 1; y++)
    {
        if (planarNeighbours[1+h][1+w][1+y])
            continue;
        
        makeCell( {h,w,y}, mesh, _offset, _side_origin, _lighting);
    }
}

static int dimglass[3];

// $exec {
//     fdm::startConsole();
//     FILE* fp;
//     freopen_s(&fp, "CONOUT$", "w", stdout);
// }
void makeCell(glm::ivec3 alignment, Chunk::ChunkMesh& mesh, glm::i8vec4 offset, glm::u8vec4 _side_origin, BlockInfo::VertLighting* _lighting) {
    
    const int dim = sizeof(alignment)/sizeof(alignment[0]);  // 3
    
    // 0 is corner, 1 is edge, 2 is ridge, 3 would be the entire cell but cannot happen
    const int symDim = dim - alignment[0]*alignment[0] - alignment[1]*alignment[1] - alignment[2]*alignment[2];
    
    glm::u8vec4 tuv_side[8];
    memcpy(tuv_side, BlockInfo::Blocks[BlockInfo::GLASS].tuv_side, sizeof(tuv_side));
    
    for (glm::u8vec4& tuvec : tuv_side)
        tuvec[dim] = dimglass[symDim];
    
    // if (symDim == 2) {
    //     for (int i = 0; i < dim; i++)
    //         printf("%d ",alignment[i]);
    //     printf("\n");
    // }
    
    // random weird stuff that breaks. Prob cause mashs convention
    // there is at least one more with symDim==1
    if (symDim == 1 && offset.y && !alignment[1])
        alignment[0] = -alignment[0];
    
    if (symDim == 2)
        alignment[1] = -alignment[1];
    
    auto alignRot = alignment;
    int swapTo = -1;
    for (int swapFrom = 0; swapFrom < symDim; swapFrom++) { // find new homes for the symmetry-axes of the texture
        while (alignment[++swapTo] != 0);  // find a swapTo that is 0, that will accept the symmetry-axis
        for (glm::u8vec4& tuvec : tuv_side)
            swap(tuvec[swapFrom],tuvec[swapTo]);
        swap(alignRot[swapFrom],alignRot[swapTo]);
    }
    
    for (glm::u8vec4& tuvec : tuv_side)
        for (int i = 0; i < dim; i++)
            if (alignRot[i] > 0)
                tuvec[i] ^= true;
    
    mesh.addMeshSide(cube_verts.at(offset), tuv_side, _side_origin, _lighting);
}


// loadArrayTexture doesn't have the filename, so we bridge the info from here
inline bool isLoadingTilemap = false;
$hookStatic(bool, ResourceManager, loadArrayTexture, const fdm::stl::string& filename, int cols, int rows) {
    if (filename == "tiles.png")
        isLoadingTilemap = true;
    
    return original(filename, cols, rows);
}

const uint32_t glassColor = 0xfffbbfb9;  // in little endian, so reversed bytes (abgr)

#define addTexture(id) \
    id = --textureIndex; \
    for (size_t h = 0; h < 16; h++) \
    for (size_t w = 0; w < 16; w++) \
    for (size_t y = 0; y < 16; y++) \
        data[ ((15-w)+y*16)*cols*16 + (h+(textureIndex)*16) ] =
$hook(bool, Tex2D, loadArrayTexture, const unsigned char* ogData, GLint texWidth, int texHeight, int channels, int cols, int rows) {
    if (!isLoadingTilemap)
        return original(self, ogData, texWidth, texHeight, channels, cols, rows);
    
    isLoadingTilemap = false;
    
    auto* data = new uint32_t[(rows*16 * cols*16 * channels)/sizeof(uint32_t)];
    memcpy(data, ogData, rows*16 * cols*16 * channels );
    
    
    int textureIndex = cols;
    
    addTexture(dimglass[0])
        (h == 0 && w == 0 && y == 0) ? glassColor : 0;
        // (h == 0 && w == 0 && y == 0) ? glassColor :
        // (h < 3 && w == 0 && y == 0) ?  0xff0000ff :
        // (h == 0 && w < 3 && y == 0) ?  0xff00ff00 :
        // (h == 0 && w == 0 && y < 3) ?  0xffff0000 :
        // 0;
    
    addTexture(dimglass[1])
        (w == 0 && y == 0) ? glassColor : 0;
        // (w == 0 && y == 0) ? glassColor :
        // (w < 3 && y == 0) ?  0xff00ff00 :
        // (w == 0 && y < 3) ?  0xffff0000 :
        // 0;
        
    addTexture(dimglass[2])
        (y == 0) ? glassColor : 0;
    
    
    return original(self, reinterpret_cast<unsigned char*>(data), texWidth, texHeight, channels, cols, rows);
}