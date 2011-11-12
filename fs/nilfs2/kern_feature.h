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
/*
 * linux-2.6.35 and the later kernels have inode_init_owner().
 */
#ifndef HAVE_INODE_INIT_OWNER
# define HAVE_INODE_INIT_OWNER \
	(LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 34))
#endif
#endif /* LINUX_VERSION_CODE */


/*
 * definitions dependent to above macros
 */
#if !HAVE_INODE_INIT_OWNER
static inline void
inode_init_owner(struct inode *inode, const struct inode *dir, mode_t mode)
{
	inode->i_uid = current_fsuid();
	if (dir && dir->i_mode & S_ISGID) {
		inode->i_gid = dir->i_gid;
		if (S_ISDIR(mode))
			mode |= S_ISGID;
	} else
		inode->i_gid = current_fsgid();
	inode->i_mode = mode;
}
#endif


#endif /* NILFS_KERN_FEATURE_H */
