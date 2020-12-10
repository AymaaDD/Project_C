
#include "edid.h"

void EdidPrint();
int ReadNameFile (char **arr);


int main(void)
{
    char *ar;
    int result;

    printf(" Enter direction file Edid!\n");

    result = ReadNameFile(&ar);

    if (0 == result ) {
        FILE *input = NULL;
        input = fopen(ar, "rb");
        EdidPrint(input); 
        
    } else if (1 == result ) {
        printf(" File is not EDID!\n");
    } else if (2 == result ) {
        printf(" Not Direction !\n");
    } else if (3 == result) {
        printf(" Error (No File or No Direction!) \n");
    }   

    free(ar);



    return 0;
    

}




int ReadNameFile (char **arr) {

    char *s = NULL;
    size_t n;
    int error = 0;
    char *result = malloc(5);
    getline(&s,&n,stdin);
   
    int k = 1;
    for(int i = 0; i < (int)n; i++) {
        if (*(s+i) != 0) {
            k++;
        } else if ( (*(s+i) = 0) || (*(s+i) = ' ') )  {
            break;
        }
    }
    
    if (k >= 5) {    
        result = (char *) realloc (result,k-1);
        for(int i = 0; i < k; i++) {
            result[i] = *(s+i);
            if (i == (k-2)) {
                result[i] = '\0';
            }
        }

        if ( (result[k-3] != (char)'D') && (result[k-3] != (char)'d') ) {
            error = 1;
        }
        if ((result[k-4] != (char)'I') && (result[k-4] != (char)'i')) {
            error = 1;
        }
        if ((result[k-5] != (char)'D') && (result[k-5] != (char)'d')) {
            error = 1;
        }
        if ((result[k-6] != (char)'E') && (result[k-6] != (char)'e')) {
            error = 1;
        }
        if (result[k-7] != (char)'.') {
            error = 1;
        }
        if (result[0] != (char)'/') {
             error = 2;
        }

        *arr = result;
    } else {
        error = 3;
        *arr = result;
    }
 
    free(s);

    return error;
}


