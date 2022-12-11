/***********************************************************************************************************
* root_app.c
*
* CServer entry-point. All initialization and registration is done here. run starts the CServer and starts 
* serving all incomgin request.
*
* Author - Anand Kumar 
************************************************************************************************************/

#include "request_router.h"
#include "http_server.h"
#include "handlers.h"
#include "logger.h"

int run_root_app() {
        LOG_DEBUG("starting cserver....");

	_router_ router = init_router();
	REGISTER_HANDLERS(router)
        run(router);

        return 0;
}

