/*
 * el3_runtime.h
 *
 *  Created on: 19-Dec-2023
 *      Author: accord_manet
 */

#ifndef INCLUDE_EL3_RUNTIME_H_
#define INCLUDE_EL3_RUNTIME_H_
#include <stdint.h>

uint32_t read_tpidr_el3();

extern const volatile unsigned int __RT_SVC_DESCS_START__;
extern const volatile unsigned int __RT_SVC_DESCS_END__;

#define SECURE		0
#define NON_SECURE	1

typedef unsigned long u_register_t;
#define assert(e)	((void)0)


#if ENABLE_RME
/* Size of cpu_context array */
#define CPU_DATA_CONTEXT_NUM		3
/* Offset of cpu_ops_ptr, size 8 bytes */
#define CPU_DATA_CPU_OPS_PTR		0x18
#else /* ENABLE_RME */
#define CPU_DATA_CONTEXT_NUM		2
#define CPU_DATA_CPU_OPS_PTR		0x10
#endif /* ENABLE_RME */

typedef enum {
	AFF_STATE_ON = 0,
	AFF_STATE_OFF = 1,
	AFF_STATE_ON_PENDING = 2
} aff_info_state_t;

typedef enum context_pas {
	CPU_CONTEXT_SECURE = 0,
	CPU_CONTEXT_NS,
#if ENABLE_RME
	CPU_CONTEXT_REALM,
#endif
	CPU_CONTEXT_NUM
} context_pas_t;


typedef uint8_t plat_local_state_t;

typedef struct psci_cpu_data {
	/* State as seen by PSCI Affinity Info API */
	aff_info_state_t aff_info_state;

	/*
	 * Highest power level which takes part in a power management
	 * operation.
	 */
	unsigned int target_pwrlvl;

	/* The local power state of this CPU */
	plat_local_state_t local_state;
} psci_cpu_data_t;

typedef struct cpu_data {
#ifdef __aarch64__
	void *cpu_context[CPU_DATA_CONTEXT_NUM];
#endif /* __aarch64__ */
	uintptr_t cpu_ops_ptr;
	struct psci_cpu_data psci_svc_cpu_data;
#if ENABLE_PAUTH
	uint64_t apiakey[2];
#endif
#if CRASH_REPORTING
	u_register_t crash_buf[CPU_DATA_CRASH_BUF_SIZE >> 3];
#endif
#if ENABLE_RUNTIME_INSTRUMENTATION
	uint64_t cpu_data_pmf_ts[CPU_DATA_PMF_TS_COUNT];
#endif
#if PLAT_PCPU_DATA_SIZE
	uint8_t platform_cpu_data[PLAT_PCPU_DATA_SIZE];
#endif
#if defined(IMAGE_BL31) && EL3_EXCEPTION_HANDLING
	pe_exc_data_t ehf_data;
#endif
}cpu_data_t;

#define PLATFORM_CLUSTER0_CORE_COUNT	(4)
#define PLATFORM_CORE_COUNT		(PLATFORM_CLUSTER0_CORE_COUNT)

cpu_data_t percpu_data[PLATFORM_CORE_COUNT];

static inline struct cpu_data *_cpu_data(void)
{
	return (cpu_data_t *)read_tpidr_el3();
}



/* Prototype for runtime service initializing function */
typedef int32_t (*rt_svc_init_t)(void);

/*
 * Prototype for runtime service SMC handler function. x0 (SMC Function ID) to
 * x4 are as passed by the caller. Rest of the arguments to SMC and the context
 * can be accessed using the handle pointer. The cookie parameter is reserved
 * for future use
 */
typedef uintptr_t (*rt_svc_handle_t)(uint32_t smc_fid,
				  u_register_t x1,
				  u_register_t x2,
				  u_register_t x3,
				  u_register_t x4,
				  void *cookie,
				  void *handle,
				  u_register_t flags);

typedef struct rt_svc_desc {
	uint8_t start_oen;
	uint8_t end_oen;
	uint8_t call_type;
	const char *name;
	rt_svc_init_t init;
	rt_svc_handle_t handle;
} rt_svc_desc_t;

typedef int gp_regs_t;
typedef int el3_state_t;
typedef int el1_sysregs_t;
typedef int cve_2018_3639_t;
typedef struct cpu_context {
	gp_regs_t gpregs_ctx;
	el3_state_t el3state_ctx;
	el1_sysregs_t el1_sysregs_ctx;
#if CTX_INCLUDE_EL2_REGS
	el2_sysregs_t el2_sysregs_ctx;
#endif
#if CTX_INCLUDE_FPREGS
	fp_regs_t fpregs_ctx;
#endif
	cve_2018_3639_t cve_2018_3639_ctx;
#if CTX_INCLUDE_PAUTH_REGS
	pauth_t pauth_ctx;
#endif
} cpu_context_t;

#define CTX_SCR_EL3		(0x0)

#define MAX_RT_SVCS		128

#define	EINVAL		22		/* Invalid argument */
#define	EALREADY	37		/* Operation already in progress */


#define OEN_TAP_END			(49)
#define OEN_TOS_START			(50)	/* Trusted OS */
#define OEN_TOS_END			(63)
#define OEN_LIMIT			(64)

#define SMC_TYPE_FAST			(1)
#define SMC_TYPE_YIELD			(0)

#define FUNCID_TYPE_SHIFT		(31)
#define FUNCID_TYPE_MASK		(0x1)
#define FUNCID_TYPE_WIDTH		(1)

#define FUNCID_OEN_SHIFT		(24)
#define FUNCID_OEN_MASK			(0x3f)
#define FUNCID_OEN_WIDTH		(6)

#define RT_SVC_DECS_NUM		((__RT_SVC_DESCS_END__ - __RT_SVC_DESCS_START__)\
					/ sizeof(rt_svc_desc_t))

#define DWORD_SHIFT		(3)
#define CTX_GPREGS_END		(0x100)
#define CTX_GPREG_ALL		(CTX_GPREGS_END >> DWORD_SHIFT)

//#define DEFINE_REG_STRUCT(name, num_regs)	\
//	typedef struct name {			\
//		uint64_t ctx_regs[num_regs];	\
//	}  __aligned(16) name##_t
//
//DEFINE_REG_STRUCT(gp_regs, CTX_GPREG_ALL);

void *cm_get_context(uint32_t security_state);
void runtime_svc_init(void);

void cm_write_scr_el3_bit(uint32_t security_state,
			  uint32_t bit_pos,
			  uint32_t value);

#endif /* INCLUDE_EL3_RUNTIME_H_ */
