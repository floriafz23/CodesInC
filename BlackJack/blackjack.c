/* 
 * Purpose: Create a code in C that utilizes loops and relational clauses, along with nested ones. 
 *          Additionally, apply pseudo-random number generation. 
 */
 
#include <stdio.h>
#define winningNumber 21
#define dealerLimit 17

int main(int argc, char **argv)
{
    // variables define and initialize here 
    int playerFirstCard, dealerFirstCard;
    int playerWorth, dealerWorth;
    int hitOrStay;
    int playerNextCard, dealerNextCard;
    
    // first card to dealer then player
	if(argc==1)
        srand(time(NULL));
    else
        srand(atoi(argv[1]));
        
    dealerFirstCard = rand() % 13 + 1;
    playerFirstCard = rand() % 13 + 1;
    
    printf("First cards: player %d, dealer %d \n", playerFirstCard,dealerFirstCard);
    
    // determining worth of first cards
    if(playerFirstCard<10) 
        playerWorth = playerFirstCard;
    else 
        playerWorth = 10;
   
    if(dealerFirstCard<10)
        dealerWorth = dealerFirstCard;
    else
        dealerWorth = 10;
    
    // Hit or Stay loop
    
    while(playerWorth<winningNumber & dealerWorth<dealerLimit){
        printf("Type 1 for Hit, 0 to Stay:"); 
        scanf("%d", &hitOrStay);
        
        //if the player hits
        if(hitOrStay==1){
            
            //player draws next card + system determines worth of card, displays card and worth
            
            playerNextCard = rand() % 13 + 1;
            
            if(playerNextCard<10)
                playerWorth = playerWorth + playerNextCard;
            else
                playerWorth = playerWorth + 10;
            printf("Player gets a %d, worth is %d \n",playerNextCard, playerWorth);
            
            //if player worth is less than 21, run hit or stay loop again
            if(playerWorth<winningNumber);
                
            //if player worth is 21, the dealer draws cards
            else if(playerWorth==winningNumber){
                printf("Dealer gets:");
                
                //runs as long as dealer's worth is less than the dealer limit
                while(dealerWorth<dealerLimit){
                    
                    //dealer draws next card + system determines worth of card, displays card
                    if(argc==1)
                        srand(time(NULL));
                    else
                        srand(atoi(argv[1]));
                    
                    dealerNextCard = rand() % 13 + 1;
            
                    if(dealerNextCard<10)
                        dealerWorth = dealerWorth + dealerNextCard;
                    else
                        dealerWorth = dealerWorth + 10;
                    
                    printf(" %d",dealerNextCard);
                }
                printf("\n");
                
                // if dealer's worth is equal to the winning number, tie; if anything else, the player wins
                if(dealerWorth == winningNumber)
                    printf("Tie! \n");
                else if(dealerWorth > winningNumber)
                    printf("Dealer over 21, Player wins");
                else   
                    printf("Player better than Dealer, Player wins");
            
            }
                
            // if player worth is more than 21, the player loses and the dealer wins
            else
                printf("Player over 21, Dealer wins \n");
        }
        
        // if player stays, dealer draws cards
        else if(hitOrStay==0){
            printf("Dealer gets:");
                
            //runs as long as dealer's worth is less than the dealer limit
            while(dealerWorth<dealerLimit){
                    
                //dealer draws next card + system determines worth of card, displays card
                    
                dealerNextCard = rand() % 13 + 1;
            
                if(dealerNextCard<10)
                        dealerWorth = dealerWorth + dealerNextCard;
                else
                    dealerWorth = dealerWorth + 10;
                    
                printf(" %d",dealerNextCard);
            }
            printf("\n");
                
            // if dealer's worth is greater than winning number, player wins
            if(dealerWorth > winningNumber)
                printf("Dealer over 21, Player wins\n");
                
            // if player's worth is between 17 and 21 (inclusive)
            else{
                    
                // if dealer's worth is less than player's worth, player wins
                if(dealerWorth<playerWorth)
                    printf("Player better than Dealer, Player wins\n");
                    
                // if dealer's worth is equal to player's worth, tie
                else if(dealerWorth == playerWorth)
                    printf("Tie!\n");
                    
                // if dealer's worth is more than player's worth, dealer wins
                else 
                    printf("Dealer better than Player, Dealer wins\n");
            }
            
        }
        
        // if player doesn't hit or stay, it asks the prompt again
        else{
            playerWorth = playerWorth;
        }
    }
	return 0;
}
