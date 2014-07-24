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
#ifndef __RTW_SECURITY_H_
#define __RTW_SECURITY_H_


#include <drv_conf.h>
#include <osdep_service.h>
#include <drv_types.h>


#define _NO_PRIVACY_		0x0
#define _WEP40_				0x1
#define _TKIP_				0x2
#define _TKIP_WTMIC_		0x3
#define _AES_				0x4
#define _WEP104_			0x5
#define _WEP_WPA_MIXED_	0x07  // WEP + WPA
#define _SMS4_				0x06
#ifdef CONFIG_IEEE80211W
#define _BIP_				0x8
#endif //CONFIG_IEEE80211W
#define is_wep_enc(alg) (((alg) == _WEP40_) || ((alg) == _WEP104_))

#define _WPA_IE_ID_	0xdd
#define _WPA2_IE_ID_	0x30

#define SHA256_MAC_LEN 32
#define AES_BLOCK_SIZE 16
#define AES_PRIV_SIZE (4 * 44)

typedef enum {
	ENCRYP_PROTOCOL_OPENSYS,   //open system
	ENCRYP_PROTOCOL_WEP,       //WEP
	ENCRYP_PROTOCOL_WPA,       //WPA
	ENCRYP_PROTOCOL_WPA2,      //WPA2
	ENCRYP_PROTOCOL_WAPI,      //WAPI: Not support in this version
	ENCRYP_PROTOCOL_MAX
}ENCRYP_PROTOCOL_E;


#ifndef Ndis802_11AuthModeWPA2
#define Ndis802_11AuthModeWPA2 (Ndis802_11AuthModeWPANone + 1)
#endif

#ifndef Ndis802_11AuthModeWPA2PSK
#define Ndis802_11AuthModeWPA2PSK (Ndis802_11AuthModeWPANone + 2)
#endif

union pn48	{

	u64	val;

#ifdef CONFIG_LITTLE_ENDIAN

struct {
  u8 TSC0;
  u8 TSC1;
  u8 TSC2;
  u8 TSC3;
  u8 TSC4;
  u8 TSC5;
  u8 TSC6;
  u8 TSC7;
} _byte_;

#elif defined(CONFIG_BIG_ENDIAN)

struct {
  u8 TSC7;
  u8 TSC6;
  u8 TSC5;
  u8 TSC4;
  u8 TSC3;
  u8 TSC2;
  u8 TSC1;
  u8 TSC0;
} _byte_;

#endif

};

union Keytype {
        u8   skey[16];
        u32    lkey[4];
};


typedef struct _RT_PMKID_LIST
{
	u8						bUsed;
	u8 						Bssid[6];
	u8						PMKID[16];
	u8						SsidBuf[33];
	u8*						ssid_octet;
	u16 						ssid_length;
} RT_PMKID_LIST, *PRT_PMKID_LIST;


struct security_priv
{
	u32	  dot11AuthAlgrthm;		// 802.11 auth, could be open, shared, 8021x and authswitch
	u32	  dot11PrivacyAlgrthm;	// This specify the privacy for shared auth. algorithm.

	/* WEP */
	u32	  dot11PrivacyKeyIndex;	// this is only valid for legendary wep, 0~3 for key id. (tx key index)
	union Keytype dot11DefKey[4];			// this is only valid for def. key
	u32 	dot11DefKeylen[4];
	u8 	key_mask; /* use to restore wep key after hal_init */

	u32 dot118021XGrpPrivacy;	// This specify the privacy algthm. used for Grp key
	u32	dot118021XGrpKeyid;		// key id used for Grp Key ( tx key index)
	union Keytype	dot118021XGrpKey[4];	// 802.1x Group Key, for inx0 and inx1
	union Keytype	dot118021XGrptxmickey[4];
	union Keytype	dot118021XGrprxmickey[4];
	union pn48		dot11Grptxpn;			// PN48 used for Grp Key xmit.
	union pn48		dot11Grprxpn;			// PN48 used for Grp Key recv.
#ifdef CONFIG_IEEE80211W
	u32	dot11wBIPKeyid;						// key id used for BIP Key ( tx key index)
	union Keytype	dot11wBIPKey[6];		// BIP Key, for index4 and index5
	union pn48		dot11wBIPtxpn;			// PN48 used for Grp Key xmit.
	union pn48		dot11wBIPrxpn;			// PN48 used for Grp Key recv.
#endif //CONFIG_IEEE80211W
#ifdef CONFIG_AP_MODE
	//extend security capabilities for AP_MODE
	unsigned int dot8021xalg;//0:disable, 1:psk, 2:802.1x
	unsigned int wpa_psk;//0:disable, bit(0): WPA, bit(1):WPA2
	unsigned int wpa_group_cipher;
	unsigned int wpa2_group_cipher;
	unsigned int wpa_pairwise_cipher;
	unsigned int wpa2_pairwise_cipher;
#endif

	u8 wps_ie[MAX_WPS_IE_LEN];//added in assoc req
	int wps_ie_len;


	u8	binstallGrpkey;
#ifdef CONFIG_IEEE80211W
	u8	binstallBIPkey;
#endif //CONFIG_IEEE80211W
	u8	busetkipkey;
	//_timer tkip_timer;
	u8	bcheck_grpkey;
	u8	bgrpkey_handshake;

	//u8	packet_cnt;//unused, removed

	s32	sw_encrypt;//from registry_priv
	s32	sw_decrypt;//from registry_priv

	s32 	hw_decrypted;//if the rx packets is hw_decrypted==_FALSE, it means the hw has not been ready.


	//keeps the auth_type & enc_status from upper layer ioctl(wpa_supplicant or wzc)
	u32 ndisauthtype;	// NDIS_802_11_AUTHENTICATION_MODE
	u32 ndisencryptstatus;	// NDIS_802_11_ENCRYPTION_STATUS

	WLAN_BSSID_EX sec_bss;  //for joinbss (h2c buffer) usage

	NDIS_802_11_WEP ndiswep;

	u8 assoc_info[600];
	u8 szofcapability[256]; //for wpa2 usage
	u8 oidassociation[512]; //for wpa/wpa2 usage
	u8 authenticator_ie[256];  //store ap security information element
	u8 supplicant_ie[256];  //store sta security information element


	//for tkip countermeasure
	u32 last_mic_err_time;
	u8	btkip_countermeasure;
	u8	btkip_wait_report;
	u32 btkip_countermeasure_time;

	//---------------------------------------------------------------------------
	// For WPA2 Pre-Authentication.
	//---------------------------------------------------------------------------
	//u8				RegEnablePreAuth;				// Default value: Pre-Authentication enabled or not, from registry "EnablePreAuth". Added by Annie, 2005-11-01.
	//u8				EnablePreAuthentication;			// Current Value: Pre-Authentication enabled or not.
	RT_PMKID_LIST		PMKIDList[NUM_PMKID_CACHE];	// Renamed from PreAuthKey[NUM_PRE_AUTH_KEY]. Annie, 2006-10-13.
	u8				PMKIDIndex;
	//u32				PMKIDCount;						// Added by Annie, 2006-10-13.
	//u8				szCapability[256];				// For WPA2-PSK using zero-config, by Annie, 2005-09-20.

	u8 bWepDefaultKeyIdxSet;
};

struct sha256_state {
	u64 length;
	u32 state[8], curlen;
	u8 buf[64];
};

#define GET_ENCRY_ALGO(psecuritypriv, psta, encry_algo, bmcst)\
do{\
	switch(psecuritypriv->dot11AuthAlgrthm)\
	{\
		case dot11AuthAlgrthm_Open:\
		case dot11AuthAlgrthm_Shared:\
		case dot11AuthAlgrthm_Auto:\
			encry_algo = (u8)psecuritypriv->dot11PrivacyAlgrthm;\
			break;\
		case dot11AuthAlgrthm_8021X:\
			if(bmcst)\
				encry_algo = (u8)psecuritypriv->dot118021XGrpPrivacy;\
			else\
				encry_algo =(u8) psta->dot118021XPrivacy;\
			break;\
	     case dot11AuthAlgrthm_WAPI:\
		     encry_algo = (u8)psecuritypriv->dot11PrivacyAlgrthm;\
		     break;\
	}\
}while(0)


#define SET_ICE_IV_LEN( iv_len, icv_len, encrypt)\
do{\
	switch(encrypt)\
	{\
		case _WEP40_:\
		case _WEP104_:\
			iv_len = 4;\
			icv_len = 4;\
			break;\
		case _TKIP_:\
			iv_len = 8;\
			icv_len = 4;\
			break;\
		case _AES_:\
			iv_len = 8;\
			icv_len = 8;\
			break;\
		case _SMS4_:\
			iv_len = 18;\
			icv_len = 16;\
			break;\
		default:\
			iv_len = 0;\
			icv_len = 0;\
			break;\
	}\
}while(0)


#define GET_TKIP_PN(iv,dot11txpn)\
do{\
	dot11txpn._byte_.TSC0=iv[2];\
	dot11txpn._byte_.TSC1=iv[0];\
	dot11txpn._byte_.TSC2=iv[4];\
	dot11txpn._byte_.TSC3=iv[5];\
	dot11txpn._byte_.TSC4=iv[6];\
	dot11txpn._byte_.TSC5=iv[7];\
}while(0)

#define ROL32( A, n )	( ((u32)(A) << (n)) | ((u32)(A)>>(32-(n))) )
#define ROR32( A, n ) 	ROL32( (A), 32 - (n) )

struct mic_data
{
	u32  K0, K1;         // Key
	u32  L, R;           // Current state
	u32  M;              // Message accumulator (single word)
	u32     nBytesInM;      // # bytes in M
};

extern const u32 Te0[256];
extern const u32 Te1[256];
extern const u32 Te2[256];
extern const u32 Te3[256];
extern const u32 Te4[256];
extern const u32 Td0[256];
extern const u32 Td1[256];
extern const u32 Td2[256];
extern const u32 Td3[256];
extern const u32 Td4[256];
extern const u32 rcon[10];
extern const u8 Td4s[256];
extern const u8 rcons[10];

#define RCON(i) (rcons[(i)] << 24)

static inline u32 rotr(u32 val, int bits)
{
	return (val >> bits) | (val << (32 - bits));
}

#define TE0(i) Te0[((i) >> 24) & 0xff]
#define TE1(i) rotr(Te0[((i) >> 16) & 0xff], 8)
#define TE2(i) rotr(Te0[((i) >> 8) & 0xff], 16)
#define TE3(i) rotr(Te0[(i) & 0xff], 24)
#define TE41(i) ((Te0[((i) >> 24) & 0xff] << 8) & 0xff000000)
#define TE42(i) (Te0[((i) >> 16) & 0xff] & 0x00ff0000)
#define TE43(i) (Te0[((i) >> 8) & 0xff] & 0x0000ff00)
#define TE44(i) ((Te0[(i) & 0xff] >> 8) & 0x000000ff)
#define TE421(i) ((Te0[((i) >> 16) & 0xff] << 8) & 0xff000000)
#define TE432(i) (Te0[((i) >> 8) & 0xff] & 0x00ff0000)
#define TE443(i) (Te0[(i) & 0xff] & 0x0000ff00)
#define TE414(i) ((Te0[((i) >> 24) & 0xff] >> 8) & 0x000000ff)
#define TE4(i) ((Te0[(i)] >> 8) & 0x000000ff)

#define TD0(i) Td0[((i) >> 24) & 0xff]
#define TD1(i) rotr(Td0[((i) >> 16) & 0xff], 8)
#define TD2(i) rotr(Td0[((i) >> 8) & 0xff], 16)
#define TD3(i) rotr(Td0[(i) & 0xff], 24)
#define TD41(i) (Td4s[((i) >> 24) & 0xff] << 24)
#define TD42(i) (Td4s[((i) >> 16) & 0xff] << 16)
#define TD43(i) (Td4s[((i) >> 8) & 0xff] << 8)
#define TD44(i) (Td4s[(i) & 0xff])
#define TD0_(i) Td0[(i) & 0xff]
#define TD1_(i) rotr(Td0[(i) & 0xff], 8)
#define TD2_(i) rotr(Td0[(i) & 0xff], 16)
#define TD3_(i) rotr(Td0[(i) & 0xff], 24)

/* ===== start - public domain SHA256 implementation ===== */

/* This is based on SHA256 implementation in LibTomCrypt that was released into
 * public domain by Tom St Denis. */

/* the K array */
extern const u32 K[64];

/* Various logical functions */
#define RORc(x, y)		ROR32((x), (y) & 31)
#define Ch(x,y,z)       (z ^ (x & (y ^ z)))
#define Maj(x,y,z)      (((x | y) & z) | (x & y))
#define S(x, n)         RORc((x), (n))
#define R(x, n)         ((u32)(x) >> (n))
#define Sigma0(x)       (S(x, 2) ^ S(x, 13) ^ S(x, 22))
#define Sigma1(x)       (S(x, 6) ^ S(x, 11) ^ S(x, 25))
#define Gamma0(x)       (S(x, 7) ^ S(x, 18) ^ R(x, 3))
#define Gamma1(x)       (S(x, 17) ^ S(x, 19) ^ R(x, 10))
#ifndef MIN
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#endif

#ifdef CONFIG_IEEE80211W
int omac1_aes_128(u8 *key, u8 *data, size_t data_len, u8 *mac);
#endif //CONFIG_IEEE80211W
void rtw_secmicsetkey(struct mic_data *pmicdata, u8 * key );
void rtw_secmicappendbyte(struct mic_data *pmicdata, u8 b );
void rtw_secmicappend(struct mic_data *pmicdata, u8 * src, u32 nBytes );
void rtw_secgetmic(struct mic_data *pmicdata, u8 * dst );

void rtw_seccalctkipmic(
	u8 * key,
	u8 *header,
	u8 *data,
	u32 data_len,
	u8 *Miccode,
	u8   priority);

u32 rtw_aes_encrypt(_adapter *padapter, u8 *pxmitframe);
u32 rtw_tkip_encrypt(_adapter *padapter, u8 *pxmitframe);
void rtw_wep_encrypt(_adapter *padapter, u8  *pxmitframe);

u32 rtw_aes_decrypt(_adapter *padapter, u8  *precvframe);
u32 rtw_tkip_decrypt(_adapter *padapter, u8  *precvframe);
void rtw_wep_decrypt(_adapter *padapter, u8  *precvframe);
#ifdef CONFIG_IEEE80211W
u32	rtw_BIP_verify(_adapter *padapter, u8 *precvframe);
#endif //CONFIG_IEEE80211W
#ifdef CONFIG_TDLS
void wpa_tdls_generate_tpk(_adapter *padapter, struct sta_info *psta);
int wpa_tdls_ftie_mic(u8 *kck, u8 trans_seq,
						u8 *lnkid, u8 *rsnie, u8 *timeoutie, u8 *ftie,
						u8 *mic);
int tdls_verify_mic(u8 *kck, u8 trans_seq,
						u8 *lnkid, u8 *rsnie, u8 *timeoutie, u8 *ftie);
#endif //CONFIG_TDLS

void rtw_use_tkipkey_handler(void* FunctionContext);

void rtw_sec_restore_wep_key(_adapter *adapter);
u8 rtw_handle_tkip_countermeasure(_adapter* adapter, const char *caller);

#endif	//__RTL871X_SECURITY_H_

