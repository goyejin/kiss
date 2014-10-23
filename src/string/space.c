// space.c : for kiss library.
//


#include "space.h"


/*
	with
	all_ascii_chars as
	(
	     select rownum - 1 as ascii_code,
	            chr( rownum - 1 ) as ascii_char
	       from dual
	    connect by rownum <= 256
	),
	all_ascii_faces as
	(
	     select ( ascii_code - mod( ascii_code, 8 ) ) / 8 as lineno,
	            ascii_code,
	            ascii_char,
	            case
	                when regexp_like( ascii_char, '[[:space:]]' )
	                then '0x' || rawtohex( ascii_char )
	                else '0x00'
	            end as ascii_face
	       from all_ascii_chars
	),
	all_ascii_table as
	(
	     select substr( sys_connect_by_path( ascii_face, ', ' ), 3 ) || ',' as line_content,
	            lineno,
	            ascii_code,
	            ascii_char,
	            ascii_face
	       from all_ascii_faces x
	      start with ascii_code = lineno * 8
	    connect by ascii_code = prior ascii_code + 1
	        and lineno = prior lineno
	        and ascii_code < ( lineno + 1 ) * 8
	)
	select line_content
	  from all_ascii_table
	 where ascii_code = lineno * 8 + 7;
*/
static const unsigned char space[ 256 ] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


int is_space( char c )
{
	return space[ ( unsigned char ) c ];
}


char * through_space( const char * s )
{
	for ( ; space[ ( unsigned char ) *s ]; ++s );
	return ( char * ) s;
}


char * reverse_through_space( const char * s, const char * e )
{
	for ( ; s >= e && space[ ( unsigned char ) *s ]; --s );
	return ( char * ) s;
}


char * through_nonspace( const char * s )
{
	for ( ; *s && !space[ ( unsigned char ) *s ]; ++s );
	return ( char * ) s;
}


char * reverse_through_nonspace( const char * s, const char * e )
{
	for ( ; s >= e && !space[ ( unsigned char ) *s ]; --s );
	return ( char * ) s;
}


char * through_last_space( const char * s )
{
	const char * e = s - 1;
	for ( ; *s; ++s )
	{
		if ( space[ ( unsigned char ) *s ] )
		{
			e = s;
		}
	}
	return ( char * ) ( e + 1 );
}


char * through_last_nonspace( const char * s )
{
	const char * e = s - 1;
	for ( ; *s; ++s )
	{
		if ( !space[ ( unsigned char ) *s ] )
		{
			e = s;
		}
	}
	return ( char * ) ( e + 1 );
}


char * through_linebody( const char * s )
{
	for ( ; *s && '\r' != *s && '\n' != *s; ++s );
	return ( char * ) s;
}


char * through_endofline( const char * s )
{
	if ( '\n' == *s )
	{
		++s;
	}
	else if ( '\r' == *s )
	{
		++s;
		if ( '\n' == *s )
		{
			++s;
		}
	}
	return ( char * ) s;
}


char * through_line( const char * s )
{
	return through_endofline( through_linebody( s ) );
}