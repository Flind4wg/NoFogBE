#include <sys/mman.h>
#include <unistd.h>
#include <dlfcn.h>
#include <stdint.h>

void patch_memory(uintptr_t address, uint32_t value) {
    uintptr_t page = address & ~(4096 - 1);
    mprotect((void*)page, 4096, PROT_READ | PROT_WRITE | PROT_EXEC);
    *(uint32_t*)address = value;
    mprotect((void*)page, 4096, PROT_READ | PROT_EXEC);
}

extern "C" {
    void _init(void) {
        void* handle = dlopen("libminecraftpe.so", RTLD_LAZY);
        if (handle) {
            const char* symbols[] = {
                "?setupFog@LevelRenderer@@QEAAXAEAVRenderContext@@AEAVCamera@@M@Z",
                "?renderFog@@YAXAEAVRenderContext@@M@Z",
                "?setupFog@FogManager@@QEAAXAEAVRenderContext@@AEAVCamera@@M@Z"
            };
            for (int i = 0; i < 3; i++) {
                void* sym = dlsym(handle, symbols[i]);
                if (sym) {
                    patch_memory((uintptr_t)sym, 0xD65F03C0);
                    break;
                }
            }
        }
    }
}
