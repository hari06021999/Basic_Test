

void bl31_main(void)
{
	

	/* Perform platform setup in BL31 */
	bl31_platform_setup();

	/* Initialise helper libraries */
	bl31_lib_init();

    /* Initialize the runtime services e.g. psci. */
	my_printf("BL31: Initializing runtime services\n");
	runtime_svc_init();

    /*
	 * We are ready to enter the next EL. Prepare entry into the image
	 * corresponding to the desired security state after the next ERET.
	 */
	bl31_prepare_next_image_entry();

	console_flush();

	/*
	 * Perform any platform specific runtime setup prior to cold boot exit
	 * from BL31
	 */
	bl31_plat_runtime_setup();
}