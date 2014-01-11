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

int wpa_init_params_parser(char * pdu, int pdu_size,struct wpa_init_params *params)
{
	struct buf_params  bufs;
	memcpy(&bufs,pdu,sizeof(struct buf_params));
	printf("ifname is %s\n",bufs.ifname);
	printf("Mac is "MACSTR"\n",MAC2STR(bufs.own_addr));
	printf("ssid is %s\n",bufs.ssid);
	printf("ssid_len is%u32\n",bufs.ssid_len);
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

int i802_bss_parser(char * pdu, int pdu_size,struct i802_bss *bss)
{
    return 0;   
}

int i802_bss_format(char * pdu, int pdu_size,struct i802_bss *bss)
{
    return 0;   
}



