#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame()	// constructor - basically sets the game up for first play / the original look of it :)
{
	Reset();
}

// if not selfexplanatiry - these methods fetch the number of maximum tries and what try the user is on
int32 FBullCowGame::GetMaxTries() const {	return MyMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }


bool FBullCowGame::IsGameWon() const
{
	//	TODO create an algorithm to check if the user provided a correct guess
	return false;
}


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "ant";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false)// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else if (false)	// if the guess contains non alphabetical characters
	{
		return EGuessStatus::Symbolic_Input;
	}
	else // otherwise OK
	{
		return EGuessStatus::OK;
	}
}

//	receives a VALID guess, increments turn, returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;
	// setup a return variable / structure
	FBullCowCount BullCowCount;
	
	// loop through all letters in guess
	int32 HiddenWordLenght = MyHiddenWord.length();
	for (int32 MHWChar = 0; MHWChar < HiddenWordLenght; MHWChar++)
	{
		//compare letters against the hidden word
		for (int32 GChar = 0; GChar < HiddenWordLenght; GChar++)
		{
			if (MyHiddenWord[MHWChar] == Guess[GChar])	// in case of same characters	
			{
				if (MHWChar == GChar)	// in the same spot
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}	
	}
	return BullCowCount;
}
