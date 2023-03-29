#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/* Definitions */

#define TRUE 1
#define FALSE 0
#define _POSIX_C_SOURCE 200809L

/* Global variables */

struct elements
{
    char name[20];
    char library[50];
    char package[20];
    char value[20];
    char x_pos[10];
    char y_pos[10];
    char rot[10];
} elements_array[1000], shortest_elements_array[1000];

int element_size = 0;

/* Functions */

/* Parses through current directory for .brd extensions */
int parse_ext(const struct dirent *dir)
{
    if (!dir)
        return 0;

    if (dir->d_type == DT_REG)
    { /* only deal with regular file */
        const char *ext = strrchr(dir->d_name, '.');
        if ((!ext) || (ext == dir->d_name))
            return 0;
        else
        {
            if (strcmp(ext, ".brd") == 0)
                return 1;
        }
    }

    return 0;
}

/* Reads file(s) and populates elements struct array */
void readFile(char *fileString)
{
    int num;
    FILE *fptr;
    fptr = fopen(fileString, "r");

    if (fptr == NULL)
    {
        printf("Error in reading file");
        exit(1);
    }

    rewind(fptr);
    char line[200];
    while (fgets(line, sizeof line, fptr) != NULL)
    {
        char *dummy;
        dummy = strstr(line, "element name");
        if (dummy != NULL)
        {
            struct elements new_element;
            elements_array[element_size] = new_element;
            element_size++;
            char *token = strtok(line, " ");
            while (token != NULL)
            {
                if (strstr(token, "name"))
                {
                    char *component = strchr(token, '\"');
                    int len = strlen(component);
                    int i;
                    for (i = 1; i < len; i++)
                    {
                        new_element.name[i - 1] = component[i];
                    }
                    new_element.name[i] = '\0';
                }
                else if (strstr(token, "library"))
                {
                    char *component = strchr(token, '\"');
                    int len = strlen(component);
                    int i;
                    for (i = 1; i < len; i++)
                    {
                        new_element.library[i - 1] = component[i];
                    }
                    new_element.library[i] = '\0';
                }
                else if (strstr(token, "package"))
                {
                    char *component = strchr(token, '\"');
                    int len = strlen(component);
                    int i;
                    for (i = 1; i < len; i++)
                    {
                        new_element.package[i - 1] = component[i];
                    }
                    new_element.package[i] = '\0';
                }
                else if (strstr(token, "value"))
                {
                    char *component = strchr(token, '\"');
                    int len = strlen(component);
                    int i;
                    for (i = 1; i < len; i++)
                    {
                        new_element.value[i - 1] = component[i];
                    }
                    new_element.value[i] = '\0';
                }
                else if (strstr(token, "x"))
                {
                    char *component = strchr(token, '\"');
                    int len = strlen(component);
                    int i;
                    for (i = 1; i < len; i++)
                    {
                        new_element.x_pos[i - 1] = component[i];
                    }
                    new_element.x_pos[i] = '\0';
                }
                else if (strstr(token, "y"))
                {
                    char *component = strchr(token, '\"');
                    int len = strlen(component);
                    int i;
                    for (i = 1; i < len; i++)
                    {
                        new_element.y_pos[i - 1] = component[i];
                    }
                    new_element.y_pos[i] = '\0';
                }
                if (strstr(token, "rot"))
                {
                    char *component = strchr(token, '\"');
                    int len = strlen(component);
                    int i;
                    for (i = 1; i < len; i++)
                    {
                        new_element.rot[i - 1] = component[i];
                    }
                    new_element.rot[i] = '\0';
                }
                else
                {
                    char rotate0[3] = "R0";
                    int i;
                    for (i = 0; i < 3; i++)
                    {
                        new_element.rot[i] = rotate0[i];
                    }
                }
                token = strtok(NULL, " ");
            }
        }
    }
    fclose(fptr);
}

/* writes the elements in the order they appear in shortest elements array 
(we will have to consider spool elements as well later) */
void writeFile(char *fileString)
{
    int num;
    FILE *fptr;
    char prepend[100] = "SD for ";
    char *outName = strcat(prepend, fileString);

    fptr = fopen(prepend, "w");

    if (fptr == NULL)
    {
        printf("Error in writing file");
        exit(1);
    }

    int i;
    for (i = 0; i < element_size; i++)
    {
        fprintf(fptr, elements_array[i].name);
        fprintf(fptr, " ");
        fprintf(fptr, elements_array[i].library);
        fprintf(fptr, " ");
        fprintf(fptr, elements_array[i].package);
        fprintf(fptr, " ");
        fprintf(fptr, elements_array[i].value);
        fprintf(fptr, " ");
        fprintf(fptr, elements_array[i].x_pos);
        fprintf(fptr, " ");
        fprintf(fptr, elements_array[i].y_pos);
        fprintf(fptr, " ");
        fprintf(fptr, elements_array[i].rot);
        fprintf(fptr, "\n");
    }

    fclose(fptr);
}

/* Write shortest distance algorithm here*/
void shortest_distance() {

}

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, parse_ext, alphasort);
    if (n < 0)
    {
        printf("Error in scanning directory");
        exit(1);
    }
    else
    {
        while (n--)
        {
            printf("%s\n", namelist[n]->d_name);
            readFile(namelist[n]->d_name);
            writeFile(namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }

    return 0;
}