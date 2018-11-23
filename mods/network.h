#if defined (WIN32)
    #include <winsock2.h>
    typedef int socklen_t;
#elif defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

/**
 * Represente le tour du joueur
 */
struct Data{
    struct Vector posStart; // Position du pion selectionné
    struct Vector posEnd; // Position du pion destination
    struct Vector posPrises[NB_PION]; // Tableau de positions des prises
    int nbPrise; // Nombre de prise effectuées

    int port_src, port_des; // Port source et destination
};

/**
 * Lance laa fonction network_server dans un thread
 */
void *network_connect(void * arg);

/**
 * Ecoute les socket sur le port PORT
 * Et renvoie une donnée
 */
int network_server(int PORT);

/**
 * Se connecte au serveur et recupere une socket.
 * Les données sont sous forme de chaine de caractère récupérer par adresse dans la variable response
 */
int network_client(char * response, int PORT);
