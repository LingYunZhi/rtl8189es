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
#ifndef __SDIO_OPS_H__
#define __SDIO_OPS_H__

#include <drv_conf.h>
#include <osdep_service.h>
#include <drv_types.h>
#include <osdep_intf.h>
#include <sdio_ops_linux.h>

extern void sdio_set_intf_ops(struct _io_ops *pops);

//extern void sdio_func1cmd52_read(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *rmem);
//extern void sdio_func1cmd52_write(struct intf_hdl *pintfhdl, u32 addr, u32 cnt, u8 *wmem);
extern u8 SdioLocalCmd52Read1Byte(PADAPTER padapter, u32 addr);
extern void SdioLocalCmd52Write1Byte(PADAPTER padapter, u32 addr, u8 v);
extern s32 _sdio_local_read(PADAPTER padapter, u32 addr, u32 cnt, u8 *pbuf);
extern s32 sdio_local_read(PADAPTER padapter, u32 addr, u32 cnt, u8 *pbuf);
extern s32 _sdio_local_write(PADAPTER padapter, u32 addr, u32 cnt, u8 *pbuf);
extern s32 sdio_local_write(PADAPTER padapter, u32 addr, u32 cnt, u8 *pbuf);

u32 _sdio_read32(PADAPTER padapter, u32 addr);
s32 _sdio_write32(PADAPTER padapter, u32 addr, u32 val);

extern void InitInterrupt8723ASdio(PADAPTER padapter);
extern void InitSysInterrupt8723ASdio(PADAPTER padapter);
extern void EnableInterrupt8723ASdio(PADAPTER padapter);
extern void DisableInterrupt8723ASdio(PADAPTER padapter);
extern void sd_int_hdl(PADAPTER padapter);
#ifdef CONFIG_RTL8723A
extern u8 HalQueryTxBufferStatus8723ASdio(PADAPTER padapter);
#endif //CONFIG_RTL8723A
#ifdef CONFIG_RTL8188E
extern u8 HalQueryTxBufferStatus8189ESdio(PADAPTER padapter);
#endif //CONFIG_RTL8188E
extern void InitInterrupt8188ESdio(PADAPTER padapter);
extern void EnableInterrupt8188ESdio(PADAPTER padapter);
extern void DisableInterrupt8188ESdio(PADAPTER padapter);
extern void UpdateInterruptMask8188ESdio(PADAPTER padapter, u32 AddMSR, u32 RemoveMSR);

#ifdef CONFIG_WOWLAN
extern u8 RecvOnePkt(PADAPTER padapter, u32 size);
extern void ClearInterrupt8189ESdio(PADAPTER padapter);
#endif //CONFIG_WOWLAN
#endif

