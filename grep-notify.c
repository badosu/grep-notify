#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <libnotify/notify.h>

char *program_name;

void notify(char * message) {
	NotifyNotification* notification = notify_notification_new(program_name, message, "dialog-information");
	notify_notification_show(notification, NULL);
	g_object_unref(G_OBJECT(notification));
}

int main(int argc, char **argv) {
	regex_t regex;
	char *line = NULL;
	size_t size = 0;
	int reti;

	if (argc < 2) {
		fprintf(stderr, "At least one argument must be provided\n");
		return 1;
	}

	reti = regcomp(&regex, argv[1], 0);
	if (reti) {
		fprintf(stderr, "Could not compile regex\n");
		return 1;
	}

	program_name = (argc > 2) ? argv[2] : "Grep Notify";

	notify_init(program_name);

	while (getline(&line, &size, stdin) != -1) {
		if (!regexec(&regex, line, 0, NULL, 0)) {
			fprintf(stdout, line);
			notify(line);
		}
	}

	free(line);
	notify_uninit();
	regfree(&regex);

	return 0;
}

