#ifndef INCLUDE_PLATFORM
#define INCLUDE_PLATFORM

// Used to prefix the root directory for web platforms.
#ifdef PLATFORM_WEB
#define FILESYS_NAME(name) std::string("/BLOCK/") + name
#else
#define FILESYS_NAME(name) name
#endif

// Used to sync fileystem changes on web platforms.
#ifdef PLATFORM_WEB
#define FILESYS_SYNC() EM_ASM(FS.syncfs(function(err) { assert(!err); }))
#else
#define FILESYS_SYNC()
#endif

#endif // INCLUDE_PLATFORM
