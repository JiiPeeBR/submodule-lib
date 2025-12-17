
FUNCTION BRSE_DTF_CreateFormat : UINT (*Parse a format string and fill the format structure*)
	VAR_INPUT
		pFormatString : UDINT; (*String format*)
		pFormat : UDINT; (*Pointer to a BRSE_DTF_DateTimeFormat_typ*)
	END_VAR
END_FUNCTION

FUNCTION BRSE_DTF_DTToString : UINT (*Returns error code, 0=no error*)
	VAR_INPUT
		DT1 : DATE_AND_TIME; (*32 bit date time in seconds since 1970*)
		pFormat : UDINT; (*Pointer to a BRSE_DTF_DateTimeFormat_typ, created by BRSE_DTF_CreateDateTimeFormat*)
		pStringOutput : UDINT; (*Pointer to formatted string.*)
	END_VAR
END_FUNCTION

FUNCTION BRSE_DTF_StringToDT : UINT (*Returns error code, 0=no error*)
	VAR_INPUT
		pString : UDINT; (*Pointer to formatted string.*)
		pFormat : UDINT; (*Pointer to a BRSE_DTF_DateTimeFormat_typ, created by BRSE_DTF_CreateDateTimeFormat*)
		pDTOutput : UDINT; (*Pointer to return date time value (seconds since 1970)*)
	END_VAR
END_FUNCTION
