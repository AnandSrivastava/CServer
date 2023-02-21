/***********************************************************************************************************
* ssl_conn.h
*
* OpenSSL specific utility method to establish secure connection to the client.
*
* Author - Anand Kumar 
************************************************************************************************************/

#ifndef _SSL_CONN_H_
#define _SSL_CONN_H_

#define FAIL -1


/*
* Initialize OpenSSL context to be used in client connection. Same context is shared across all clients.
* @return SSL context to be used across all clients.
*/
SSL_CTX *Init_SSL();

/*
* Create an SSL connection with client on given socket.
* @params ctx - SSL context initialized at the start of the app.
* @params socket_id - socket at which client is connected.
* @return SSL connection through which app can read and write to client.
*/
SSL* SSL_New_connect(SSL_CTX *ctx, int socket_id);

#endif
