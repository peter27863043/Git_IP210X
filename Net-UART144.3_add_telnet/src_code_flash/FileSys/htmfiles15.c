/******************************************************************************
*
*   Name:           
*
*   Description:    
*
*   Copyright:      (c) 2005-2050    IC Plus Corp.
*                   All rights reserved.  By Jesse
*
*******************************************************************************/



/******************************************************************************
Need to modify following string to match bank# :
* (for example bank15)
* files_table07 (x2) in array and in fs_open15()
* cgi_table07   (x2) in array and in fs_open15()
* fs_open07     (x1) in fs_open15()
* datacpy07     (x1) in datacpy15()
* get_tag07     (x1) in get_tag15()
******************************************************************************/







/******************************************************************************
*
*   Name:           htmfiles.c
*
*   Description:    htmfiles in bank15
*
*   Copyright:      (c) 2005-2050    IC Plus Corp.
*                   All rights reserved.  By Chance
*
*******************************************************************************/
#include <stdlib.h>
#include "type_def.h"
#include "fs.h"
#include "uip.h"
#include "httpd.h"
#include <string.h>
//*****include html files*********

#include "dido_htm.c"
extern u8_t ssi_dido(u8_t varid, data_value *vp);
extern u8_t cgi_dido(u8_t cnt, void *vptr);

//*************File System*********
SFILENAME code files_table15[] = {
{"dido.htm",            dido_htm_file,    		sizeof(dido_htm_file),   	0},
{"cgi/dido.cgi",        NULL,             		NULL,                    	1},	
{ NULL,                 NULL,             		NULL,                    	NO_EX_FUNC},
};
//*************CGI service function table*********
CGI_FUNC_T code cgi_table15[] = {
{ssi_dido,    	dido_htm_tags},     //05
{cgi_dido,    	NULL},             	//12
{NULL,        	NULL},
};

/******************************************************************************
*
*  Function:    fs_open15
*
*  Description:  find request filename or cgi in bank15
*               
*  Parameters:  address of filename
*               
*  Returns:     address of filesystem
*               
*******************************************************************************/
SFILENAME *  fs_open15(char *name)
{
    SFILENAME  *ptr;
    HS->cgi_func_id=NO_EX_FUNC;
    if (name[0] == '/')
    {
        name++;
        if (*name == '\0')
            return NULL;
    }
    for (ptr = files_table15; ptr->file_name != NULL; ptr++)
    {
        if (strcmp(name, ptr->file_name) == 0)
        {
					 HS->file=*ptr;
        	 if(ptr->func_id!=NO_EX_FUNC)
        	 {
        	 		HS->cgi_func=cgi_table15[ptr->func_id];
        	 		HS->cgi_func_id=ptr->func_id;
        	 }
           return &HS->file;
	  	}
    }
    return NULL;
}

/******************************************************************************
*
*  Function:    datacpy15
*
*  Description: data copy function for Bank15
*               
*  Parameters:  data copy structure
*               
*  Returns:     None
*               
*******************************************************************************/
void datacpy15(mem_cpy_fs *inputdata)
{
    memcpy(inputdata->dest_ptr, inputdata->source_ptr, inputdata->len ) ;      
}

/******************************************************************************
*
*  Function:    get_tag15
*
*  Description: data copy function for Bank15
*               
*  Parameters:  index
*               
*  Returns:     None
*               
*******************************************************************************/
struct html_tags get_tag15(u8_t index)
{
		return HS->cgi_func.tags[index];
}