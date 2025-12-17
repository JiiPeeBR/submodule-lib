
TYPE
	BRSE_DTF_DateTime_typ : 	STRUCT 
		start : USINT;
		length : USINT;
	END_STRUCT;
	BRSE_DTF_DateTimeFormat_typ : 	STRUCT  (*Structure describing where to put the values of the date&time at the beginning of the log entry*)
		format : STRING[BRSE_DTF_MAX_LENGTH_STRING];
		year : BRSE_DTF_DateTime_typ;
		month : BRSE_DTF_DateTime_typ;
		day : BRSE_DTF_DateTime_typ;
		hour : BRSE_DTF_DateTime_typ;
		minute : BRSE_DTF_DateTime_typ;
		second : BRSE_DTF_DateTime_typ;
	END_STRUCT;
END_TYPE
