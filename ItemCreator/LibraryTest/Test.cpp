#include <ItemReader.h>

int main()
{
	ItemLibrary::ItemLoader loader;

	loader.Load("../TestDatabase.db");

	return 0;
}