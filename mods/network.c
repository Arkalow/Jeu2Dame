#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "Vector.h"
#include "network.h"


void *network_connect(void * arg)
{
    printf("start thread\n");
    struct Data thread_param = *((struct Data*)arg);
    network_server(thread_param.port_src);
    (void) arg;
    printf("Close thread\n");
    pthread_exit(NULL);
}


int network_server(int PORT)
{
    int status = EXIT_SUCCESS;
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif
 
    SOCKET sock;
    SOCKADDR_IN sin;
    SOCKET csock;
    SOCKADDR_IN csin;
    char buffer[32] = "OK !";
    socklen_t recsize = sizeof(csin);
    int sock_err;
 
    /* Si les sockets Windows fonctionnent */
    if(!erreur)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
 
        /* Si la socket est valide */
        if(sock != INVALID_SOCKET)
        {
            printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);
 
            /* Configuration */
            sin.sin_addr.s_addr    = htonl(INADDR_ANY);   /* Adresse IP automatique */
            sin.sin_family         = AF_INET;             /* Protocole familial (IP) */
            sin.sin_port           = htons(PORT);         /* Listage du port */
            sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));
 
            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                /* Démarrage du listage (mode server) */
                sock_err = listen(sock, 5);
                printf("Listage du port %d...\n", PORT);
 
                /* Si la socket fonctionne */
                if(sock_err != SOCKET_ERROR)
                {
                    /* Attente pendant laquelle le client se connecte */
                    printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);        
 
                    csock = accept(sock, (SOCKADDR*)&csin, &recsize);
                    printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
 
                    sock_err = send(csock, buffer, 32, 0);

                    if(sock_err != SOCKET_ERROR)
                        printf("Chaine envoyée : %s\n", buffer);
                    else
                        printf("Erreur de transmission\n");
 
                    /* Il ne faut pas oublier de fermer la connexion (fermée dans les deux sens) */
                    if(!shutdown(csock, SHUT_RD))
                        perror("shutdown");
                    if(!shutdown(sock, SHUT_RD))
                        perror("shutdown");
                }else{
                    perror("bind");
                    status = EXIT_FAILURE;
                }

            }else{ 
                perror("bind");
                status = EXIT_FAILURE;
            }
 
            /* Fermeture de la socket */
            printf("Fermeture de la socket...\n");
            if(!closesocket(sock))
                perror("closesocket");

            if(!closesocket(csock))
                perror("closesocket");
            
            printf("Fermeture du serveur terminee\n");
        }else{
            printf("La socket est invalide\n");
            status = EXIT_FAILURE;
        }
 
        #if defined (WIN32)
            WSACleanup();
        #endif
    }else{
        printf("Les sockets windows ne fonctionnent pas\n");
        status = EXIT_FAILURE;
    }
 
    return status;
}

int network_client(char * response, int PORT)
{
    #if defined (WIN32)
        WSADATA WSAData;
        int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
    #else
        int erreur = 0;
    #endif
 
    int status = EXIT_SUCCESS;

    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[32] = "";
 
    /* Si les sockets Windows fonctionnent */
    if(!erreur)
    {
        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);
 
        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr("127.0.0.1");
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
 
        /* Si l'on a réussi à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        {
            printf("Connection à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
            
            /* Si l'on reçoit des informations : on les affiche à l'écran */
            if(recv(sock, buffer, 32, 0) != SOCKET_ERROR)
            {
                printf("Recu : %s\n", buffer);
                strcpy(response, buffer);
            }
        }
        /* sinon, on affiche "Impossible de se connecter" */
        else
        {
            //printf("Impossible de se connecter\n");
            status = EXIT_FAILURE;
        }
 
        /* On ferme la socket */
        closesocket(sock);
 
        #if defined (WIN32)
            WSACleanup();
        #endif

    }else{
        status = EXIT_FAILURE;
    }

    return status;
}