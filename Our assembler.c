/*Code for a 2 pass assembler
  Part 2 of the COA PROJECT
       Shreya Kaushik 15UCC036
       Anjali Mudgal 15UCC011
       Himanshi Tulsiani 15UCC016
       Ayushi Bhatia 15ucc011
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

#define alength 30

void codedisplay();
int firstpass();
void secondpass();
void viewmachcode();
void viewsymbtable();

struct opcode
{
    char code[10];
    int len;
};

struct opcode info[alength] = {
       {"R0",-1},{"R1",-1},{"R2",-1},{"R3",-1},{"R4",-1},{"R5",-1},{"R6",-1},{"R7",-1},{"R8",-1},{"R9",-1},
       {"ADD",2},{"MOV",2},{"SUB",2},{"CMP",2},{"MUL",2},{"STB",2},{"LOAD",2},
       {"JMP",3},{"JNE",3},{"JEQ",3},{"HLT",4},{"START",4}
};

int main(){
    int input,rtrn=0;
     do{
     
	 printf("\t1.Display Assembly Language Code.\n"); // displays the code you have typed.
	 printf("\t2.Display Machine Code.\n");  // displays the machine code generated on the console itself.
	 printf("\t3.Display Symbol Table.\n"); // displays only the symbol table and no machine code is generated.
	 printf("\t4.Generate Machine Code.\n"); // generates all the files symbol table file and machine code file but not displayed on console.
     printf("\t5.Exit.\n"); // to exit from file
        printf("Enter your choice:\n");
        scanf("%d",&input);
        switch(input)
        {
                     case 1 : 
                          printf("The assembly language code is:\n");
                          codedisplay();
                          break;
                     case 2 :
                          rtrn = firstpass();
                          if(rtrn == 1)
                          {
                                  printf("Error!!");
                          }
                          else
                          {
                                   secondpass();    
                                   printf("The machine language code is:\n");
                                   viewmachcode();
                          }
                          break;
                     case 3 :
                          rtrn = firstpass();
                          if(rtrn == 1)
                          {
                                  printf("Error:Cannot generate symbol table");
                          }
                          else
                          {
                                     printf("Symbol Table\n");
                                     viewsymbtable();
                          }
                          break;
                     case 4 :
                          rtrn = firstpass();
                          if(rtrn == 1)
                          {
                                  printf("Error!!");
                          }
                          else
                                     secondpass();    
                          break;
                      default :
                              printf("Wrong choice!!");     
        }            
  }while(input!=5);    
     return 0;
}



void codedisplay()
{
     int k;
     FILE *f;
     f = fopen("INPUT.txt","r");
     if(f)
     {
             while((k = getc(f))!= EOF)
             {
                      putchar(k);
             }
             fclose(f);
     }
}

int firstpass()
{
    FILE *file1,*file2;
    file1 = fopen("INPUT.txt","r"); //file containg the assembly code
    file2 = fopen("SYMBOLTABLE","w");
    char scode[20];
    int i,line=1,rtrn=0;
    char opcode[20];
    char ch;
    int length,wcount=0,temp,reg;
    fprintf(file2,"SYMBOL TABLE\n");
    while(fscanf(file1,"%s",scode)==1)      //Scanning the code
    {
                                                           //temp=1;
                                reg = 0;
                                for(i=0;i<alength;i++)   //checking opcode or label
                                {
                                                         strcpy(opcode,info[i].code);
                                                         length = strlen(opcode);
                                                         if((strcmp(scode,opcode))==0)
                                                         {
                                                                                      if(info[i].len==-1)
                                                                                                         reg = 1;
                                                                                      wcount++;
                                                                                      if(info[i].len==2)
                                                                                                        temp = 3;
                                                                                      if(info[i].len==3)
                                                                                                         temp = 2;
                                                                                      if(info[i].len==4)
                                                                                                        temp = 1;
                                                                                      break;
                                                         }
                                }
                                length = strlen(scode);
                                if(scode[length-1]==':')
                                {
                                                        
                                                        temp=1;
                                                        wcount++;
                                
                                                        fprintf(file2,"%s\t",scode);
                                                        fprintf(file2,"%d\n",line);
                                }
                                if(scode[0]=='L' && scode[length-1]!=':')
                                wcount++; 
                                
                                if(ch=fgetc(file1)=='\n')
                                {
                                                         if(wcount!=temp)
                                                         {    
                                                                         printf("Wrong opcode syntax\n %d %d %s",temp , wcount, scode);
                                                                      //   rtrn =1;
                                                         }
                                                         wcount=0;
                                                         line++;
                                }        
    }
    fclose(file1);
    fclose(file2);
    return rtrn;
}

void secondpass()
{
     FILE *file1,*file2,*file3,*file4;
     file2 = fopen("SYMBOLTABLE","r");
     file3 = fopen("MACHINECODE","w");
     file4 = fopen("INPUT.txt","r");
     char scode[20],isa[20];
     int i,line=1,rtrn=0,length=0;
     char opcode[20],binary[20];
     char ch;
     while(fscanf(file4,"%s",scode)==1)
     {
                                     file1 = fopen("ISA.txt","r");
                                     while(fscanf(file1,"%s",isa)==1)
                                     {
                                                                fscanf(file1,"%s",binary);
                                                                if(strcmp(scode,isa)==0)
                                                                {
                                                                                        fprintf(file3,"%s\t",binary);
                                                                                        break;
                                                                }       
                                     }
                                     length = strlen(scode);
                                     if(scode[length-1]==':')
                                     fprintf(file3,"\n");
                                     if(scode[0]=='L' && scode[length-1]!=':')
                                     {
                                             char garbage[30],label[20];
                                             int l;
                                             file2 = fopen("SYMBOLTABLE","r");
                                             fscanf(file2,"%s",garbage);
                                             fscanf(file2,"%s",garbage);
                                             while(fscanf(file2,"%s",label)==1)
                                             {
                                                                               fscanf(file2,"%d",&l);
                                                                               switch(l)
                                                                               {
                                                                                        case 0: 
                                                                                             fprintf(file3,"0000\n");
                                                                                             break;
                                                                                        case 1: 
                                                                                             fprintf(file3,"0001\n");
                                                                                             break;
                                                                                        case 2: 
                                                                                             fprintf(file3,"0010\n");
                                                                                             break;
                                                                                        case 3: 
                                                                                             fprintf(file3,"0011\n");
                                                                                             break;
                                                                                        case 4: 
                                                                                             fprintf(file3,"0100\n");
                                                                                             break;
                                                                                        case 5: 
                                                                                             fprintf(file3,"0101\n");
                                                                                             break;
                                                                                        case 6: 
                                                                                             fprintf(file3,"0110\n");
                                                                                             break;
                                                                                        case 7: 
                                                                                             fprintf(file3,"0111\n");
                                                                                             break;
                                                                                        case 8: 
                                                                                             fprintf(file3,"1000\n");
                                                                                             break;
                                                                                        case 9: 
                                                                                             fprintf(file3,"1001\n");
                                                                                             break;
                                                                                        case 10: 
                                                                                             fprintf(file3,"1010\n");
                                                                                             break;
                                                                                        case 11: 
                                                                                             fprintf(file3,"1011\n");
                                                                                             break;
                                                                                        case 12: 
                                                                                             fprintf(file3,"1100\n");
                                                                                             break;
                                                                                        case 13: 
                                                                                             fprintf(file3,"1101\n");
                                                                                             break;
                                                                                        case 14: 
                                                                                             fprintf(file3,"1110\n");
                                                                                             break;
                                                                                        case 15: 
                                                                                             fprintf(file3,"1111\n");
                                                                                             break;
							
                                                                               }
                                             }
                                             fclose(file2);         
                                     }
                                     if(ch=fgetc(file1)=='\n')
                                     {
                                                              line++;
                                                              fprintf(file3,"\n");
                                     }
                                     fclose(file1);
     }
     fclose(file3);
     fclose(file4);
}

void viewmachcode()
{
     int k;
	FILE *f;
	f=fopen("MACHINECODE", "r");
	if(f) 
	{
	    while( (k = getc(f))!= EOF )
	    {    
	    	putchar(k);
	    }
    	fclose(f);
	}	
}

void viewsymbtable()
{
     int k;
	FILE *f;
	f=fopen("SYMBOLTABLE", "r");
	if(f) 
	{
	    while( (k = getc(f))!= EOF )
	    {    
	    	putchar(k);
	    }
    	fclose(f);
	}	
}
