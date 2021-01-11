#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "frequency.h"


int main(int argc, char const *argv[])
{
    NODE* root=input();//take the input from the user by input() method
    //if there is no another input exept the name of the function then print in lexicographic order
    if(argc==1) 
        lexicographical_order(root);
    //else if there is an input equal to 'r' the print in a reverse lexicographic order
	else if(argc==2 && *argv[1]=='r') 
        lexicographical_order_r(root);    
    free_tree(root);
    return 0;
}
