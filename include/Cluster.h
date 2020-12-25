#pragma once
#include "Queue.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <iomanip>

enum class Mode
{
	RANDOM,
	MANUAL,
	COMBINED
};

const int MAX_PROCESSORS_AMOUNT = 64;
//const int MAX_TASKS_AMOUNT = 150;

struct Task
{
	int tacts;
	int processors;
	int priority;
};

struct OnExecution
{
	struct Task task;
	int completionTact;
};

class Cluster
{
private:
	Queue<struct Task> queue;
	std::vector<struct OnExecution> onExecution;
	Mode mode;
	int processors;
	const int PROCESSORS_AMOUNT;
	int tact = 0;
	int idle = 0;
	int refusals = 0;
	int completed = 0;
public:
	Cluster(int processors = 5, Mode mode = Mode::RANDOM);
	void run(Queue<struct Task> q = Queue<struct Task>(), double ratio = 0.1, unsigned int seed = time(NULL));
	void stat();
};

