#CServer
**(what is it)** A simple C-based http server to host rest-api endpoints.


**(why is it done)**
This is a hobby project to build various components needed to build an HTTP Server in C and incrementally add different component to understand web-service in detail.
Started as a weekend project I am continuing this to see how far it goes.


**(deps)**

 1. (make) build tool
 2. gcc installation
 3. OpenSSL installation 

**(OpenSSL)**
* MAC user can install OpenSSL using brew - brew install openssl
* Linux installation - sudo apt-get install libssl-dev
* For windows or other alternate OS'es check - https://www.openssl.org/source/

After OpenSSL installation please set OPENSSL_LIB and OPENSSL_INCLUDE environment variable.
eg :- export OPENSSL_LIB /path/to/openssl/lib/installation

**(how to use it)**

 1. Currently it is phase-0 where a rest handler can be added through a quick command
 2. cd tools;  python3 server_app.py --add-controller=<controller_name\>
 3. DO NOT FORGET TO REBUILD PROJECT AFTER ADDING A CONTROLLER. (follow how to build)
 4. Follow the steps shown in the commandline output of above command and add business-logic at rest-endpoint into <controller_name\>_endpoint.c 
 5. start the server (./cserver)

Now all requests to http://cserver:port/<controller_name\>/ is routed to newly created controller. Add handling to play with it.

**(how to build)**
run "make cserver" at the root folder of this project.


**(what now)**

  * Make it Multi-threaded.
  * Add a JSON parser to parse json request-body.
  * Parse HTTP URL to get parameters after '?'
  * Enhance router logic to include complex url such as <u>*http://cserver:port/**endpoint**/xyz/123/filename*</u>
  * Add configuration driven service startup.
  * Identify methods to add throttling and rate-limiting at API-level into C-Server.

**Note** - It has no intention to become next web-server. However, this is a quick tool to experiment and run quick logic to see how does that work. Being light-weight this C-Server is easy to host and run.

 
Enjoy !!
