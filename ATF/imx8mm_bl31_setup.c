#include "bl31_generic_timer.h"

void bl31_platform_setup(void)
{
	generic_delay_timer_init();

	/* select the CKIL source to 32K OSC */
	mmio_write_32(0x30360124, 0x1);

	/* init the dram info */
	dram_info_init(SAVED_DRAM_TIMING_BASE);

	/* init the GICv3 cpu and distributor interface */
	plat_gic_driver_init();
	plat_gic_init();

	/* gpc init */
	imx_gpc_init();

}