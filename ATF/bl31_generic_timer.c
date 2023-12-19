#include "bl31_generic_timer.h"


/* Ticks elapsed in one second by a signal of 1 MHz */
#define MHZ_TICKS_PER_SEC 1000000



static timer_ops_t ops;

/***********************************************************
 * Delay for the given number of microseconds. The driver must
 * be initialized before calling this function.
 ***********************************************************/
void udelay(uint32_t usec)
{
	assert(timer_ops != NULL &&
		(timer_ops->clk_mult != 0) &&
		(timer_ops->clk_div != 0) &&
		(timer_ops->get_timer_value != NULL));

	uint32_t start, delta, total_delta;

	assert(usec < UINT32_MAX / timer_ops->clk_div);

	start = timer_ops->get_timer_value();

	/* Add an extra tick to avoid delaying less than requested. */
	total_delta =
		div_round_up(usec * timer_ops->clk_div, timer_ops->clk_mult) + 1;

	do {
		/*
		 * If the timer value wraps around, the subtraction will
		 * overflow and it will still give the correct result.
		 */
		delta = start - timer_ops->get_timer_value(); /* Decreasing counter */

	} while (delta < total_delta);
}

/***********************************************************
 * Delay for the given number of milliseconds. The driver must
 * be initialized before calling this function.
 ***********************************************************/
void mdelay(uint32_t msec)
{
	udelay(msec*1000);
}

/***********************************************************
 * Initialize the timer. The fields in the provided timer
 * ops pointer must be valid.
 ***********************************************************/
void timer_init(const timer_ops_t *ops_ptr)
{
	assert(ops_ptr != NULL  &&
		(ops_ptr->clk_mult != 0) &&
		(ops_ptr->clk_div != 0) &&
		(ops_ptr->get_timer_value != NULL));

	timer_ops = ops_ptr;
}

static uint32_t get_timer_value(void)
{
	/*
	 * Generic delay timer implementation expects the timer to be a down
	 * counter. We apply bitwise NOT operator to the tick values returned
	 * by read_cntpct_el0() to simulate the down counter. The value is
	 * clipped from 64 to 32 bits.
	 */
	return (uint32_t)(~read_cntpct_el0());
}

void generic_delay_timer_init_args(uint32_t mult, uint32_t div)
{
	ops.get_timer_value	= get_timer_value;
	ops.clk_mult		= mult;
	ops.clk_div		= div;

	timer_init(&ops);

	my_printf("Generic delay timer configured with mult=%u and div=%u\n",
		mult, div);
}

void generic_delay_timer_init(void)
{
	/* Value in ticks */
	unsigned int mult = MHZ_TICKS_PER_SEC;

	/* Value in ticks per second (Hz) */
	unsigned int div  = plat_get_syscnt_freq2();

	/* Reduce multiplier and divider by dividing them repeatedly by 10 */
	while ((mult % 10 == 0) && (div % 10 == 0)) {
		mult /= 10;
		div /= 10;
	}

	generic_delay_timer_init_args(mult, div);
}

