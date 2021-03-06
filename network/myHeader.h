#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <winsock2.h>

#define MACLEN 6

typedef struct ethernet_header
{
	u_char dst_MAC[MACLEN];
	u_char src_MAC[MACLEN];
	u_short ether_Type;
}ethernet_header, *Pethernet_header;

/* 4 bytes IP address */
typedef struct ip_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

typedef struct arp_header
{
	u_short Hardware_type;
	u_short Protocol_type;
	u_char Hardware_size;
	u_char Protocol_size;
	u_short Opcode;	// 1 : request, 2 : reply
	u_char src_MAC[MACLEN];
	u_char src_IP[4];
	u_char dst_MAC[MACLEN];
	u_char dst_IP[4];
}arp_header, *Parp_header;


/* IPv4 header */
typedef struct ip_header {
	u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
	u_char  tos;            // Type of service 
	u_short tlen;           // Total length 
	u_short identification; // Identification
	u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
	u_char  ttl;            // Time to live
	u_char  proto;          // Protocol
	u_short crc;            // Header checksum
	ip_address  src_addr;      // Source address
	ip_address  dst_addr;      // Destination address
	u_int   op_pad;         // Option + Padding
}ip_header, *Pip_header;

typedef struct tcp_header
{
	u_short src_port; // Source port
	u_short dst_port; // Destination port
}tcp_header, *Ptcp_header;

typedef struct DeviceInfo
{
	IN_ADDR ipAddress;
	IN_ADDR gateWayAddress;
	u_char macAddress[MACLEN];
}DeviceInfo, *PDeviceInfo;


/* ChoiceDev.c */
pcap_if_t * ChoiceDev(pcap_if_t * alldevs);
int ethernetHeader(const u_char *packet);
int ipHeader(const u_char *packet);
int tcpHeader(const u_char *packet);
int getGateWayAddress(pcap_if_t * choiceDev, PDeviceInfo myDeviceInfo);
char *iptos(u_long in);
int getVictimMAC(pcap_t *handle, PDeviceInfo myDeviceInfo, PDeviceInfo victimDeviceInfo);