#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

void usage()
{
    printf("ascii print ASCII table\n\n");
    printf("Usage:\n");
    printf("  ascii [OPTION]...\n\n");

    printf("\nOptions:\n");
    printf("  -h, --help               show this help, then exit\n");
    printf("  -c, --control            show control characters\n");
    printf("  -p, --printable          show printable characters\n");
    printf("  -e, --extended           show extended characters\n");
    printf("  -a, --all                show all characters\n");
}

struct options {
    bool control;
    bool printable;
    bool extended;
};

static void parse_options(int argc, char *argv[], struct options *opts) 
{
    int ch;
    FILE *fd;

    /* options descriptor */
    static struct option longopts[] = {
        { "help",        no_argument,       NULL, 'h' },
        { "control",     no_argument,       NULL, 'c' },
        { "printable",   no_argument,       NULL, 'p' },
        { "extended",    no_argument,       NULL, 'e' },
        { "all",         no_argument,       NULL, 'a' },
        { NULL,          0,                 NULL,  0  }
    };

    while ((ch = getopt_long(argc, argv, "hcpea", longopts, NULL)) != -1) {
        switch (ch) {
            case 'c':
                opts->control = true;
                break;
            case 'p':
                opts->printable = true;
                break;
            case 'e':
                opts->extended = true;
                break;
            case 'a':
                opts->control = true;
                opts->printable = true;
                opts->extended = true;
                break;
            case 'h':
                usage();
                exit(0);
                break;
            default:
                fprintf(stderr, "Try: ascii --help\n");
                exit(1);
        }
    }
    argc -= optind;
    argv += optind;
}

int main(int argc, char *argv[]) 
{
    struct options opts = {0};
    parse_options(argc, argv, &opts);

    return 0;
}

