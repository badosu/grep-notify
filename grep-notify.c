#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <libnotify/notify.h>

char *program_name;

void notify(char * message, NotifyUrgency urgency) {
	NotifyNotification* notification = notify_notification_new(program_name, message, "dialog-information");
	notify_notification_set_urgency(notification, urgency);
	notify_notification_show(notification, NULL);
	g_object_unref(G_OBJECT(notification));
}

void print_usage(char * program) {
	printf("Usage: %s [-k] [-u URGENCY] PATTERN [TITLE]\n\n", program);
	puts("DESCRIPTION");
	puts("  grep-notify searches for PATTERN from STDIN and sends a notification");
	puts("  whenever it's matched.  If no TITLE is given, the notification title");
	puts("  is 'Grep Notify'.\n");
	puts("OPTIONS");
	puts("  -k Keep the original program STDOUT");
	puts("  -u Set the urgency to low|normal|critical. Default: normal.");
}

int main(int argc, char **argv) {
	NotifyUrgency urgency = NOTIFY_URGENCY_NORMAL;
	int keep_stdout = false;
	size_t optind;
	for (optind = 1; optind < argc && argv[optind][0] == '-'; optind++) {
		switch (argv[optind][1]) {
		case 'k': keep_stdout = true; break;
		case 'u':
			if (argc == optind + 1) { break; }
			optind++;
			if (strcmp(argv[optind], "low") == 0) {
				urgency = NOTIFY_URGENCY_LOW;
			}
			else if (strcmp(argv[optind], "normal") == 0) {
				urgency = NOTIFY_URGENCY_NORMAL;
			}
			else if (strcmp(argv[optind], "critical") == 0) {
				urgency = NOTIFY_URGENCY_CRITICAL;
			}
			else {
				fprintf(stderr, "Invalid urgency setting, valid settings: low|normal|critical\n\n");
				print_usage(argv[0]);
				return 1;
			}
			break;
		default:
			print_usage(argv[0]);
			return 1;
		}
	}

	regex_t regex;
	char *line = NULL;
	size_t size = 0;
	int reti;

	if (!argv[optind]) {
		fprintf(stderr, "At least one argument must be provided\n\n");
		print_usage(argv[0]);
		return 1;
	}

	reti = regcomp(&regex, argv[optind], 0);
	if (reti) {
		fprintf(stderr, "Could not compile regex\n");
		return 1;
	}

	program_name = (argv[optind+1]) ? argv[optind+1] : "Grep Notify";

	notify_init(program_name);

	while (getline(&line, &size, stdin) != -1) {
		if (!regexec(&regex, line, 0, NULL, 0)) {
			if (!keep_stdout) {
				printf(line);
			}
			notify(line, urgency);
		}
		if (keep_stdout) {
			printf(line);
		}
	}

	free(line);
	notify_uninit();
	regfree(&regex);

	return 0;
}

