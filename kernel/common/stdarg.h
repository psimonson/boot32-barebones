#ifndef _STDARG_H_
#define _STDARG_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char *va_list;

#define _VA_SIZE(type) \
	((sizeof(type) + sizeof(int) - 1) & ~(sizeof(int) - 1))

/* ---------------------- Variable arguments --------------------- */
#define va_start(ap, lastarg) \
	(ap = ((va_list)&(lastarg) + _VA_SIZE(lastarg)))

#define va_end(ap)

#define va_arg(ap, type) \
	(ap += _VA_SIZE(type), *((type*)(ap-_VA_SIZE(type))))

#ifdef __cplusplus
}
#endif

#endif
