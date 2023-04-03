//shortest_path.h

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
typedef struct element element;

int getDistance(int x_pos,int y_pos);

double distance(element *a, element *b);

void swap_elements(element *a, element *b) ;

void permute_elements(element *arr[], int start, int end, double *min_distance, element *min_path[], double curr_distance, element *curr_path[]);


//sorts workList based on shortest possible path between all elements.
//returns nothing. Sorts array given to it. 
void shortest_distance(element *arr[], int n);
