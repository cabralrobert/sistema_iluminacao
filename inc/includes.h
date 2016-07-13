/*******************************************************
*                                                      *
*   Criado em: Qui 07/Jul/2016,  20:15 hs              *
*   Instituicao: Universidade Federal do Ceará         *
*   Autor: Robert Cabral                               *
*   email: robertcabral@alu.ufc.br                     *
*                                                      *
********************************************************/
#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <pthread.h>

char *getIP();

#endif
