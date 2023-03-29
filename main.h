//main.h

/* parsed from brd file, information about the element */
struct element
{
    char name[20];
    char library[50];
    char package[20];
    char value[20];
    char x_pos[10];
    char y_pos[10];
    char rot[10];
};

/* yet to be implemented, use dummy values for now */
struct spool
{

};