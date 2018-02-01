/*	signalHandlerExample.c

	Extracted from CS 361 class notes, Fall 2017 by John Bell
	
	Modified by ...
*/


#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

const int N = 5;
int signalCaught = 0;

// Signal Handler

void int_handler( int sig ) {
        signalCaught = sig;
	return;
}

// Main

int main( int argc, char ** argv ) {
	
    pid_t pid[ N ];
    int i, child_status, time2Sleep;
    
    // Register the signal handler for SIGINT
    
    signal( SIGINT, int_handler );
    
    // Fork off a bunch of children
    
    for ( i = 0; i < N; i++ ) {
        if ( ( pid[ i ] = fork( ) ) == 0 ) {
            while ( 1 ) { // infinite loop
            	  if( signalCaught ) {
			              printf( "Process %d received signal %d\n", getpid( ), signalCaught );
    			          exit( signalCaught );
    		        }
	          }
   	        exit( -1 );  // Safety.  This line should never execute.
        } else { // parent
	          printf( "Created process %d\n", pid[ i ] );
	      }
    }
    
    // Only the parent should make it past this point
    
    // Pause here if requested
    
    if( argc > 1 && ( ( time2Sleep = atoi( argv[ 1 ] ) ) > 0 ) )
    	sleep( time2Sleep ) ;
        
    // Okay, now send SIGINT signals to all the kids
    
    for ( i = 0; i < N; i++ ) {
        printf( "Killing process %d\n", pid[ i ] );
        kill( pid[ i ], SIGINT );
    }
    
    // And finally to wait for all kids and report their status
    
    for ( i = 0; i < N; i++ ) {
        pid_t wpid = wait( &child_status );
        if ( WIFEXITED( child_status ) )
            printf( "Child %d terminated with exit status %d\n",
                   wpid, WEXITSTATUS( child_status) );
        else
            printf( "Child %d terminated abnormally\n", wpid );
            // todo:  Determine and report WHY child terminated abnormally
    }
    
    return 0;
    
} // main
