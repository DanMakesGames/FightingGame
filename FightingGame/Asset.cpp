#include "Asset.h"

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