#ifndef LIBHELPER_H
#define LIBHELPER_H


inline int absdsq(int val, int sample_val) {

    int tmp;
    __asm__ volatile (
            "absd   %[t], %[x], %[y]\n\t"
            : [t] "=r"(tmp)
    : [x] "r"(val), [y] "r"(sample_val)
    );
    return tmp;
}
#endif
