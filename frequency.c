#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "frequency.h"
int max_word=0;
NODE
{
    char data;
    int counter;
    struct node *children[ALPHABET]; 
};
//this method return a new node after init
NODE* make_node(){
    int i;
    NODE* ans = (NODE*) calloc(1,sizeof(NODE));
    if(!ans){//problem with memory allocation
    	return ans;
    
    }
    for(i=0;i<ALPHABET;i++){//init all the childrens into NULL
        ans->children[i]=NULL;
    }
    ans->counter=0;    
    return ans;
}


//this method get a single char and puts it in his position
NODE* insert_char(NODE* pointer, char data){
    NODE* child=pointer;
    //if the node never got visited
    //then init a new node and connect it to the graph
    //else return a pointer to the address of the node
    if(pointer->children[CHARTOINDEX(data)]==NULL){
        child=make_node();
        if(!child){//problem with memory allocation
        	return child;
        
        }
        child->data=data;
        pointer->children[CHARTOINDEX(data)]=child;
        
    }
    return pointer->children[CHARTOINDEX(data)];
}

//this method get a word and puts it into the graph
void insert_word(NODE* root, char* word){
    int size=strlen(word);
    //we save the biggest size of the word for the prints method
    if(max_word<size){
        max_word=size;
    }
    int i;
    NODE* pointer=root;

    //run on each single char in the graph
    //put any char into the graph using insert_char() method
    for(i=0; i< size;i++){
        pointer=insert_char(pointer,word[i]);
         if(!pointer){
    		free_tree(root);
    		exit(1);
    }
    }
    pointer->counter++;//in the end of the word make the counter++ 
}


//this method take a word and proccess it into a proper word with only lower case
void proper_word(NODE* root,char* word){
    int i;
    int length=strlen(word);
    int index_proper=0;
    for(i=0;i<length;i++){
        if(word[i]<='z' && word[i] >= 'a' ){//if lower case
            word[index_proper] = word[i];
  	  	    index_proper++;
        }
        else if (word[i]<='Z' && word[i] >= 'A' ){//if upper case then -> lower case
            word[index_proper] = word[i]+LOWERCASE;
  	  	    index_proper++;
        }
    }
    word[index_proper]='\0';// make the word a string
    if(index_proper!=0)//if the word does not contains alphbet at all then dont insert it to the TRIE
        insert_word(root,word);

}

//take a block of data and process it into words
void proccesing(NODE* root,char* buffer){
    int size_of_input=strlen(buffer);
    int i,start;
    boolean flag=FALSE;
    char* temp;
    for(i=0; i<size_of_input;i++){
      start=i;
      while(i<size_of_input&&buffer[i]!=' '&&buffer[i]!='\n'&&buffer[i]!='\t'){//count the size of the word
          i++;
          flag=TRUE;
      }
      if(flag==TRUE){//if there is a word

        temp = (char*) calloc((i-start+1),sizeof(char));//make a memory in the size of the found word
        if(!temp){
        	free_tree(root);
        	exit(1);
        }
        strncpy(temp,&buffer[start],i-start);//make a copy of the word
        temp[i-start]='\0';//make the word a string
        proper_word(root,temp);//send the found word to proper_word() method
        free(temp);//free temp after use
        flag=FALSE;
    }
    }
    
} 



////////////////////////prints//////////////////////////////////////




//this method prints the TRIE in opposite lexicographical order
//this mehod using lexicographical_order_r_help() method

void lexicographical_order_r(NODE* pointer){

    char* str=(char*) calloc((max_word+1),(sizeof(char)));//make place in the size of the greater word
    
    if(!str){
        free_tree(pointer);
        exit(1);
     }
    lexicographical_order_r_help(pointer,str,0);
    free(str);//free str after use
}




//this method is a recursive method
//enter recursively to the tree starting at the right corner of the tree
//every entreance, add the letter of the node into str
//check if the counter is not 0, if so then print the word with its counter of words
//index is the end index of the word in *str

void lexicographical_order_r_help(NODE* pointer,char* str,int index){

    for(int i=ALPHABET-1;i>=0;i--){//run all over the node childs
        if(pointer->children[i]!=NULL){//every child if not null then add him to str and enter recursively into him
            str[index]=pointer->children[i]->data;
            index++;
            str[index]='\0';//make a string from the word
            lexicographical_order_r_help(pointer->children[i],str,index);//recursive call
            index--;//after the recursive call done, tell index to be level -1
        }
          
}
    if(pointer->counter!=0){////if this position is the of a some word -> print the word with its counter
        printf("%s %d\n",str,pointer->counter);
    }
    if(index-1>=0)
    	str[index-1]='\0';//after printing there is no need in this letter


}



//this method prints the TRIE in a lexicographical order
//this mehod using lexicographical_order_r_help() method

void lexicographical_order(NODE* pointer){
    char* str=(char*) calloc((max_word+1),(sizeof(char)));
    if(!str){
        free_tree(pointer);
        exit(1);
     }
    lexicographical_order_help(pointer,str,0);
    free(str);
}





//this method is a recursive method
//enter recursively to the tree starting at the left corner of the tree
//check if the counter is not 0, if so then print the word with its counter of words
//every entreance, add the letter of the node into str
//index is the end index of the word in *str

void lexicographical_order_help(NODE* pointer,char* str,int index){
    
    if(pointer->counter!=0){//if this position is the of a some word -> print the word with its counter
        printf("%s %d\n",str,pointer->counter);
    }
   
    for(int i=0;i<ALPHABET;i++){//run all over the node childs
        if(pointer->children[i]!=NULL){//every child if not null then add him to str and enter recursively into him
            str[index]=pointer->children[i]->data;
            index++;
            str[index]='\0';//make the word a string
            lexicographical_order_help(pointer->children[i],str,index);//recursively call
            index--;//after the recursive call done, tell index to be level -1
        }
    }
    if(index-1>=0)
    	str[index-1]='\0';//after printing there is no need in this letter

}



//this method free the memory of the tree by recursive call
void free_tree(NODE* pointer){
	int i;
    for(i=ALPHABET-1;i>=0;i--){
        if(pointer->children[i]!=NULL)
            free_tree(pointer->children[i]);
    }
    free(pointer);
}

//take input from stdin and send the input to proccesing() method
NODE* input(){

    char* buffer=(char*) calloc(1,sizeof(char));//make a space in of size of char
    if(!buffer){
        exit(1);
     }
    char c;
    int i=0,size=2;//size of the buffer +1 for 0 in the end
    while((c = fgetc(stdin))!= EOF) {
   	 	buffer = (char*)realloc(buffer,  size + sizeof(char));//make realloc
   	 	if(!buffer){//problem with memory allocation
        	exit(1);}
   	 	buffer[i] = c;//enter the input into the array
  	  	i++;
  	  	size++;
  	} 
  	buffer[i]='\0';	
        NODE* root=(NODE*) calloc(1,sizeof(NODE));//memory for the root of the tree   
    if(!root){//problem with memory allocation
    	free(buffer);
        exit(1);
        }
    proccesing(root,buffer);
    free(buffer);//free after use
    return root;
}


