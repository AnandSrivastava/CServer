/***********************************************************************************************************
* ssl_conn.c
*
* Open SSL utility method.
*
* Author - Anand Kumar 
************************************************************************************************************/

#include "openssl/ssl.h"
#include "openssl/err.h"

#include "ssl_conn.h"
#include "logger.h"

/*
 * Initialize open_ssl context.
 * sets up open-ssl-algorithm, error string and methods.
 * Creates a new open-ssl context. 
 * @return created openssl context.
*/
SSL_CTX *Initialize_ssl_context() {
	SSL_METHOD *method = NULL;
	SSL_CTX *ctx = NULL;

	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = TLSv1_2_server_method();
	ctx = SSL_CTX_new(method);
	if(ctx == NULL) {
		ERR_print_errors_fp(stderr);
		abort();
	}

	SSL_CTX_set_options(ctx, SSL_OP_IGNORE_UNEXPECTED_EOF);

	return ctx;
}

/*
 * Loads given certificate to be used by open-ssl context to establish secure connection with client. 
 * @params ctx - OpenSSL context initialized at the start of the app
 * @params certFile - .pem file containg server certificate
 * @params keyFile - .pem file containing cert key 
*/
void LoadCertificates(SSL_CTX *ctx, const char *certFile, const char * keyFile) {
	if(SSL_CTX_use_certificate_file(ctx, certFile, SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		abort();
	}

	if(SSL_CTX_use_PrivateKey_file(ctx, keyFile, SSL_FILETYPE_PEM) <= 0) {
		ERR_print_errors_fp(stderr);
		abort();
	}

	if(!SSL_CTX_check_private_key(ctx)) {
		fprintf(stderr, "Private key does not match the public certificate\n");
		abort();
	}
}


/*
 * Helper method to log cert details (Used for debugging)
 * @param ssl - secure connection created to communicate with client.
*/
void ShowCerts(SSL* ssl)
{
    X509 *cert;
    char *line;
    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if ( cert != NULL ) {
        LOG_DEBUG("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        LOG_DEBUG(line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        LOG_DEBUG(line);
        free(line);
        X509_free(cert);
    } else
        LOG_DEBUG("No certificates.\n");
}

//@see-def
SSL_CTX *Init_SSL() {
	SSL_library_init();
	SSL_CTX *ctx = Initialize_ssl_context();
	LoadCertificates(ctx, "cert.pem", "key.pem");

	return ctx;
}

//@see-def
SSL* SSL_New_connect(SSL_CTX *ctx, int socket_id) {
	SSL *ssl = SSL_new(ctx);
	SSL_set_fd(ssl, socket_id);
	if ( SSL_accept(ssl) == FAIL )
        	ERR_print_errors_fp(stderr);
    	else
        	ShowCerts(ssl);

	return ssl;
}
