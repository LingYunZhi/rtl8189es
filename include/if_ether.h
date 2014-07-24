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

#ifndef _RTW_IF_ETHER_H
#define _RTW_IF_ETHER_H

#include <rtw_byteorder.h>
#include <linux/if_ether.h>

struct _vlan {
   u16       h_vlan_TCI;                // Encapsulates priority and VLAN ID
   u16       h_vlan_encapsulated_proto;
};

#define get_vlan_id(pvlan) ((ntohs((unsigned short )pvlan->h_vlan_TCI)) & 0xfff)
#define get_vlan_priority(pvlan) ((ntohs((unsigned short )pvlan->h_vlan_TCI))>>13)
#define get_vlan_encap_proto(pvlan) (ntohs((unsigned short )pvlan->h_vlan_encapsulated_proto))

#define MAC_FMT "%02x:%02x:%02x:%02x:%02x:%02x"
#define MAC_ARG(x) ((u8*)(x))[0],((u8*)(x))[1],((u8*)(x))[2],((u8*)(x))[3],((u8*)(x))[4],((u8*)(x))[5]
#define IP_FMT "%d.%d.%d.%d"
#define IP_ARG(x) ((u8*)(x))[0],((u8*)(x))[1],((u8*)(x))[2],((u8*)(x))[3]

extern const u8 zero_mac_addr[ETH_ALEN];
extern const u8 broadcast_mac_addr[ETH_ALEN];

static inline bool mac_addr_equal(const u8 *addr1, const u8 *addr2)
{
	return RTW_RN32(addr1) == RTW_RN32(addr2) && RTW_RN16(addr1 + 4) == RTW_RN16(addr2 + 4);
}

static inline bool is_multicast_mac_addr(const u8 *addr)
{
	return (addr[0] != 0xff) && (0x01 & addr[0]);
}

static inline bool is_broadcast_mac_addr(const u8 *addr)
{
	return RTW_RN32(addr) == 0xffffffff && RTW_RN16(addr + 4) == 0xffff;
}

static inline bool is_zero_mac_addr(const u8 *addr)
{
	return RTW_RN32(addr) == 0 && RTW_RN16(addr + 4) == 0;
}

static inline void copy_mac_addr(u8 *dest, const u8 *src)
{
	RTW_WN32(dest, RTW_RN32(src));
	RTW_WN16(dest + 4, RTW_RN16(src + 4));
}

static inline void set_broadcast_mac_addr(u8 *dest)
{
	RTW_WN32(dest, 0xffffffff);
	RTW_WN16(dest + 4, 0xffff);
}

static inline void set_zero_mac_addr(u8 *dest)
{
	RTW_WN32(dest, 0);
	RTW_WN16(dest + 4, 0);
}

#endif	/* _RTW_IF_ETHER_H */

