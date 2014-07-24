/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef _RTL871X_BYTEORDER_H_
#define _RTL871X_BYTEORDER_H_

#include <drv_conf.h>
#include <asm/byteorder.h>
#include <asm/unaligned.h>
#include <linux/swab.h>

#define RTW_RL16(p)	get_unaligned_le16(p)
#define RTW_RL24(p)	((u32)(((u8*)(p))[0]) | (u32)(((u8*)(p))[1]) << 8 | (u32)(((u8*)(p))[2]) << 16)
#define RTW_RL32(p)	get_unaligned_le32(p)
#define RTW_RL64(p)	get_unaligned_le64(p)

#define RTW_RB16(p)	get_unaligned_be16(p)
#define RTW_RB24(p)	((u32)(((u8*)(p))[0]) << 16 | (u32)(((u8*)(p))[1]) << 8 | (u32)(((u8*)(p))[2]))
#define RTW_RB32(p)	get_unaligned_be32(p)
#define RTW_RB64(p)	get_unaligned_be64(p)

#define RTW_WL16(p, v)	put_unaligned_le16((v), (p))
#define RTW_WL24(p, v)	do { u8* __p = (p); __p[0] = (v) & 0xff; __p[1] = ((v) >> 8) & 0xff; __p[2] = ((v) >> 16) & 0xff; } while (0)
#define RTW_WL32(p, v)	put_unaligned_le32((v), (p))
#define RTW_WL64(p, v)	put_unaligned_le64((v), (p))

#define RTW_WB16(p, v)	put_unaligned_be16((v), (p))
#define RTW_WB24(p, v)	do { u8* __p = (p); __p[0] = ((v) >> 16) & 0xff; __p[1] = ((v) >> 8) & 0xff; __p[2] = (v) & 0xff; } while (0)
#define RTW_WB32(p, v)	put_unaligned_be32((v), (p))
#define RTW_WB64(p, v)	put_unaligned_be64((v), (p))

#define PACK_LE16(a, b)			((u16)(a) | (u16)(b) << 8)
#define PACK_LE24(a, b, c)		((u32)(a) | (u32)(b) << 8 | (u32)(c) << 16)
#define PACK_LE32(a, b, c, d)	((u32)(a) | (u32)(b) << 8 | (u32)(c) << 16 | (u32)(d) << 24)
#define PACK_LE64(a, b, c, d, e, f, g, h) \
	((u64)(a) | (u64)(b) << 8 | (u64)(c) << 16 | (u64)(d) << 24 | \
	 (u64)(e) << 32 | (u64)(f) << 40 | (u64)(g) << 48 | (u64)(h) << 56)

#define PACK_BE16(a, b)			((u16)(a) << 8 | (u16)(b))
#define PACK_BE24(a, b, c)		((u32)(a) << 16 | (u32)(b) << 8 | (u32)(c))
#define PACK_BE32(a, b, c, d)	((u32)(a) << 24 | (u32)(b) << 16 | (u32)(c) << 8 | (u32)(d))
#define PACK_BE64(a, b, c, d, e, f, g, h) \
	((u64)(a) << 56 | (u64)(b) << 48 | (u64)(c) << 40 | (u64)(d) << 32 | \
	 (u64)(e) << 24 | (u64)(f) << 16 | (u64)(g) << 8 | (u64)(h))

# define RTW_RN16A(p) (*(u16*)(p))
# define RTW_RN32A(p) (*(u32*)(p))
# define RTW_RN64A(p) (*(u64*)(p))

# define RTW_WN16A(p, v) (*(u16*)(p) = (u16)(v))
# define RTW_WN32A(p, v) (*(u32*)(p) = (u32)(v))
# define RTW_WN64A(p, v) (*(u64*)(p) = (u64)(v))

#if defined (CONFIG_BIG_ENDIAN)

# define RTW_RN16 RTW_RB16
# define RTW_RN24 RTW_RB24
# define RTW_RN32 RTW_RB32
# define RTW_RN64 RTW_RB64

# define RTW_WN16 RTW_WB16
# define RTW_WN24 RTW_WB24
# define RTW_WN32 RTW_WB32
# define RTW_WN64 RTW_WB64

# define RTW_RB16A RTW_RN16A
# define RTW_RB32A RTW_RN32A
# define RTW_RB64A RTW_RN64A

# define RTW_WB16A RTW_WN16A
# define RTW_WB32A RTW_WN32A
# define RTW_WB64A RTW_WN64A

# define RTW_RL16A(p) swab16(*(u16*)(p))
# define RTW_RL32A(p) swab32(*(u32*)(p))
# define RTW_RL64A(p) swab64(*(u64*)(p))

# define RTW_WL16A(p, v) (*(u16*)(p) = swab16((u16)(v)))
# define RTW_WL32A(p, v) (*(u32*)(p) = swab32((u32)(v)))
# define RTW_WL64A(p, v) (*(u64*)(p) = swab64((u64)(v)))

# define PACK_NE16 PACK_BE16
# define PACK_NE24 PACK_BE24
# define PACK_NE32 PACK_BE32
# define PACK_NE64 PACK_BE64

#else

# define RTW_RN16 RTW_RL16
# define RTW_RN24 RTW_RL24
# define RTW_RN32 RTW_RL32
# define RTW_RN64 RTW_RL64

# define RTW_WN16 RTW_WL16
# define RTW_WN24 RTW_WL24
# define RTW_WN32 RTW_WL32
# define RTW_WN64 RTW_WL64

# define RTW_RB16A(p) swab16(*(u16*)(p))
# define RTW_RB32A(p) swab32(*(u32*)(p))
# define RTW_RB64A(p) swab64(*(u64*)(p))

# define RTW_WB16A(p, v) (*(u16*)(p) = swab16((u16)(v)))
# define RTW_WB32A(p, v) (*(u32*)(p) = swab32((u32)(v)))
# define RTW_WB64A(p, v) (*(u64*)(p) = swab64((u64)(v)))

# define RTW_RL16A RTW_RN16A
# define RTW_RL32A RTW_RN32A
# define RTW_RL64A RTW_RN64A

# define RTW_WL16A RTW_WN16A
# define RTW_WL32A RTW_WN32A
# define RTW_WL64A RTW_WN64A

# define PACK_NE16 PACK_LE16
# define PACK_NE24 PACK_LE24
# define PACK_NE32 PACK_LE32
# define PACK_NE64 PACK_LE64

#endif

#if BITS_PER_LONG == 32
# define RTW_RNLONG RTW_RN32
# define RTW_WNLONG RTW_WN32
# define PACK_NELONG PACK_NE32
#else
# define RTW_RNLONG RTW_RN64
# define RTW_WNLONG RTW_WN64
# define PACK_NELONG PACK_NE64
#endif

#endif /* _RTL871X_BYTEORDER_H_ */
