// Bintie Kayode and Brent Matthew Ortizo

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    int option;
    int frames = 0;
    FILE *input_file;
    char *page = NULL;  
    char *tlb = NULL;

    // Define long options
    static struct option long_options[] = {
        {"frames", required_argument, 0, 'f'},
        {"page", required_argument, 0, 'p'},
        {"tlb", required_argument, 0, 't'},
        {0, 0, 0, 0}};

    while ((option = getopt_long(argc, argv, "t:p:f:", long_options, NULL)) != -1)
    {
        switch (option)
        {
        case 'f':
            //Validate that frames is a positive integer, and a power of 2
            frames = atoi(optarg);
            if(frames <= 0 || (frames & (frames - 1)) != 0) {
                fprintf(stderr, "Error: invalid frame count. Must be a positive power of 2.\n");
                return 1;
            }
            break;
        case 'p':
            page = optarg;
            if(strcmp(page, "fifo") != 0 && strcmp(page, "random") != 0 && strcmp(page, "lru") != 0) {
                fprintf(stderr, "Error: invalid Page replacement policy. Valid options are: fifo, random, and lru\n");
                return 1;
            }
            break;
        case 't':
            tlb = optarg;
            if(strcmp(tlb, "fifo") != 0 && strcmp(tlb, "random") != 0) {
                fprintf(stderr, "Error: invalid TLB replacement policy. Valid options are: fifo, random\n");
                return 1;
            }
            break;
        case '?':
            // getopt_long already printed an error message
            break;
        default:
            abort();
        }
    }

    if (optind > 1)
    {
        fprintf(stderr, "Too many arguments: %s\n Only one non-option argument allowed", argv[optind]);
        return 1;
    }
    else
    {
        char *filename = argv[optind];
        input_file = fopen(filename, "r");
        if (input_file == NULL)
        {
            fprintf(stderr, "Error: could not open input file %s\n", filename);
            return 1;
        }
    }

    return 0;
}
