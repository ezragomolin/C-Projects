/*
Program to implement a scientific calculator
***************************************************************
* Author             Dept .                Date        Notes
***************************************************************
* Ezra Gomolin Software Engineering  . NOV 3 2020 Initial version (handling input errors).
* Ezra Gomolin Software Engineering  . NOV 4 2020 Added the addition implementation.
*/

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[]){

if(argc !=4){
printf("Error: invalid number of arguments!\n");
printf("scalc <operand1> <operater> <operand2>\n");
return 1;
}

if(argv[2][0] != '+' || argv[2][1] != '\0'){
printf("Error: operator can only be + !\n");
return 1;
}

for(int i = 0; argv[1][i] != '\0'; i++){
if (argv[1][i] !='0' && argv[1][i] !='1' && argv[1][i] !='2' && argv[1][i] !='3' && argv[1][i] !='4' && argv[1][i] !='5' && argv[1][i] !='6'&& argv[1][i] !='7' && argv[1][i] !='8' && argv[1][i] !='9'){
printf("Error!! operand can only be positive integers\n");
return 1;
}

}
for(int i = 0; argv[3][i] != '\0'; i++){
if (argv[3][i] !='0' && argv[3][i] !='1' && argv[3][i] !='2' && argv[3][i] !='3' && argv[3][i] !='4' && argv[3][i] !='5' && argv[3][i] !='6'&& argv[3][i] !='7' && argv[3][i] !='8' && argv[3][i] !='9'){
printf("Error!! operand can only be positive integers\n");
return 1;
}
}

int strnlengtharg1 = 0;
for(; argv[1][strnlengtharg1] != '\0'; strnlengtharg1++){
}
strnlengtharg1 = strnlengtharg1 - 1;

int strnlengtharg3 = 0;
for(; argv[3][strnlengtharg3] != '\0'; strnlengtharg3++){
}
strnlengtharg3 = strnlengtharg3 - 1;



int finalarraysize=strnlengtharg1+1;
int offset=0;
int stringlengthcmp=strnlengtharg1;
if(strnlengtharg3 > strnlengtharg1){
offset = strnlengtharg3-strnlengtharg1;
stringlengthcmp=strnlengtharg1;
finalarraysize=strnlengtharg3+1;
}
if (strnlengtharg1 > strnlengtharg3){
offset = strnlengtharg1 - strnlengtharg3;
stringlengthcmp=strnlengtharg3;
}


int finalresult[finalarraysize];


int arraycount=finalarraysize;
int carry=0;
int x=0;
int y=0;
int result=0;
int temp=0;
int j = stringlengthcmp;
int q = offset;
while(j>0 || j==0){

if(strnlengtharg1>strnlengtharg3){
x = argv[1][j+q];
y = argv[3][j];
}

else if(strnlengtharg3>strnlengtharg1){
x = argv[1][j];
y = argv[3][j+q];
}

else{
x=argv[1][j];
y=argv[3][j];
}

result = carry + x + y - 96;
temp = result - 10;

if(temp < 0){
carry = 0;
}
if (temp >= 0){
carry = 1;
result = temp;
}
finalresult[arraycount]=result;
arraycount--;
//printf("%d", result);
j--;
}

int t=offset-1;
int offsetx=0;
int offsetresult=0;
int offsettemp=0;
if(strnlengtharg1>strnlengtharg3){
while(t>0 || t==0){
offsetx = argv[1][t];
offsetresult= offsetx + carry - 48;
offsettemp = offsetresult - 10;
if (offsettemp < 0){
carry = 0;
}

if(offsettemp >= 0){
carry = 1;
offsetresult= offsettemp;
}
//printf("%d", offsetresult);
finalresult[arraycount]=offsetresult;
arraycount--;
t--;
}
}


int z=offset-1;
int offsety=0;
int offsetyresult=0;
int offsetytemp=0;
if(strnlengtharg3>strnlengtharg1){
while(z>0 || z==0){
offsety = argv[3][z];
offsetyresult= offsety + carry - 48;
offsetytemp = offsetyresult - 10;
if (offsetytemp < 0){
carry = 0;
}
if(offsetytemp >= 0){
carry = 1;
offsetyresult= offsetytemp;
}
//printf("%d", offsetyresult);
z--;
finalresult[arraycount]=offsetyresult;
arraycount--;
}
}

if(carry == 1){
finalresult[arraycount]=carry;
for(int k=0; k<= finalarraysize; k++){
printf("%d", finalresult[k]);
}
}

else if(carry == 0){
for(int k=1; k<= finalarraysize; k++){
printf("%d", finalresult[k]);
}

}

printf("\n");


}















