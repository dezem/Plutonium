#include <pu/ui/render/render_SDL2.hpp>
#include <pu/ui/render/render_Renderer.hpp>
#include <utility>
#include <unordered_map>

namespace pu::ui::render
{
    sdl2::Texture ConvertToTexture(sdl2::Surface Surface)
    {
        sdl2::Texture tex = SDL_CreateTextureFromSurface(GetMainRenderer(), Surface);
        SDL_FreeSurface(Surface);
        return tex;
    }

    sdl2::Texture LoadImage(std::string Path)
    {
        return ConvertToTexture(IMG_Load(Path.c_str()));
    }

    sdl2::Texture LoadJpegImage(void* buffer, s32 size)
    {
        return ConvertToTexture(IMG_Load_RW(SDL_RWFromMem(buffer, size), size));
    }

    sdl2::Texture LoadRgbImage(void* buffer, u64 width, u64 height, u8 depth) {
        return ConvertToTexture(SDL_CreateRGBSurfaceFrom(buffer, width, height, depth * 8, depth * width, 0x000000ff, 0x0000ff00, 0x00ff0000, depth == 4 ? 0xff000000 : 0));
    }

    i32 GetTextureWidth(sdl2::Texture Texture)
    {
        int w = 0;
        SDL_QueryTexture(Texture, nullptr, nullptr, &w, nullptr);
        return (i32)w;
    }

    i32 GetTextureHeight(sdl2::Texture Texture)
    {
        int h = 0;
        SDL_QueryTexture(Texture, nullptr, nullptr, nullptr, &h);
        return (i32)h;
    }

    void SetAlphaValue(sdl2::Texture Texture, u8 Alpha)
    {
        SDL_SetTextureBlendMode(Texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureAlphaMod(Texture, Alpha);
    }

    void DeleteTexture(sdl2::Texture Texture)
    {
        SDL_DestroyTexture(Texture);
        Texture = nullptr;
    }
}