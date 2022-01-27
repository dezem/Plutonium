#include <pu/ui/elm/elm_Toggle.hpp>
#include <pu/ui/ui_Application.hpp>

namespace pu::ui::elm
{
    static s32 prev_touchcount = 0;

    Toggle::Toggle(s32 X, s32 Y, String Content, u64 Key, Color Color) : Element::Element()
    {
        this->x = X;
        this->y = Y;
        this->key = Key;
        this->cnt = Content;
        this->clr = Color;
        this->fnt_name = "DefaultFont@25";
        this->fsize = 25;
        this->togfact = 255;
        this->checked = false;
        this->ntex = render::RenderText(this->fnt_name, Content, Color);
    }

    Toggle::~Toggle()
    {
        if (this->ntex != nullptr)
        {
            render::DeleteTexture(this->ntex);
            this->ntex = nullptr;
        }
    }

    s32 Toggle::GetX()
    {
        return this->x;
    }

    void Toggle::SetX(s32 X)
    {
        this->x = X;
    }

    s32 Toggle::GetY()
    {
        return this->y;
    }

    void Toggle::SetY(s32 Y)
    {
        this->y = Y;
    }

    s32 Toggle::GetWidth()
    {
        return 0;
    }

    s32 Toggle::GetHeight()
    {
        return 0;
    }

    String Toggle::GetContent()
    {
        return this->cnt;
    }

    void Toggle::SetContent(String Content)
    {
        this->cnt = Content;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt_name, Content, this->clr);
    }

    void Toggle::SetFont(String font_name)
    {
        this->fnt_name = font_name;
        this->ntex = render::RenderText(this->fnt_name, this->cnt, this->clr);
    }

    Color Toggle::GetColor()
    {
        return this->clr;
    }

    void Toggle::SetColor(Color Color)
    {
        this->clr = Color;
        render::DeleteTexture(this->ntex);
        this->ntex = render::RenderText(this->fnt_name, this->cnt, Color);
    }

    u64 Toggle::GetKey()
    {
        return this->key;
    }

    void Toggle::SetKey(u64 Key)
    {
        this->key = Key;
    }

    bool Toggle::IsChecked()
    {
        return this->checked;
    }

    void Toggle::OnRender(render::Renderer::Ref &Drawer, s32 X, s32 Y)
    {
        s32 tw = render::GetTextWidth(this->fnt_name, this->cnt);
        s32 th = render::GetTextHeight(this->fnt_name, this->cnt);
        s32 rw = th;
        s32 rh = (2 * th);
        s32 rx = X;
        s32 ry = Y;
        s32 tx = rx + rw + (th / 2);
        s32 ty = ry + (th / 2);
        if(this->checked)
        {
            Drawer->RenderRectangleFill({ 130, 130, 130, 255 }, rx, ry, rw, rh);
            if(this->togfact < 255)
            {
                Drawer->RenderRectangleFill({ this->clr.R, this->clr.G, this->clr.B, (255 - this->togfact) }, rx, ry, rw, rh);
                this->togfact += 48;
            }
            else Drawer->RenderRectangleFill({ 130, 130, 130, 255 }, rx, ry, rw, rh);
        }
        else
        {
            Drawer->RenderRectangleFill(this->clr, rx, ry, rw, rh);
            if(this->togfact > 0)
            {
                Drawer->RenderRectangleFill({ 130, 130, 130, this->togfact }, rx, ry, rw, rh);
                this->togfact -= 48;
            }
            else Drawer->RenderRectangleFill(this->clr, rx, ry, rw, rh);
        }
        Drawer->RenderTexture(this->ntex, tx, ty);
    }

    void Toggle::OnInput(u64 Down, u64 Up, u64 Held, Touch Pos)
    {
        if ((Down & this->key) || (Application::GetTouchState().count == 0 && prev_touchcount == 1)) {
            prev_touchcount = 0;
            this->checked = !this->checked;
        }
        if (Application::GetTouchState().count == 1)
            prev_touchcount = 1;
    }
}
