#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "a.txt"; 
    char line[256];  

    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
   }
    fclose(file);

    return EXIT_SUCCESS;
}
