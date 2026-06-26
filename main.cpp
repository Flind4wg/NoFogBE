#include <llapi/LoggerAPI.h>
#include <hook.h>

extern Logger logger;

TCHAR_HOOK(void, "?applyFog@FogManager@@QEAAXAEAVRenderContext@@AEAVPlayer@@M@Z", 
           void* renderContext, void* player, float fogDistance) {
    original(renderContext, player, 999999.0f); 
}

void entry() {
    logger.info("NoFog Loaded.");
}

