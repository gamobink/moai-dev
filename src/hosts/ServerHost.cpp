#include <aku/AKU.h>
#include <moaiext-server/AKU-server.h>

#ifdef _WIN32
	#include <windows.h>
	#define sleep(x) Sleep((x) * 1000)
	#define WINCDECL __cdecl
#endif

#include <signal.h>

static int sExitFlag = 0;

//----------------------------------------------------------------//
static void WINCDECL signal_handler ( int sig_num ) {
  sExitFlag = sig_num;
}

//----------------------------------------------------------------//
static void die ( const char *fmt, ... ) {
  va_list ap;
  char msg [ 200 ];

  va_start ( ap, fmt );
  vsnprintf ( msg, sizeof ( msg ), fmt, ap );
  va_end ( ap );

  exit ( EXIT_FAILURE );
}

//----------------------------------------------------------------//
int main ( int argc, char *argv []) {

	AKUCreateContext ();
	AKUServerInit ();

	// Setup signal handler: quit on Ctrl-C
	signal ( SIGTERM, signal_handler );
	signal ( SIGINT, signal_handler );
	
	AKUSetArgv ( argv );
	
	for ( int i = 1; i < argc; ++i ) {
		char* arg = argv [ i ];
		if ( strcmp( arg, "-s" ) == 0 && ++i < argc ) {
			AKURunString ( argv [ i ]);
		}
		else {
			AKURunScript ( arg );
		}
	}
	
	while ( sExitFlag == 0 ) {
		sleep ( 1 );
	}
	printf ( "Exiting on signal %d, waiting for all threads to finish...", sExitFlag );
	fflush ( stdout );
	AKUFinalize ();
	printf ( "%s", " done.\n" );

	return EXIT_SUCCESS;
}
