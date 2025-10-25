// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * CPUIDLE driver for Exynos 64bits
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/cpuidle.h>
#include <linux/cpu_pm.h>
#include <linux/cpu.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/errno.h>
#include <linux/psci.h>
#include <linux/slab.h>
#include <linux/reboot.h>

#include <asm/cpuidle.h>
#include <asm/topology.h>

#include "dt_idle_states.h"

static int exynos_enter_idle(struct cpuidle_device *dev,
			     struct cpuidle_driver *drv, int index)
{
        if (index == 0) {
                cpu_do_idle();
                return index;
        }

        return index;
}

static int exynos_cpuidle_reboot_notifier(struct notifier_block *nb,
					  unsigned long event, void *data)
{
	switch (event) {
	case SYS_RESTART:
	case SYSTEM_POWER_OFF:
		cpuidle_pause();
		break;
	default:
		break;
	}
	return NOTIFY_OK;
}

static struct notifier_block exynos_cpuidle_reboot_nb = {
	.notifier_call = exynos_cpuidle_reboot_notifier,
};

#define exynos_idle_state_wfi(state)				\
	do {							\
		state.enter = exynos_enter_idle;		\
		state.exit_latency = 1;				\
		state.target_residency = 1;			\
		state.power_usage = UINT_MAX;			\
		strscpy(state.name, "WFI", CPUIDLE_NAME_LEN);	\
		strscpy(state.desc, "c1", CPUIDLE_DESC_LEN);	\
	} while (0)

static struct cpuidle_driver exynos_cpuidle_drivers[NR_CPUS];

static const struct of_device_id exynos_idle_state_of_match[] __initconst = {
	{ .compatible = "samsung,exynos-idle-state",
	  .data = exynos_enter_idle },
	{ },
};

static int __init exynos_idle_driver_init(struct cpuidle_driver *drv,
					  struct cpumask *cpumask)
{
	int cpu = cpumask_first(cpumask);

	drv->name = kzalloc(sizeof("exynos_idleX"), GFP_KERNEL);
	if (!drv->name)
		return -ENOMEM;

	scnprintf((char *)drv->name, sizeof(drv->name), "exynos_idle%d", cpu);
	drv->owner = THIS_MODULE;
	drv->cpumask = cpumask;
	exynos_idle_state_wfi(drv->states[0]);

	return 0;
}

static int __init exynos_cpuidle_percpu_init(unsigned int cpu)
{
	struct cpumask *mask = topology_sibling_cpumask(cpu);
	int ret;

	ret = exynos_idle_driver_init(&exynos_cpuidle_drivers[cpu], mask);

	if (ret)
		return ret;

	/*
	 * Initialize idle states data, starting at index 1.
	 * This driver is DT only, if no DT idle states are detected
	 * (ret == 0) let the driver initialization fail accordingly
	 * since there is no reason to initialize the idle driver
	 * if only wfi is supported.
	 */
	ret = dt_init_idle_driver(&exynos_cpuidle_drivers[cpu],
				  exynos_idle_state_of_match, 1);
	if (ret < 0)
		return ret ? : -ENODEV;

	ret = cpuidle_register(&exynos_cpuidle_drivers[cpu], NULL);
	if (ret)
		return ret;

	return 0;
}

static int __init exynos_cpuidle_init(void)
{
	int cpu, ret;

	for_each_possible_cpu(cpu) {
		ret = exynos_cpuidle_percpu_init(cpu);
		if (ret) {
			pr_err("CPU %d failed initialize cpuidle driver\n", cpu);
			goto out_fail;
		}
	}

	register_reboot_notifier(&exynos_cpuidle_reboot_nb);

	return 0;

out_fail:
	while (--cpu >= 0) {
		cpuidle_unregister(&exynos_cpuidle_drivers[cpu]);
		kfree(exynos_cpuidle_drivers[cpu].name);
	}

	return ret;
}

device_initcall(exynos_cpuidle_init);
