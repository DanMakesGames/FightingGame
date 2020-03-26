#include "Asset.h"
#include "Master.h"

Master* Asset::master = nullptr;

Asset::Asset(string inSource, EAssetType inType) : source(inSource), type(inType)
{
}

string Asset::GetSource()
{
	return source;
}

void Asset::SetSource(string sourceName)
{
	source = sourceName;
}