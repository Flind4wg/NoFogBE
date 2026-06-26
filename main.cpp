#include <hook.h>

TCHAR_HOOK(void, "?applyFog@FogManager@@QEAAXAEAVRenderContext@@AEAVPlayer@@M@Z", 
           void* renderContext, void* player, float fogDistance) {
    original(renderContext, player, 999999.0f); 
}

void entry() {
}
