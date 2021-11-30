/* 
 * Purpose: Create a code in C that utilizes functions and for loops.
 */
 
 #include <stdio.h>
 void triangle(int numRows);
 int choose(int n, int r);
 int fact(int num);
 
int main()
{
	// variables define and initialize here
    int numberRows;

    // scan input number from 1 to 13
    
    printf("Enter the number of rows: "); 
    scanf("%d", &numberRows);
    
    while(numberRows >=0 && numberRows <=13){
        triangle(numberRows);
        printf("Enter the number of rows: "); 
        scanf("%d", &numberRows);
    }
    
    return 0;
}

void triangle(int numRows)
{
    //defining variables
    int curRow = 0, curColumn;
    int counter;
    int curValue;
    int leftSpaces;
    
    //printing rows
    while(curRow < numRows){
        //left hand spaces
        for(leftSpaces = curRow; leftSpaces < numRows - 1; leftSpaces++)
            printf("   ");
        // print values and spaces in between
        curColumn = curRow;
        counter = curColumn;
        while(counter >= 0){
            curValue = choose(curColumn,counter);
            printf("%d",curValue);
            
            //printing spaces between
            if(curValue < 10)
                printf("     ");
            else if(curValue < 100 && curValue >10)
                printf("    ");
            else if(curValue <1000 && curValue >100)
                printf("   ");
            else
                printf("  ");
                
            //set up for next loop
            counter --;
        }
        printf("\n");
        curRow++;
    }
}

int choose(int n, int r)
{
	int result;

    result = fact(n) / fact(r) / fact(n-r);
    
    return result;

}

int fact(int num)
{
    int prod = 1;
    int cnt;
    
    for (cnt=1; cnt <= num; cnt++)
        prod *= cnt;
    
    return prod;
}
        

