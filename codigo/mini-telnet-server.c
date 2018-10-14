#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "config.h"

int
main(int argc, char **argv)
{
	char buf[MSGLEN + 1];
	struct sockaddr_in local, remote;
	int s, new_s;

	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket");
		exit(1);
	}

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = INADDR_ANY;
	local.sin_port = htons(PORT);

	if (bind(s, (struct sockaddr *)&local, sizeof(local)) == -1) {
		perror("bind");
		exit(1);
	}

	//TODO: Completar conexión del socket para TCP
	if (listen(s, 10) == -1) {
		perror("listen");
		exit(1);
	}

	if (new_s = (accept(s, (struct sockaddr *)&local, sizeof(local)))<0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	for (;;) {
		memset(&buf, 0, MSGLEN+1);

		//TODO: Recibir mensaje en buf



		//Imprimir comando
		printf("comando: %s", buf);

		if (strncmp(buf, ENDMSG, sizeof(ENDMSG)) == 0)
			break;
		//Ejectuar comando
		if(system(buf) == -1){
			perror("error ejecución comando");
			break;
		}
	}

	close(s);
	return 0;
}
