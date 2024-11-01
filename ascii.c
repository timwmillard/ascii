#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>

void usage() {
    printf("ascii - print ASCII table\n\n");
    printf("Usage:\n");
    printf("  ascii [OPTION]...\n\n");

    printf("\nOptions:\n");
    printf("  -h, --help               Show this help, then exit\n");
    printf("  -c, --control            Show control characters (ASCII 0-31)\n");
    printf("  -p, --printable          Show printable characters (ASCII 32-126)\n");
    printf("  -e, --extended           Show extended characters (ASCII 127-255)\n");
    printf("  -a, --all                Show all characters\n");
}

struct options {
    bool control;
    bool printable;
    bool extended;
};

static void parse_options(int argc, char *argv[], struct options *opts) {
    int ch;
    static struct option longopts[] = {
        { "help",      no_argument, NULL, 'h' },
        { "control",   no_argument, NULL, 'c' },
        { "printable", no_argument, NULL, 'p' },
        { "extended",  no_argument, NULL, 'e' },
        { "all",       no_argument, NULL, 'a' },
        { NULL,        0,           NULL,  0  }
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
            default:
                fprintf(stderr, "Try: ascii --help\n");
                exit(1);
        }
    }
}

// Function to print control characters (ASCII 0-31)
void print_control_characters() {
    printf("Control Characters (ASCII 0-31):\n");
    for (int i = 0; i < 32; i++) {
        printf("%3d: ^%c\n", i, i + 64); // Showing control characters as ^ notation
    }
    printf("\n");
}

// Function to print printable characters (ASCII 32-126)
void print_printable_characters() {
    printf("Printable Characters (ASCII 32-126):\n");
    for (int i = 32; i < 127; i++) {
        printf("%3d: %c\n", i, i);
    }
    printf("\n");
}

// Function to print extended characters (ASCII 127-255)
void print_extended_characters() {
    printf("Extended Characters (ASCII 127-255):\n");
    for (int i = 127; i < 256; i++) {
        printf("%3d: %c\n", i, (unsigned char)i);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    struct options opts = {0};
    parse_options(argc, argv, &opts);

    // If no option is selected, show the usage message and exit
    if (!opts.control && !opts.printable && !opts.extended) {
        usage();
        return 1;
    }

    // Print based on selected options
    if (opts.control) {
        print_control_characters();
    }
    if (opts.printable) {
        print_printable_characters();
    }
    if (opts.extended) {
        print_extended_characters();
    }

    return 0;
}