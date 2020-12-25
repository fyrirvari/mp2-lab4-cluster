#include "Cluster.h"

int getProcessors()
{
	std::cout << "Enter processors amount in the cluster: ";
	int processors;
	std::cin >> processors;
	while (processors < 1 || MAX_PROCESSORS_AMOUNT < processors)
	{
		std::cout << "Incorrect argument. Try again: ";
		std::cin >> processors;
	}
	system("cls");
	return processors;
}

Mode chooseMode()
{
	std::cout << "Choose mode:\n1)Random\n2)Manual\n3)Combined\n--> ";
	int var;
	std::cin >> var;
	Mode mode;
	switch (var)
	{
	case 1: mode = Mode::RANDOM; break;
	case 2: mode = Mode::MANUAL; break;
	case 3: mode = Mode::COMBINED; break;
	default: mode = Mode::RANDOM; break;
	}
	system("cls");
	return mode;
}

int main(void)
{
	Cluster cluster(getProcessors(), chooseMode());
	cluster.run();
	cluster.stat();
	return 0;
}