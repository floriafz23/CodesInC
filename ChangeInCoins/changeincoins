/* 
 * Purpose: Create a code in C that utilizes nested loops and relational clauses to determine amounts of change.
 */
 
 #include <stdio.h>
#define Quarter 25
#define Dime 10
#define Nickel 5

int main()
{
	// variables define and initialize here
    int inputNumber;
    int afterQuarters, afterDimes, afterNickels;
    int numQuarters, numDimes, numNickels, numCents;

    // scan input number
    
    printf("Please give an amount in cents less than 100: "); 
    scanf("%d", &inputNumber);
    
    //enter loop and stay while number is valid
    
    while(inputNumber < 100 && inputNumber > 0){
        
    // print input number
        
        if(inputNumber <100 & inputNumber > 0)
            printf("%d cents: ",inputNumber);
            
        // finding number of quarters
        for(afterQuarters = inputNumber; afterQuarters >= Quarter; afterQuarters = afterQuarters - Quarter);
        numQuarters = (inputNumber - afterQuarters) / Quarter;
            
        // finding number of dimes
        for(afterDimes = afterQuarters; afterDimes >= Dime; afterDimes = afterDimes - Dime);
        numDimes = (afterQuarters - afterDimes) / Dime;
            
        // finding number of nickels
        for(afterNickels = afterDimes; afterNickels >= Nickel; afterNickels = afterNickels - Nickel);
        numNickels = (afterDimes - afterNickels) / Nickel;
            
        //finding number of cents
        numCents = afterNickels;
            
        // displaying amount of change

        // displaying quarters
        if(numQuarters == 0);
        else if(numQuarters == 1)
            printf("%d quarter",numQuarters);
        else
            printf("%d quarters",numQuarters);
        
        // dispalying dimes
        if(numQuarters != 0){
            if(numDimes == 0);
            else if(numDimes == 1)
                printf(", %d dime",numDimes);
            else
                printf(", %d dimes",numDimes);
        }
        else {
            if(numDimes == 0);
            else if(numDimes == 1)
                printf("%d dime",numDimes);
            else
                printf("%d dimes",numDimes);
        }
                
        //displaying nickels 
        if(numQuarters == 0 && numDimes == 0){
            if(numNickels == 0);
            else if(numNickels == 1)
                printf("%d nickel",numNickels);
            else
                printf("%d nickels",numNickels);
        }  
        else {
            if(numNickels == 0);
            else if(numNickels == 1)
                printf(", %d nickel",numNickels);
            else
                printf(", %d nickels",numNickels);
        }
            
        //displaying cents
        if (numQuarters == 0 && numDimes == 0 && numNickels == 0){
            if(numCents == 0);
            else if(numCents == 1)
                printf("%d cent",numCents);
            else
                printf("%d cents",numCents);
        }
        else {
            if(numCents == 0);
            else if(numCents == 1)
                printf(", %d cent",numCents);
            else
                printf(", %d cents",numCents);
        }

        // printing period
        printf(". \n");
        
        // again!
        printf("Please give an amount in cents less than 100: "); 
        scanf("%d", &inputNumber);
        
    }

    printf("Goodbye \n");
    
	return 0;
}
