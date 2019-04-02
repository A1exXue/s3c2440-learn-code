#include "s3c2440.h"
typedef void (*irq_funcp)(void);
irq_funcp irq_array[32];
void irq_register(unsigned char irq,irq_funcp irq_handle_func);


