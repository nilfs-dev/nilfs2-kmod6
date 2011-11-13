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


#include <linux/sched.h>	/* current_fsuid() and current_fsgid() */
#include <linux/fs.h>

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

/*
 * The following patches are left unapplied during backporting later
 * patches:
 *
 * commit 6a47dc1418682c83d603b491df1d048f73aa973e
 *   "nilfs: fix breakage caused by barrier flag changes"
 * commit 7ea8085910ef3dd4f3cad6845aaa2b580d39b115
 *   "drop unused dentry argument to ->fsync"
 * commit 7b6d91daee5cac6402186ff224c3af39d79f4a0e
 *   "block: unify flags for struct bio and struct request"
 * commit eafdc7d190a944c755a9fe68573c193e6e0217e7
 *   "sort out blockdev_direct_IO variants"
 * commit f4e420dc423148fba637af1ab618fa8896dfb2d6
 *   "clean up write_begin usage for directories in pagecache"
 * commit 6e1db88d536adcbbfe562b2d4b7d6425784fff12
 *   "introduce __block_write_begin"
 * commit 155130a4f7848b1aac439cab6bda1a175507c71c
 *   "get rid of block_write_begin_newtrunc"
 * commit 1025774ce411f2bd4b059ad7b53f0003569b74fa
 *   "remove inode_setattr"
 * commit a4ffdde6e56fdf8c34ddadc2674d6eb978083369
 *   "simplify checks for I_CLEAR/I_FREEING"
 * commit 6fd1e5c994c392ebdbe45600051b2a32ec4860f1
 *   "convert nilfs2 to ->evict_inode()"
 * commit 87e99511ea54510ffb60b98001d108794d5037f8
 *   "kill BH_Ordered flag"
 * commit 1cb0c924fa2d616e5e3b5bc62d97191aac9ff442
 *   "nilfs2: wait for discard to finish"
 * commit f8c131f5b6ffc899a70b30e541f367d47f89691c
 *   "nilfs2: replace barriers with explicit flush / FUA usage"
 * commit dd3932eddf428571762596e17b65f5dc92ca361b
 *   "block: remove BLKDEV_IFL_WAIT"
 */

#endif /* NILFS_KERN_FEATURE_H */
