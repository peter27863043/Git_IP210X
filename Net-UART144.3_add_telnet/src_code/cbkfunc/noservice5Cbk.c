#include "type_def.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type_def.h"
#include "fs.h"
#include "httpd.h"
#include "uip.h"
//include html files
#include "NoService5_htm.h"
extern u8_t errmsgflag;

u8_t ssi_noservice5(u8_t varid, data_value *vp)
{
    switch (varid)
    {
        case CGI_NS5_TITLE1 :
			vp->value.string = hs->errormsg;
			vp->type = string;
            break ;
			
        case CGI_NS5_TITLE2 :
            vp->value.string = "Wait";
            vp->type = string;
			break;
		
		
		case CGI_NS5_DELAY_SEC:
			vp->type=digits_3_int;
			vp->value.digits_3_int=errmsgflag-ERRORMSG_WAIT0;
			break;	

     }
    return OK;
}


u8_t cgi_noservice5(u8_t cnt, void *vptr)
{
	return OK;
}


