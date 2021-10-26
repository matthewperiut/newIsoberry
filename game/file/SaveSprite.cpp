#include "SaveSprite.h"

#include "../external/olcPixelGameEngine.h"
#include "../external/png/svpng.h"
#include "../external/png/lodepng.h"

#include <ostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using namespace olc;

// Thank you lode png for compression
void compress(std::string filepath) {
    std::vector<unsigned char> image;
    unsigned w, h;
    std::vector<unsigned char> buffer;
    unsigned error;

    lodepng::load_file(buffer, filepath);
    lodepng::decode(image, w, h, buffer);
    buffer.clear();

    //Now encode as hard as possible with several filter types and window sizes

    lodepng::State state;
    state.encoder.filter_palette_zero = 0; //We try several filter types, including zero, allow trying them all on palette images too.
    state.encoder.add_id = false; //Don't add LodePNG version chunk to save more bytes
    state.encoder.text_compression = 1; //Not needed because we don't add text chunks, but this demonstrates another optimization setting
    state.encoder.zlibsettings.nicematch = 258; //Set this to the max possible, otherwise it can hurt compression
    state.encoder.zlibsettings.lazymatching = 1; //Definitely use lazy matching for better compression
    state.encoder.zlibsettings.windowsize = 32768; //Use maximum possible window size for best compression

    size_t bestsize = 0;
    bool inited = false;

    int beststrategy = 0;
    LodePNGFilterStrategy strategies[4] = { LFS_ZERO, LFS_MINSUM, LFS_ENTROPY, LFS_BRUTE_FORCE };
    std::string strategynames[4] = { "LFS_ZERO", "LFS_MINSUM", "LFS_ENTROPY", "LFS_BRUTE_FORCE" };

    // min match 3 allows all deflate lengths. min match 6 is similar to "Z_FILTERED" of zlib.
    int minmatches[2] = { 3, 6 };
    int bestminmatch = 0;

    int autoconverts[2] = { 0, 1 };
    std::string autoconvertnames[2] = { "0", "1" };
    int bestautoconvert = 0;

    int bestblocktype = 0;

    // Try out all combinations of everything
    for (int i = 0; i < 4; i++)   //filter strategy
        for (int j = 0; j < 2; j++)   //min match
            for (int k = 0; k < 2; k++)   //block type (for small images only)
                for (int l = 0; l < 2; l++) { //color convert strategy
                    if (bestsize > 3000 && (k > 0 || l > 0)) continue; /* these only make sense on small images */
                    std::vector<unsigned char> temp;
                    state.encoder.filter_strategy = strategies[i];
                    state.encoder.zlibsettings.minmatch = minmatches[j];
                    state.encoder.zlibsettings.btype = k == 0 ? 2 : 1;
                    state.encoder.auto_convert = autoconverts[l];
                    error = lodepng::encode(temp, image, w, h, state);

                    if (!inited || temp.size() < bestsize)
                    {
                        bestsize = temp.size();
                        beststrategy = i;
                        bestminmatch = state.encoder.zlibsettings.minmatch;
                        bestautoconvert = l;
                        bestblocktype = state.encoder.zlibsettings.btype;
                        temp.swap(buffer);
                        inited = true;
                    }
                }

    lodepng::save_file(buffer, filepath);
}

// Thank you svpng for giving me the ability to save
void save(Sprite* spr, std::string filepath)
{
    auto* v = new std::vector<unsigned char>;
    v->reserve(spr->width * spr->height * 4);

    FILE* fp = fopen(filepath.c_str(), "wb");
    for (int y = 0; y < spr->height; y++)
        for (int x = 0; x < spr->width; x++)
        {
            Pixel color = spr->GetPixel(vi2d(x, y));
            for (int c = 0; c < 4; c++)
            {
                switch (c)
                {
                    case 0: //r
                    v->push_back(color.r);
                    break;
                    case 1: //g
                    v->push_back(color.g);
                    break;
                    case 2: //b
                    v->push_back(color.b);
                    break;
                    case 3: //a
                    v->push_back(color.a);
                    break;
                }
            }
        }

    unsigned char* a = &(*v)[0];
        svpng(fp, spr->width, spr->height, a, 1);
        fclose(fp);
        //compress(filepath);
        delete v;
}

void SaveSprite(Sprite* spr, std::string filepath)
{
    std::thread task(save, spr, filepath);
    task.detach();
}

void SaveSprite(Sprite& spr, std::string filepath)
{
    SaveSprite(&spr, filepath);
}