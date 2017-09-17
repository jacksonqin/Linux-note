#include <unistd.h>
char get_opt_version[] = "short version option";
/*
 *usage	: command [-i] [-u username] [-z filename] when options
 		 will be passe "iu:z:"
 * returns: the next option character,
 * 		 or -1 when all options have been processed
 */
int getopt(int argc, char * const argv[], const char *options);

extern int optind, opterr, optopt;
extern char * optarg;
/* optarg: if an option takes an arguement, getopt sets optarg to point to
* the option's arguement string when an option is processed.
*/

//options : "ab:c:lwf:g::"
//
static void parse_cmd_line(int argc, char *argv[])
{
	int c;
	int bs;
	bool flag, write_lat_log, write_bw_log;
	char *file;
	while( (c = getopt(argc, argv, options)) != EOF) {
		switch(c) {
		case 'a':
			break;
		case 'b':
			bs = atoi(optarg);
			break;
		case 'c':
			flag = !!(optarg);
			break;
		case 'l':
			write_lat_log = 1;
			break;
		case 'w':
			write_bw_log = 1;
			break;
		case 'f':
			file =strdup(optarg);
			break;
		case 'v':
			printf("%s\n", get_opt_version);
			break;
		default: /* ''?'' */
			fprintf(stderr, "usage: %s [-b bs] [-c] [-l] [-w] [-f filename] [-v]\n", argv[0]);
			break;
		}

	}
}

#include <getopt.h>  
int getopt_long (int ___argc, char *const *___argv,    
            const char *__shortopts,    
                const struct option *__longopts, int *__longind);    
int getopt_long_only (int ___argc, char *const *___argv,    
                 const char *__shortopts,    
                     const struct option *__longopts, int *__longind);  
//argc, argv passed from main
//shortopts: short option string
//longopts: struct option array, used to store long options parameter
//longind: return index of long opts structure array.
struct option    
{    
  const char *name;
  int has_arg;  
  int *flag;    
  int val;    
};  
/*
*name: is the name of the long option    
*has_arg: no_argument  if the option does not take an argument
		required_argument if the option requires an argument
		optional_argument if the option takes an optional argument.
 flag and val: 
 	If flag is NULL, then getopt_long() returns val
*/
// ***** Note********
/*
* how to bind short options to long options
  (1) longoptions is val
  (2) so just let shortoption = val, and flag=NULL
*/
#include <getopt.h> //getopt_long
char optstr[1024];
static void fill_optstring(char *optstr, struct option *l_opts)
{
	int i, j;
	i = j = 0;
	while(l_opts[i].name ){
		optstr[j++] =l_opts.val;
		if(l_opts[i].has_arg == require_argement)
			optstr[j++] = ':'
		else if(l_opts[i].has_arg ==optional_argement){
			optstr[j++] = ':';
			optstr[j++] = ':';
		}
		i++;
	}
	optstr[j] = '\0';
}

static void parse_cmd_line(int argc, char *argv[])
{
	int c;
	int index;
	struct option opts[]{
		{
			.name="username", 
			.has_arg = required_argument,
			.flag = NULL, 
			.val = 'u'
		},
		{
			.name="version", 
			.has_arg = no_argument,
			.flag = NULL, 
			.val = 'v'
		},
		{
			.name = NULL
		}
	};
//	const char *optstring = "n:v";
	fill_optstring(optstr, opts);
	
	while( (c = getopt_long_only(argc, argv, optstr, opts, &index)) != -1) {
		switch(c) {
		case 'u'://-n or --username
			printf("username:%s", optarg);
			break;
		case 'v':// -v or --version
			printf("version is 1.0.0\n");
			break;
		default: /* ''?'' */
			fprintf(stderr, "usage: %s [-u username] [-v]\n or %s [--username username] [--version]", argv[0]);
			break;
		}
	}
}

