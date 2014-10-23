// space.h : for kiss library.
//


#ifndef __SPACE_H__
#define __SPACE_H__


int is_space( char c );
char * through_space( const char * s );
char * reverse_through_space( const char * s, const char * e );
char * through_nonspace( const char * s );
char * reverse_through_nonspace( const char * s, const char * e );
char * through_last_space( const char * s );
char * through_last_nonspace( const char * s );
char * through_linebody( const char * s );
char * through_endofline( const char * s );
char * through_line( const char * s );


#endif // __SPACE_H__
