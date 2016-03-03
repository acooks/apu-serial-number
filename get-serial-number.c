#include <sys/ioctl.h>
#include <net/if.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

int main()
{
	struct ifreq ifr;

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (sock == -1) {
		fprintf(stderr, "couldn't create socket\n");
		assert(0);
	};

	strcpy(ifr.ifr_name, "enp0s25");
	if (ioctl(sock, SIOCGIFFLAGS, &ifr) != 0) {
		fprintf(stderr, "couldn't ioctl iface: %s\n",
		        ifr.ifr_name);
		assert(0);
	}

	if (ioctl(sock, SIOCGIFHWADDR, &ifr) == 0) {
		unsigned char mac_address[6];
		unsigned char oui[3];
		unsigned char sn[4] = {0};
		int si = 0;

		memcpy(mac_address, ifr.ifr_hwaddr.sa_data, 6);
		memcpy(oui, mac_address, 3);
		memcpy(sn, &mac_address[3], 3);

//		printf("sn: %02x:%02x:%02x:%02x\n", sn[0], sn[1], sn[2], sn[3]);

//		printf("%s, oui: %02x:%02x:%02x\n", ifr.ifr_name, oui[0], oui[1], oui[2]);

		si = sn[2] + 0xff * sn[1] + 0xffff * sn[0];
		si = si / 4 - 64;
		printf("%d\n", si);
	}
}