
/*

    Plutonium library

    @file Image.hpp
    @brief An Image is an Element showing a picture. (JPEG, PNG, TGA, BMP)
    @author XorTroll

    @copyright Plutonium project - an easy-to-use UI framework for Nintendo Switch homebrew

*/

#pragma once
#include <pu/ui/elm/elm_Element.hpp>

namespace pu::ui::elm
{
    class Image : public Element
    {
        public:
            Image(i32 X, i32 Y, String Image);
            Image(s32 X, s32 Y, void* jpegbuffer, s32 size);
            Image(s32 X, s32 Y, void* rgbBuffer, u64 width, u64 height, u8 depth);
            PU_SMART_CTOR(Image)
            ~Image();

            i32 GetX();
            void SetX(i32 X);
            i32 GetY();
            void SetY(i32 Y);
            i32 GetWidth();
            void SetWidth(i32 Width);
            i32 GetHeight();
            void SetHeight(i32 Height);
            float GetRotation();
            void SetRotation(float Angle);
            String GetImage();
            void SetImage(String Image);
            void SetJpegImage(void* buffer, s32 size);
            void SetRgbImage(void* buffer, u64 width, u64 height, u8 depth = 4);
            bool IsImageValid();
            void OnRender(render::Renderer::Ref &Drawer, i32 X, i32 Y);
            void OnInput(u64 Down, u64 Up, u64 Held, Touch Pos);
        private:
            String img;
            sdl2::Texture ntex;
            render::TextureRenderOptions rendopts;
            i32 x;
            i32 y;
    };
}