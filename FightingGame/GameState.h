#pragma once
class GameState
{
	bool SaveGameState(unsigned char**buffer, int *len, int*checksum, int frame);
	bool LoadGameState(unsigned char* buffer, int len);
};

