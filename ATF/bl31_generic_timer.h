
#include <stdint.h>

typedef struct timer_ops {
	uint32_t (*get_timer_value)(void);
	uint32_t clk_mult;
	uint32_t clk_div;
} timer_ops_t;

void mdelay(uint32_t msec);
void udelay(uint32_t usec);
void timer_init(const timer_ops_t *ops_ptr);

void generic_delay_timer_init_args(uint32_t mult, uint32_t div);
void generic_delay_timer_init(void);