#ifndef LWIPOPTSFLAG_H
#define LWIPOPTSFLAG_H
// Common settings used in most of the pico_w examples
// (see https://www.nongnu.org/lwip/2_1_x/group__lwip__opts.html for details)]
#include "lwipopts.h"

// This section enables HTTPD server with SSI, SGI
// and tells server which converted HTML files to use
#define LWIP_HTTPD 1
#define LWIP_HTTPD_SSI 1
#define LWIP_HTTPD_CGI 1
#define LWIP_HTTPD_SSI_INCLUDE_TAG 0
#define HTTPD_FSDATA_FILE "htmldata.c"

#endif