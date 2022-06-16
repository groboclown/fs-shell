// Pulled from wikipedia
// https://en.wikipedia.org/wiki/Inline_function

#ifndef _FS_SHELL__FORCEINLINE_

#ifdef _MSC_VER
    #define forceinline __forceinline
#elif defined(__GNUC__)
    #define forceinline inline __attribute__((__always_inline__))
#elif defined(__CLANG__)
    #if __has_attribute(__always_inline__)
        #define forceinline inline __attribute__((__always_inline__))
    #else
        #define forceinline inline
    #endif
#else
    #define forceinline inline
#endif

#endif /* _FS_SHELL__FORCEINLINE_ */
