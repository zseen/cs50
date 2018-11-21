char* generateInitialPW(int i)
{

}

char* generateFinalPW(int i)
{

}

void increaseCharacter(char* c) // here c points to exactly one character as far as the function knows
{

}

char* getLexicographicalNextString(char* c) // c is a pointer to a char array
{

}


int main()
{
	char* targetHash = "abas:dbef1323?L";
	
	for(all sizes...)
	{
		char* currentPW = generateInitialPW(i);
		char* finalPW = generateFinalPW(i);
		
		while(current not equals final) // not equals
		{
			char* hash = cryptCalculateMD5(currentPW); // from the crypt library
			if(hash was guessed right)
			{
				printf("Solution, %s", currentPW);
				return 0;
			}
			
			getLexicographicalNextString(currentPW);
		}
	}
	
	return 1;
}