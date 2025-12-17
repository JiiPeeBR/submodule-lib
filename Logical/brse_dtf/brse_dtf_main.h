/*! \file brse_csv_main.h */

/*! \mainpage BRSE_DTF
	\section Introduction
	
	BRSE_DTF (Date Time Format) is a library used for converting DATE_AND_TIME variables into readable strings via a defined format.
	
	\arg The format is put together by Y=year (1970-2099), M=month (1-12), D=day (1-31), h=hour (0-23), m=minute (0-59), s=second (0-59).
	
	\arg A common example is: YYYY-MM-DD hh:mm:ss.
	
	\arg A format (BRSE_DTF_DateTimeFormat_typ) is created from the format string. This format structure is then used to convert DATE_AND_TIME variables to and from a string value.
	
	\par Important
	Always use the \b BRSE_DTF_MAX_LENGTH_STRING as length for your format string, as well as for your output strings.
	The library will not take care of limiting the string output to something smaller than this length!
	
	See an \ref Example on how to use the library.
	
*/
#include <bur/plctypes.h>
#include <AsBrStr.h>
#include <string.h> /*this will override the asstring functions*/
#include <sys_lib.h>
#include "BRSE_DTF.h"
