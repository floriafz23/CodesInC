/* 
 * Purpose: Create a code in C that utilizes for loops to create an image.
 */
 
 #include <stdio.h>

int main()
{
	// variables define and initialize here
    int triangleRows;
    int topSpaces1, topSpaces2;
    int rowNumber, leftNumber, middleNumber;
    int leftSpaces, middleSpaces; 
    int bottomStars;

    // scan input number from 1 to 20
    
    printf("Enter the number of rows in the triangle: "); 
    scanf("%d", &triangleRows);
   
    //print top row
    for(topSpaces1 =1; topSpaces1 < triangleRows; topSpaces1++)
        printf(" ");
    printf("*");
    for(topSpaces1 =1; topSpaces2 < triangleRows; topSpaces2++)
        printf(" ");
    printf("\n");
    
    //print middle rows
    rowNumber = 2;
    leftNumber = 2;
    middleNumber = 1;
    while(rowNumber < triangleRows){
        
        // print left spaces
        for(leftSpaces = leftNumber; leftSpaces < triangleRows; leftSpaces++)
            printf(" ");
       
        //print first asterisk
        printf("*");
        
        // print middle spaces
        for(middleSpaces = middleNumber; middleSpaces <= 2 * rowNumber - 3; middleSpaces++)
            printf(" ");
        
        //print second asterisk and enter new line
        printf("*");
        
        printf("\n");
        
        // conditions for next loop
            
        rowNumber++;
        leftNumber++;
        
    }
    
    //print bottom row of stars
    if (triangleRows != 1){
        for(bottomStars == triangleRows; bottomStars < 2*triangleRows - 1; bottomStars++)
            printf("*");
        printf("\n");
    }
    
    
	return 0;
}


