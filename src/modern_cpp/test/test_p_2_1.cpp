#if __cplusplus >= 201103L
    #define INLINE inline
#else
#define INLINE __attribute__((__always_inline__))
#endif

int main() {
    // INLINE
    return 0;
}