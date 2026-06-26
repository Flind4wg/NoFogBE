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
            void* sym = dlsym(handle, "?_setupFog@@YAXAEAVRenderContext@@M@Z");
            if (!sym) {
                sym = dlsym(handle, "?setupFog@RenderDragon@@YAXAEAVRenderContext@@M@Z");
            }
            if (sym) {
                patch_memory((uintptr_t)sym, 0xD65F03C0);
            }
        }
    }
}
