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
* (for example bank07)
* files_table07 (x2) in array and in fs_open10()
* cgi_table07   (x2) in array and in fs_open10()
* fs_open07     (x1) in fs_open10()
* datacpy07     (x1) in datacpy10()
* get_tag07     (x1) in get_tag10()
******************************************************************************/







/******************************************************************************
*
*   Name:           htmfiles.c
*
*   Description:    htmfiles in bank10
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



#include "telnet_htm.c"
extern u8_t cgi_telnet(u8_t cnt, void *vptr);
extern u8_t ssi_telnet(u8_t varid, data_value *vp);



//*************File System*********
SFILENAME code files_table10[] = {
{"telnet.htm",          telnet_htm_file,  sizeof(telnet_htm_file),  0},
{"cgi/telnet.cgi",      NULL,             NULL,                    	1},	
{ NULL,                 NULL,             NULL,                    	NO_EX_FUNC},
};
//*************CGI service function table*********
CGI_FUNC_T code cgi_table10[] = {
	{ssi_telnet,  telnet_htm_tags}, 
	{cgi_telnet,  NULL},            
	{NULL,        NULL},
};

struct html_tags  telnet_htm_tags_Buffer =  { 0, 0 }; 


/******************************************************************************
*
*  Function:    fs_open10
*
*  Description:  find request filename or cgi in bank10
*               
*  Parameters:  address of filename
*               
*  Returns:     address of filesystem
*               
*******************************************************************************/
SFILENAME *  fs_open10(char *name)
{
    SFILENAME  *ptr;
    HS->cgi_func_id=NO_EX_FUNC;
    if (name[0] == '/')
    {
        name++;
        if (*name == '\0')
            return NULL;
    }
    for (ptr = files_table10; ptr->file_name != NULL; ptr++)
    {
        if (strcmp(name, ptr->file_name) == 0)
        {
					 HS->file=*ptr;
        	 if(ptr->func_id!=NO_EX_FUNC)
        	 {
        	 		HS->cgi_func=cgi_table10[ptr->func_id];
        	 		HS->cgi_func_id=ptr->func_id;
        	 }
           return &HS->file;
	  	}
    }
    return NULL;
}

/******************************************************************************
*
*  Function:    datacpy10
*
*  Description: data copy function for Bank10
*               
*  Parameters:  data copy structure
*               
*  Returns:     None
*               
*******************************************************************************/
void datacpy10(mem_cpy_fs *inputdata)
{
    memcpy(inputdata->dest_ptr, inputdata->source_ptr, inputdata->len ) ;      
}

/******************************************************************************
*
*  Function:    get_tag10
*
*  Description: data copy function for Bank10
*               
*  Parameters:  index
*               
*  Returns:     None
*               
*******************************************************************************/
struct html_tags get_tag10(u8_t index)
{
		telnet_htm_tags_Buffer.pos 	=telnet_htm_tags[index].pos;
		telnet_htm_tags_Buffer.varid=telnet_htm_tags[index].varid;
		return telnet_htm_tags_Buffer;
		//return HS->cgi_func.tags[index];
}
