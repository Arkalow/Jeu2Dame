#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <string.h>
#include "../define.h"
#include "Vector.h"
#include "Player.h"
#include "../main.h"
#include "network.h"

void *network_connect(void * arg)
{
    debug("start thread\n");
    struct Data thread_param = *((struct Data*)arg);
    // Encode data
    char buffer[200];
    strcpy(buffer, encode_data(thread_param));
    int compteur = 0;
    // GERER L'ERREUR DE CONNEXION!!
    while(compteur < 100 && network_server(buffer, thread_param.addr_src, thread_param.port_src) == EXIT_FAILURE) compteur++;
    (void) arg;
    debug("Close thread\n");
    pthread_exit(NULL);
}

char * encode_data(struct Data data)
{
    char * str;
    str = (char *)malloc(sizeof(char) * 100); /* make space for the new string (should check the return value ...) */
    str[0] = '\0';
    // Coordonnées start
    str = strcat(str, vectorToString(data.posStart));
    str = strcat(str, ";");

    // Coordonnées end
    str = strcat(str, vectorToString(data.posEnd));
    str = strcat(str, ";");

    // Liste des prises
    if(data.nbPrise > 1)
    {
        for(int i = 0; i < data.nbPrise; i++)
        {
            str = strcat(str, vectorToString(data.posPrises[i]));
            str = strcat(str, ";");
        }
    }
    else if(data.nbPrise == 1)
    {
        str = strcat(str, vectorToString(data.posPrises[0]));
        str = strcat(str, ";");
    }

    str = strcat(str, ";");

    debug("Fin encode\n");
    return str;
}

struct Data decode_data(char * str)
{
    struct Data data;
    debug("\t\tDECODE DATA : \n");

    data.posStart = stringToVector(str);
    while(str++[0] != ';');

    data.posEnd = stringToVector(str);
    while(str++[0] != ';');
    
    data.nbPrise = 0;
    while(str[0] != ';')
    {
        data.posPrises[data.nbPrise] = stringToVector(str);
        while(str++[0] != ';');
        data.nbPrise++;
    }
    return data;
}

int network_server(char buffer[200], char * addr_src, int PORT)
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
    socklen_t recsize = sizeof(csin);
    int sock_err;
    int yes = 1;
 
    /* Si les sockets Windows fonctionnent */
    if(!erreur)
    {
        sock = socket(AF_INET, SOCK_STREAM, 0);
 
        /* Si la socket est valide */
        if(sock != INVALID_SOCKET)
        {
            debug("La socket est maintenant ouverte en mode TCP/IP\n");
 
            /* Configuration */
            // sin.sin_addr.s_addr    = htonl(INADDR_ANY);   /* Adresse IP automatique */
            sin.sin_addr.s_addr = inet_addr(addr_src);
            sin.sin_family         = AF_INET;             /* Protocole familial (IP) */
            sin.sin_port           = htons(PORT);         /* Listage du port */

            // lose the pesky "Address already in use" error message
            if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
                perror("setsockopt");
                pthread_exit(NULL);
            }

            sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));
 
            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                /* Démarrage du listage (mode server) */
                sock_err = listen(sock, 5);
                debug("Listage du port...\n");
 
                /* Si la socket fonctionne */
                if(sock_err != SOCKET_ERROR)
                {
                    /* Attente pendant laquelle le client se connecte */
                    debug("Patientez pendant que le client se connecte sur le port...\n");        
 
                    csock = accept(sock, (SOCKADDR*)&csin, &recsize);
                    debug("Client connecte");
                    //printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
 
                    sock_err = send(csock, buffer, 32, 0);

                    if(sock_err != SOCKET_ERROR)
                        debug("Data envoyee");
                    else
                        debug("Erreur de transmission\n");
 
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
            debug("Fermeture de la socket...\n");
            if(!closesocket(sock))
                perror("closesocket");

            if(!closesocket(csock))
                perror("closesocket");
            
            debug("Fermeture du serveur terminee\n");
        }else{
            fprintf(stderr, "La socket est invalide\n");
            status = EXIT_FAILURE;
        }
 
        #if defined (WIN32)
            WSACleanup();
        #endif
    }else{
        fprintf(stderr, "Les sockets windows ne fonctionnent pas\n");
        status = EXIT_FAILURE;
    }
 
    return status;
}

int network_client(char * response, char * addr_des, int PORT)
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
        sin.sin_addr.s_addr = inet_addr(addr_des);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);
 
        /* Si l'on a réussi à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        {
            //printf("Connection à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
            debug("Connexion...\n");
            /* Si l'on reçoit des informations : on les affiche à l'écran */
            if(recv(sock, buffer, 32, 0) != SOCKET_ERROR)
            {
                debug("Data recu");
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