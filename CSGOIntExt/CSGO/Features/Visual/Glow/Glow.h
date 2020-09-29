#pragma once

#include "../../../SDK/SDK.h"

struct fColor_t { float r, g, b, a; };

class C_Glow
{
public:
	void Run();

private:
	void ForceGlow(DWORD dwBase, int nIndex, fColor_t clrGlow);
    bool ShouldRun();

    struct GlowObject_t
    {
        float r;
        float g;
        float b;
        float a;
        char __pad0[4];
        float __pad1;
        float m_flBloomAmount;
        float __pad2;
        bool m_bRenderWhenOccluded;
        bool m_bRenderWhenUnoccluded;
        bool m_bFullBloomRender;
        char __pad3;
        int m_nFullBloomStencilTestValue;
        int m_nGlowStyle;
        int m_nSplitScreenSlot;
        int m_nNextFreeSlot;
    };

    GlowObject_t m_sGlowObj;
};

extern C_Glow gGlow;