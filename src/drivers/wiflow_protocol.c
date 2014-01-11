/********************************************************************/
/* Copyright (C) SSE-USTC, 2014                                     */
/*                                                                  */
/*  FILE NAME             :  wiflow_protocol.c                      */
/*  PRINCIPAL AUTHOR      :  Mengning                               */
/*  SUBSYSTEM NAME        :  driver_nl80211                         */
/*  MODULE NAME           :  WiFlow                                 */
/*  LANGUAGE              :  C                                      */
/*  TARGET ENVIRONMENT    :  ANY                                    */
/*  DATE OF FIRST RELEASE :  2014/01/08                             */
/*  DESCRIPTION           :  implement of WiFlow PDU parser         */
/********************************************************************/

/*
 * Revision log:
 *
 * Created by Mengning,2014/01/08 
 *
 */
#include<stdio.h> 			/* perror */
#include<stdlib.h>			/* exit	*/
#include<sys/types.h>		/* WNOHANG */
#include<sys/wait.h>		/* waitpid */
#include<string.h>			/* memset */

#include "common.h"
#include "driver.h"
#include "wiflow_protocol.h"

/*
struct wpa_init_params {
	void *global_priv; //NOT used,use local global_priv
	const u8 *bssid;   //ETH_ALEN length
	const char *ifname;//sizeof(bss->ifname) or char ifname[IFNAMSIZ + 1]; ex.wlan0
	const u8 *ssid;    //ssid_len
	size_t ssid_len;    
	const char *test_socket;//NOT used
	int use_pae_group_addr;//NOT used
	char **bridge; //ex. br0
	size_t num_bridge;

	u8 *own_addr; // ETH_ALENlength,buffer for writing own MAC address 
};
struct buf_params{
	char global_priv;
	u8 bssid[20];
	char ifname[20];
	u8 ssid[20];
	u32 ssid_len;
	char test_socket;
	int use_pae_group_addr;
	char bridge[20];
	u32 num_bridge;
	u8 own_addr[50];
};
*/
int wpa_init_params_parser(char * pdu, int pdu_size,struct wpa_init_params *params)
{
	struct buf_params  bufs;
	memcpy(&bufs,pdu,sizeof(struct buf_params));
	printf("ifname is %s\n",bufs.ifname);
	printf("Mac is "MACSTR"\n",MAC2STR(bufs.own_addr));
	printf("ssid is %s\n",bufs.ssid);
	printf("ssid_len is%u32",bufs.ssid_len);
	params->bridge=bufs.bridge;//未实现
	params->bssid=bufs.bssid;
	params->ifname=bufs.ifname;
	params->use_pae_group_addr=bufs.use_pae_group_addr;
	params->num_bridge=bufs.num_bridge;
	params->test_socket=bufs.test_socket;
	params->own_addr=bufs.own_addr;
	params->ssid=bufs.ssid;
	params->ssid_len=bufs.ssid_len;
	params->global_priv=bufs.global_priv;//未实现
    return 0;
}

int wpa_init_params_format(char * pdu, int pdu_size,struct wpa_init_params *params)
{
	struct buf_params  bufs;
	bufs.global_priv='W';
	bufs.ssid_len=params->ssid_len;
	bufs.test_socket=params->test_socket;
	bufs.use_pae_group_addr=params->use_pae_group_addr;
	strncpy(bufs.bridge,params->bridge,20);
	//strncpy(bufs.bssid,params->bssid,20);
	strncpy(bufs.ifname,params->ifname,20);
	strncpy(bufs.own_addr,params->own_addr,50);
	strncpy(bufs.ssid,params->ssid,20);
	memset(pdu,0,sizeof(pdu));
	memcpy(pdu,&bufs,sizeof(struct buf_params));
    return 0;   
}
/*
struct i802_bss {
	struct wpa_driver_nl80211_data *drv;//NOT used
	struct i802_bss *next;//multi-record flag
	int ifindex;
	char ifname[IFNAMSIZ + 1];
	char brname[IFNAMSIZ];
	unsigned int beacon_set:1;
	unsigned int added_if_into_bridge:1;
	unsigned int added_bridge:1;
	unsigned int in_deinit:1;

	u8 addr[ETH_ALEN];

	int freq;

	void *ctx;//NOT used
	struct nl_handle *nl_preq, *nl_mgmt;//NOT used
	struct nl_cb *nl_cb;//NOT used

	struct nl80211_wiphy_data *wiphy_data;//NOT used
	struct dl_list wiphy_list;//NOT used
};
*/
int i802_bss_parser(char * pdu, int pdu_size,struct i802_bss *bss)
{
    return 0;   
}

int i802_bss_format(char * pdu, int pdu_size,struct i802_bss *bss)
{
    return 0;   
}



