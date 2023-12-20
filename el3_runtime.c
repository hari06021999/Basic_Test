/*
 * el3_runtime.c
 *
 *  Created on: 19-Dec-2023
 *      Author: accord_manet
 */
#include "el3_runtime.h"
#include <string.h>
#include "my_printf.h"

#define get_el3state_ctx(h)	(&((cpu_context_t *) h)->el3state_ctx)

#define read_ctx_reg(ctx, offset)	((ctx)->ctx_regs[(offset) >> DWORD_SHIFT])

uint8_t rt_svc_descs_indices[MAX_RT_SVCS] = {-1};
static int32_t validate_rt_svc_desc(const rt_svc_desc_t *desc);
static inline uint32_t get_unique_oen(uint32_t oen, uint32_t call_type);
static inline context_pas_t get_cpu_context_index(uint32_t security_state);

void runtime_svc_init(void)
{
	my_printf("runtime_svc_init\r\n");

	int rc = 0;
	uint8_t index, start_idx, end_idx;
	rt_svc_desc_t *rt_svc_descs;

	/* Assert the number of descriptors detected are less than maximum indices */
	assert((RT_SVC_DESCS_END >= RT_SVC_DESCS_START) &&
			(RT_SVC_DECS_NUM < MAX_RT_SVCS));

	/* If no runtime services are implemented then simply bail out */
	if (RT_SVC_DECS_NUM == 0U)
		return;

	/* Initialise internal variables to invalid state */
	//memset(rt_svc_descs_indices, -1, sizeof(rt_svc_descs_indices));

	rt_svc_descs = (rt_svc_desc_t *) __RT_SVC_DESCS_START__;
	for (index = 0U; index < RT_SVC_DECS_NUM; index++) {
		rt_svc_desc_t *service = &rt_svc_descs[index];

		/*
		 * An invalid descriptor is an error condition since it is
		 * difficult to predict the system behaviour in the absence
		 * of thi	(void)memset(rt_svc_descs_indices, -1, sizeof(rt_svc_descs_indices));
		 * s service.
		 */
		rc = validate_rt_svc_desc(service);
		if (rc != 0) {
			my_printf("Invalid runtime service descriptor %p\r\n",
				(void *) service);
			my_printf("panic warn\r\n");
		}

		/*
		 * The runtime service may have separate rt_svc_desc_t
		 * for its fast smc and yielding smc. Since the service itself
		 * need to be initialized only once, only one of them will have
		 * an initialisation routine defined. Call the initialisation
		 * routine for this runtime service, if it is defined.
		 */
		if (service->init != NULL) {
			rc = service->init();
			if (rc != 0) {
				//(void)memset(rt_svc_descs_indices, -1, sizeof(rt_svc_descs_indices));
				my_printf("Error initializing runtime service %s\r\n",
						service->name);
				continue;
			}
		}

		/*
		 * Fill the indices corresponding to the start and end
		 * owning entity numbers with the index of the
		 * descriptor which will handle the SMCs for this owning
		 * entity range.
		 */
		start_idx = (uint8_t)get_unique_oen(service->start_oen,
						    service->call_type);
		end_idx = (uint8_t)get_unique_oen(service->end_oen,
						  service->call_type);
		assert(start_idx <= end_idx);
		assert(end_idx < MAX_RT_SVCS);
		for (; start_idx <= end_idx; start_idx++)
			rt_svc_descs_indices[start_idx] = index;
	}
}
static int32_t validate_rt_svc_desc(const rt_svc_desc_t *desc)
{
	my_printf("validate_rt_svc_desc\r\n");

	if (desc == NULL)
		return -EINVAL;

	if (desc->start_oen > desc->end_oen)
		return -EINVAL;

	if (desc->end_oen >= OEN_LIMIT)
		return -EINVAL;

	if ((desc->call_type != SMC_TYPE_FAST) &&
	    (desc->call_type != SMC_TYPE_YIELD))
		return -EINVAL;

	/* A runtime service having no init or handle function doesn't make sense */
	if ((desc->init == NULL) && (desc->handle == NULL))
		return -EINVAL;

	return 0;
}


static inline uint32_t get_unique_oen(uint32_t oen, uint32_t call_type)
{
	return ((call_type & FUNCID_TYPE_MASK) << FUNCID_OEN_WIDTH) |
		(oen & FUNCID_OEN_MASK);
}


#define get_cpu_data(_m)		   _cpu_data()->_m
void *cm_get_context(uint32_t security_state)
{
	assert(sec_state_is_valid(security_state));

	return get_cpu_data(cpu_context[get_cpu_context_index(security_state)]);
}

static inline context_pas_t get_cpu_context_index(uint32_t security_state)
{
	if (security_state == SECURE) {
		return CPU_CONTEXT_SECURE;
	} else {
#if ENABLE_RME
		if (security_state == NON_SECURE) {
			return CPU_CONTEXT_NS;
		} else {
			assert(security_state == REALM);
			return CPU_CONTEXT_REALM;
		}
#else
		assert(security_state == NON_SECURE);
		return CPU_CONTEXT_NS;
#endif
	}
}


void cm_write_scr_el3_bit(uint32_t security_state,
			  uint32_t bit_pos,
			  uint32_t value)
{
	my_printf("cm_write_scr_el3_bit\r\n");
	cpu_context_t *ctx;
	el3_state_t *state;
	u_register_t scr_el3;

	ctx = cm_get_context(security_state);
	assert(ctx != NULL);

	/* Ensure that the bit position is a valid one */
	assert(((1UL << bit_pos) & SCR_VALID_BIT_MASK) != 0U);

	/* Ensure that the 'value' is only a bit wide */
	assert(value <= 1U);

	/*
	 * Get the SCR_EL3 value from the cpu context, clear the desired bit
	 * and set it to its new value.
	 */
	state = get_el3state_ctx(ctx);
//	scr_el3 = read_ctx_reg(state, CTX_SCR_EL3);
//	scr_el3 &= ~(1UL << bit_pos);
//	scr_el3 |= (u_register_t)value << bit_pos;
//	write_ctx_reg(state, CTX_SCR_EL3, scr_el3);
}
