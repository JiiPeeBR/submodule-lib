/*! \file brse_csv_main.h */

#include "brse_dtf_main.h"

/************************************************************************
  _____                _          __                           _   
 / ____|              | |        / _|                         | |  
| |     _ __ ___  __ _| |_ ___  | |_ ___  _ __ _ __ ___   __ _| |_ 
| |    | '__/ _ \/ _` | __/ _ \ |  _/ _ \| '__| '_ ` _ \ / _` | __|
| |____| | |  __/ (_| | ||  __/ | || (_) | |  | | | | | | (_| | |_ 
 \_____|_|  \___|\__,_|\__\___| |_| \___/|_|  |_| |_| |_|\__,_|\__|
*************************************************************************/
 
#define START_END_FORMAT(_item_, _strdesc_) 	\
	pSeek = pStrFormat;							\
	length = strcspn(pSeek,_strdesc_);			\
												\
	if(length < strlen(pSeek))					\
	{	pFormat->_item_.start = length;			\
		pSeek+=length;							\
		length = strspn(pSeek,_strdesc_);		\
												\
		pFormat->_item_.length = length;		\
	}											\
	else										\
	{											\
		pFormat->_item_.start = 0;				\
		pFormat->_item_.length = 0;				\
	}
	
/*! \interface BRSE_DTF_CreateFormat
	\brief Create a date time format from a format string (like YYYY-MM-DD hh:mm:ss).
	
	This function parametrizes the format structure which is used as an input 
	to BRSE_DTF_DTToString and BRSE_DTF_StringToDT. You set a string which defines
	how your output string will look like.
	\par Note
	If you use only two characters for the year in the format YY, the library will assume
	that you mean a year past 2000. You could change this by setting BRSE_DTF_CENTURY_OFFSET to zero.
	
	\param pFormatString Pointer to the string
	\param pFormat Pointer to BRSE_DTF_DateTimeFormat_typ, the resulting format.
	\retval 0 if successful.
	\retval BRSE_DTF_ERR_INPUT if one of the input pointers are zero
*/
UINT BRSE_DTF_CreateFormat(UDINT formatStringAddress, UDINT formatAddress)
{
	BRSE_DTF_DateTimeFormat_typ *pFormat;
	char 	*pStrFormat;
	char	*pSeek;
	UINT 	length;	
	
	if (formatStringAddress == 0 || formatAddress == 0)
		return BRSE_DTF_ERR_INPUT;
	
	pFormat = (BRSE_DTF_DateTimeFormat_typ *)formatAddress;
	pStrFormat = (char *)formatStringAddress;

	strncpy(pFormat->format,pStrFormat,BRSE_DTF_MAX_LENGTH_STRING);

	START_END_FORMAT( year, 	"Y" );
	START_END_FORMAT( month, 	"M" );
	START_END_FORMAT( day, 		"D" );
	START_END_FORMAT( hour, 	"h" );
	START_END_FORMAT( minute, 	"m" );
	START_END_FORMAT( second, 	"s" );
	
	return 0;
}

/*************************************************************************
 _______       _____ _        _             
|__   __|     / ____| |      (_)            
   | | ___   | (___ | |_ _ __ _ _ __   __ _ 
   | |/ _ \   \___ \| __| '__| | '_ \ / _` |
   | | (_) |  ____) | |_| |  | | | | | (_| |
   |_|\___/  |_____/ \__|_|  |_|_| |_|\__, |
                                       __/ |
                                      |___/ 
*************************************************************************/
#define COPY_DATE_TIME(_item_) 					\
	brsitoa(pTime->_item_,(UDINT)ascii_val);		\
	length = strlen(ascii_val);					\
	offset = 0;									\
	startoffset = 0;							\
												\
	if(length > pFormat->_item_.length)			\
	{											\
		/*eg. YY is specified and year is 1981 */\
		offset = length - pFormat->_item_.length;\
		/*start with ascii_val[offset]*/ 		\
		length = pFormat->_item_.length;		\
	}											\
	else if(length < pFormat->_item_.length)	\
	{											\
		/*lets say month is 9, and MM is specified*/\
		startoffset = pFormat->_item_.length - length;\
		/*start copying one character later*/	\
	}											\
												\
	memset(pStr + pFormat->_item_.start,'0',pFormat->_item_.length);/*insert leading zeros to make it 2005-05-05 instead of 2005- 5 - 5*/\
	memcpy(pStr + pFormat->_item_.start + startoffset ,&ascii_val[offset],length);

/*! \interface BRSE_DTF_DTToString
	\brief Convert a DATE_AND_TIME value to string using a certain created format.

	\param DT1 DATE_AND_TIME to convert.
	\param pFormat Pointer to BRSE_DTF_DateTimeFormat_typ, the format to use.
	\param pStringOutput Pointer to the resulting string.
	\retval 0 if successful.
	\retval BRSE_DTF_ERR_INPUT if one of the input pointers are zero
*/
UINT BRSE_DTF_DTToString(DATE_AND_TIME dt, UDINT formatAddress, UDINT stringOutputAddress)
{
	char *pStr = 0;
	BRSE_DTF_DateTimeFormat_typ *pFormat = 0;
	DTStructure dtStruct;
	DTStructure *pTime = &dtStruct;
	char ascii_val[15];
	UDINT length,offset,startoffset;
	
	if (formatAddress == 0 || stringOutputAddress == 0)
		return BRSE_DTF_ERR_INPUT;
	
	memset(&dtStruct, 0, sizeof(dtStruct));	
	DT_TO_DTStructure(dt, (UDINT)&dtStruct);
	pStr = (char *)stringOutputAddress;
	pFormat = (BRSE_DTF_DateTimeFormat_typ *)formatAddress;
	
	strncpy(pStr,pFormat->format,BRSE_DTF_MAX_LENGTH_STRING);
	
	COPY_DATE_TIME(year);
	COPY_DATE_TIME(month);
	COPY_DATE_TIME(day);
	COPY_DATE_TIME(hour);
	COPY_DATE_TIME(minute);
	COPY_DATE_TIME(second);
	
	return 0;
}

/**************************************************************************
 ______                      _____ _        _             
|  ____|                    / ____| |      (_)            
| |__ _ __ ___  _ __ ___   | (___ | |_ _ __ _ _ __   __ _ 
|  __| '__/ _ \| '_ ` _ \   \___ \| __| '__| | '_ \ / _` |
| |  | | | (_) | | | | | |  ____) | |_| |  | | | | | (_| |
|_|  |_|  \___/|_| |_| |_| |_____/ \__|_|  |_|_| |_|\__, |
                                                     __/ |
                                                    |___/ 
*************************************************************************/

#define PARSE_DATE_TIME(_item_) 				\
												\
	memset(&ascii_val[0], 0, sizeof(ascii_val));\
	memcpy(&ascii_val[0], pStr + pFormat->_item_.start, pFormat->_item_.length);\
	for (i=0; i<pFormat->_item_.length; i++)	\
	{											\
		if (ascii_val[i] < 0x30 || ascii_val[i] > 0x39)\
		{										\
			return BRSE_DTF_ERR_FORMAT;			\
		}										\
	}											\
	pTime->_item_ = brsatoi((UDINT)&ascii_val[0]);

/*! \interface BRSE_DTF_StringToDT
	\brief Parse a string to DATE_AND_TIME value using a certain created format.

	\param pString string to parse.
	\param pFormat Pointer to BRSE_DTF_DateTimeFormat_typ, the format to use.
	\param pDTOutput Pointer to the resulting DATE_AND_TIME object.
	\retval 0 if successful.
	\retval BRSE_DTF_ERR_INPUT if one one the input pointers are zero
	\retval BRSE_DTF_ERR_FORMAT if the input string does not give a valid date
*/
UINT BRSE_DTF_StringToDT(UDINT stringAddress, UDINT formatAddress, UDINT dateTimeOutputAddress)
{
	char *pStr = 0;
	DTStructure dtStruct;
	DTStructure *pTime = &dtStruct;
	BRSE_DTF_DateTimeFormat_typ *pFormat= 0;
	DATE_AND_TIME dt = 0;
	char ascii_val[15];
	int i = 0;
	if (stringAddress == 0 || formatAddress == 0)
		return BRSE_DTF_ERR_INPUT;
		
	pStr = (char *)stringAddress;
	pFormat = (BRSE_DTF_DateTimeFormat_typ *)formatAddress;
	
	memset(&dtStruct, 0, sizeof(dtStruct));
	PARSE_DATE_TIME(year);
	PARSE_DATE_TIME(month);
	PARSE_DATE_TIME(day);
	PARSE_DATE_TIME(hour);
	PARSE_DATE_TIME(minute);
	PARSE_DATE_TIME(second);
	
	if (pFormat->year.length > 0 && dtStruct.year < 1970) /* add current year */
		dtStruct.year += BRSE_DTF_CENTURY_OFFSET;
	
	/* set default valuess where 0 is not accepted */
	if (dtStruct.year == 0) 
		dtStruct.year = 1970;
	if (dtStruct.month == 0) 
		dtStruct.month = 1;
	if (dtStruct.day == 0) 
		dtStruct.day = 1;
		
	dt = DTStructure_TO_DT((UDINT)&dtStruct);
	
	if((UDINT)dt == 0xFFFFFFFF) return BRSE_DTF_ERR_FORMAT;
	
	memcpy((DATE_AND_TIME *)dateTimeOutputAddress, &dt, sizeof(dt));
	return 0;
}
