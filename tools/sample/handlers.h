#ifndef __HANDLERS_H__
#define __HANDLERS_H__

/**************************************(AUTO GENERATED)***************************************
* DO NOT MODIFY
* This file is auto-generated during compilation process which ensures that all created
* controller is registered.
* Author - Anand Kumar
* Github repo - https://github.com/l1nk-0
**********************************************************************************************/

#define MAKE_QUOTED(x) #x
#define INCLUDES(x) MAKE_QUOTED(x##_endpoint.h)

#define CALL_REGISTRATION(x) get_##x##_handler()
#define REGISTER_ONE(r,x) register_endpoint(r, MAKE_QUOTED(x), CALL_REGISTRATION(x))

{{HEADERS}}

#define REGISTER_HANDLERS(r) \
{{REGISTER}}

#endif
