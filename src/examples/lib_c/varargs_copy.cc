#include <stdio.h> // for printf(3)
#include <stdarg.h> // for va_start(3), va_arg(3), va_end(3)

/*
 * This example shows how to use the 'va_copy' function.
 *
 *		Mark Veltzer
 */
void trace(const char *fmt, ...) {
	va_list ap;
	int d;
	char c, *s;
	float f;
	va_start(ap,fmt);
	while (*fmt) {
		switch (*fmt++) {
			case 'f': /* float */
				f = (double)va_arg(ap, double);
				printf("float %f\n", f);
				break;
			case 's': /* string */
				s = va_arg(ap, char *);
				printf("string %s\n", s);
				break;
			case 'd': /* int */
				d = va_arg(ap, int);
				printf("int %d\n", d);
				break;
			case 'c': /* char */
			/* need a cast here since va_arg only
			* takes fully promoted types */
				c = (char)va_arg(ap, int);
				printf("char %c\n", c);
				break;
		}
	}
	va_end(ap);
}

void trace(const char *fmt, ...) __attribute__((format(printf, 1, 2)));

int main(int argc, char **argv, char **envp) {
	printf("sizeof(va_list) is [%d]\n",sizeof(va_list));
	//trace("%s %d %f\n", "Hello", 5, 3.14);
	return(0);
}