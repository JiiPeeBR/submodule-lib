/*!

\page History

\section History

\par V1.00
\arg First version.

\par V1.10
\arg BRSE_DTF_StringToDT Added status ouput BRSE_DTF_ERR_INPUT when the date and time was outside valid bounds, eg. september 31st
\arg BRSE_DTF_CreateFormat now also saving the format string into the structure
\arg BRSE_DTF_DTToString Changed so that the format string is copied to the output string before copying the values

\par V1.11
\arg Library dependency has been changed from AsString to AsBrStr, so that conflicts can be avoided with ANSI-C standard functions(atof, atoi etc.)
*/
