/*! 

\page Example
\anchor Example

\section Example
This example shows how to convert between DATE_AND_TIME and STRING variables using the DTF library.

<a href = "y:\Application\Libraries\BRSE_DTF\Documentation\ConvertDate.zip" >Get the ZIP Import Package for AS3</a>

\par ConvertDate.typ
\code
TYPE
	ConvertDate_typ : 	STRUCT 
		Address : UDINT;
		Input : ConvertDateInput_typ;
		Output : ConvertDateOutput_typ;
	END_STRUCT;
	ConvertDateInput_typ : 	STRUCT 
		Command : ConvertDateInputCommand_typ;
		Format : STRING[BRSE_DTF_MAX_LENGTH_STRING];
		DataAsString : STRING[BRSE_DTF_MAX_LENGTH_STRING];
		DataAsDateTime : DATE_AND_TIME;
	END_STRUCT;
	ConvertDateInputCommand_typ : 	STRUCT 
		ConvertToString : USINT;
		ConvertToDateTime : USINT;
	END_STRUCT;
	ConvertDateOutput_typ : 	STRUCT 
		ConvertedToDateTime : DATE_AND_TIME;
		ConvertedToString : STRING[BRSE_DTF_MAX_LENGTH_STRING];
		Status : UINT;
	END_STRUCT;
END_TYPE
\endcode


\par ConvertDate.var
\code
VAR
	ConvertDate : ConvertDate_typ;
	ConversionFormat : BRSE_DTF_DateTimeFormat_typ;
END_VAR
\endcode

\par ConvertDate.st
\code
PROGRAM _INIT
	
	ConvertDate.Address := ADR(ConvertDate);

	ConvertDate.Input.Format := 'YYYY-MM-DD hh:mm:ss';

END_PROGRAM


PROGRAM _CYCLIC

	(*convert STRING[50] to DATE_AND_TIME*)
	IF ConvertDate.Input.Command.ConvertToDateTime <> 0 THEN

		ConvertDate.Output.Status := BRSE_DTF_CreateFormat(
			ADR(ConvertDate.Input.Format), 
			ADR(ConversionFormat));

		IF ConvertDate.Output.Status <> 0 THEN RETURN; END_IF

		ConvertDate.Output.Status := BRSE_DTF_StringToDT(
			ADR(ConvertDate.Input.DataAsString),
			ADR(ConversionFormat),
			ADR(ConvertDate.Output.ConvertedToDateTime));

		ConvertDate.Input.Command.ConvertToDateTime := 0;
		
	END_IF
	
	(*convert DATE_AND_TIME to STRING[50]*)
	IF ConvertDate.Input.Command.ConvertToString <> 0 THEN

		ConvertDate.Output.Status := BRSE_DTF_CreateFormat(
			ADR(ConvertDate.Input.Format), 
			ADR(ConversionFormat));

		IF ConvertDate.Output.Status <> 0 THEN RETURN; END_IF

		ConvertDate.Output.Status := BRSE_DTF_DTToString(
			ConvertDate.Input.DataAsDateTime,
			ADR(ConversionFormat),
			ADR(ConvertDate.Output.ConvertedToString));
		
		ConvertDate.Input.Command.ConvertToString := 0;
		
	END_IF

END_PROGRAM
\endcode


*/
