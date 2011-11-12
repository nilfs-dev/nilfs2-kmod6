/*
 * kern_feature.h - Kernel dependent features
 *
 * Licensed under GPLv2: the complete text of the GNU General Public
 * License can be found in COPYING file of the nilfs-kmod package.
 *
 * Copyright (C) 2006-2011 Nippon Telegraph and Telephone Corporation.
 */

#ifndef NILFS_KERN_FEATURE_H
#define NILFS_KERN_FEATURE_H

#include <linux/version.h>

/*
 * Please define as 0/1 here if you want to override
 */

/*
 * for Red Hat Enterprise Linux / CentOS 5.x
 */
#if defined(RHEL_MAJOR) && (RHEL_MAJOR == 6)
#endif

/*
 * defaults dependent to kernel versions
 */
#ifdef LINUX_VERSION_CODE
#endif /* LINUX_VERSION_CODE */


#endif /* NILFS_KERN_FEATURE_H */
