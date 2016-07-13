#include "includes.h"

#define tmb 1024
#define porta 8002

static void Delay(unsigned int count);

int main(char *argc, char *argv[]){

    char ip[16], message_server[2000];
	// Receber o IP do servidor como argumento
	strcpy(ip, argv[1]);
    int skt, valor, ldrValue;
    struct sockaddr_in serv;

	// Abrindo os arquivos que seram usados para ler o sensor e acender o led
	FILE *ain,*aval,*gpio, *dir, *high;

	ain = fopen("/sys/devices/bone_capemgr.9/slots", "w");

	gpio = fopen("/sys/class/gpio/export", "w");
	fprintf(gpio, "60");
	fclose(gpio);

	dir  = fopen("/sys/class/gpio/gpio60/direction", "w");
	fprintf(dir, "out");
	fclose(dir);

	fseek(ain,0,SEEK_SET);
	fprintf(ain,"cape-bone-iio");
	fflush(ain);
	
	// Inicio do socket 
    skt = socket(AF_INET, SOCK_STREAM, 0);
    
    serv.sin_family = AF_INET; 
    serv.sin_addr.s_addr = inet_addr(ip); 
    serv.sin_port = htons (porta); 
	
    memset (&(serv.sin_zero), 0x00, sizeof (serv.sin_zero));
    connect (skt, (struct sockaddr *)&serv, sizeof (struct sockaddr));

	/* Pegando o endereço IP da prípria maquina e escrevendo para que o servidor 
	 * saiba o IP, escrito duas vezes para que a função da thread seja capaz de 
	 * ter essa informação tambem */

	strcpy(ip,getIP());
	write(skt, ip, 11);

	write(skt, ip, 11);

	read(skt , message_server, 2000);
	printf("%s", message_server);

	memset(message_server, 0, 2000);

	while(1){

		// Lendo o valor do sensor e jogando no ldrValue

		high = fopen("/sys/class/gpio/gpio60/value", "w");
		aval = fopen("/sys/devices/ocp.3/helper.15/AIN0", "r");
		fseek(aval,0,SEEK_SET);
		fscanf(aval,"%d",&ldrValue);
		fclose(aval);
	
		// Enviando para o servidor o valor lido
		Delay(10000000);
		write(skt, &ldrValue, 4);
		Delay(10000000);
	
		// Retornado o que a BBB deve fazer, se é acender o LED ou apagar
		read(skt, &valor, 4);

		if(valor){
			fprintf(high, "1");
			fclose(high);
		}else{
			fprintf(high, "0");
			fclose(high);
		}	

	}
	
	return 0;
    
}

// Função para que ocorra o dalay
static void Delay(unsigned int count){
    while(count--);
      asm("   nop");
}


