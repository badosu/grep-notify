#include <pcre.h>
#include <stdio.h>
#include <libnotify/notify.h>

#define MATCH_COUNT 30    /* should be a multiple of 3 */

pcre *regex;
const char *error;
int erroffset;
char *program_name;

int matches[MATCH_COUNT];

int main(int argc, char **argv) {
	char *line = NULL;
	int line_length;
	size_t size;

	regex = pcre_compile(
		argv[1],              /* the pattern */
		0,                    /* default options */
		&error,               /* for error message */
		&erroffset,           /* for error offset */
		NULL);                /* use default character tables */

	program_name = (argc > 2) ? argv[2] : "Grep Notify";

	notify_init(program_name);

	while ((line_length = getline(&line, &size, stdin)) != -1) {
		if (line_match(line, line_length) > -1) {
			notify(line);
		}

		printf("%s", line);
	}

	notify_uninit();

	pcre_free(regex);

	return 0;
}

void notify(message) {
	NotifyNotification* Hello = notify_notification_new(program_name, message, "dialog-information");
	notify_notification_show(Hello, NULL);
	g_object_unref(G_OBJECT(Hello));
}

int line_match(line, line_length) {
	pcre_exec(
	  regex,             /* the compiled pattern */
	  NULL,              /* no extra data ‐ we didn’t study the pattern */
	  line,              /* the subject string */
	  line_length,       /* the length of the subject */
	  0,                 /* start at offset 0 in the subject */
	  0,                 /* default options */
	  matches,           /* output vector for substring information */
	  MATCH_COUNT);      /* number of elements in the output vector */
}
