/* This is the console exetucable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCow class.
*/



#include <iostream>
#include <string>
#include "FBullCowGame.h"	// reminder: quotation marks are linking local files (selfmade) to the compiler

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
FBullCowGame BCGame;	// instantiate a new game


int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	}
	while (AskToPlayAgain());
	return 0;	// exit the application
}




// introduce the game
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows\n";
	std::cout << "You think you can guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n" << std::endl;
	return;
}

// loop to get a valid guess from the player
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		FText Guess = "";
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an Isogram.\n";
			break;
		case EGuessStatus::Numeric_Input:
			std::cout << "Enter only words, no numbers please.\n";
			break;
		case EGuessStatus::Symbolic_Input:
			std::cout << "No symbols in words please.\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Enter only lowercase words please.\n";
			break;
		default:
			return Guess;
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);	// keep looping while we get no errors

	

	
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries << " chances to guess the isogram." << std::endl;
	
	// loop for number of turns asking for guesses
	for (int32 i = 0; i < MaxTries; i++) // TODO change from FOR to WHILE
	{
		FText Guess = GetValidGuess();

		// Submit valid guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);  
		
		std::cout << "Bulls =  " << BullCowCount.Bulls;
		std::cout << ". Cows =  " << BullCowCount.Cows << "\n\n";
	}
	// TODO summarise game

}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (Y/N)" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y' || Response[0] == 'Y');
}


