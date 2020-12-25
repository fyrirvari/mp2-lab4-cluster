#include "Cluster.h"

Cluster::Cluster(int processors, Mode mode) : mode(mode), PROCESSORS_AMOUNT(processors), processors(processors)
{
	if (processors < 1 || MAX_PROCESSORS_AMOUNT < processors)
		throw std::exception("Invalid processors amount");
}

void Cluster::run(Queue<struct Task> q, double ratio, unsigned int seed)
{
	srand(seed);
	if (!q.empty())
		queue = q;
	while (true)
	{
		if (tact % 3 == 0)
		{
			system("cls");
			std::cout << "Press \'s\' to stop cluster.";
			std::cout << (mode == Mode::RANDOM ? "\n" : " Press \'a\' to add new task to the cluster.\n");
		}
		std::cout << ".";

		/*for (std::vector<struct OnExecution>::iterator it = onExecution.begin(); it != onExecution.end(); ++it;)
		{
			if (it->completionTact == tact)
			{
				++completed;
				processors += it->task.processors;
				onExecution.erase(it);
				--it;
			}
		}*/
		for (size_t i = 0; i < onExecution.size(); ++i)
		{
			if (onExecution[i].completionTact == tact)
			{
				++completed;
				processors += onExecution[i].task.processors;
				onExecution.erase(onExecution.begin() + i);
				--i;
			}
		}

		if (mode == Mode::RANDOM || mode == Mode::COMBINED)
		{
			if ((rand() % 100) / 100.0 <= ratio)
			{
				if (queue.full())
					++refusals;
				else
					queue.push({ rand() % 20, rand() % (PROCESSORS_AMOUNT + 1), 0 });
			}
		}

		if (mode == Mode::MANUAL || mode == Mode::COMBINED)
		{
			if (_kbhit())
			{
				char c;
				if ((c = _getch()) == 'a')
				{
					std::cout << "\nEnter processors and tact needed to complete the task: ";
					Task task = { 0,0,0 };
					std::cin >> task.processors >> task.tacts;
					while (task.processors > PROCESSORS_AMOUNT || task.tacts > 20)
					{
						std::cout << "Incorrect data. Try again: ";
						std::cin >> task.processors >> task.tacts;
					}
					queue.push(task);
				}
				else if (c == 's')
				{
					system("cls");
					return;
				}
				system("cls");
			}
		}

		if (_kbhit())
		{
			char c;
			if ((c = _getch()) == 's')
			{
				system("cls");
				return;
			}
		}

		for (int i = 0; i < queue.size(); ++i)
		{
			if (queue.geti(i).processors <= processors)
			{
				struct Task task = queue.getd(i);
				processors -= task.processors;
				onExecution.push_back({ task, tact + task.tacts });
			}
			else if (queue.geti(i).priority == 3)
				break;
			else
				++queue.geti(i).priority;
		}

		if (onExecution.empty())
			++idle;

		Sleep(100);

		++tact;
	}
}

void Cluster::stat()
{
	std::cout << std::setw(25) << "Total PROCESSORS: "		<< PROCESSORS_AMOUNT		<< std::endl;
	std::cout << std::setw(25) << "Total TACTS: "			<< tact						<< std::endl;
	std::cout << std::setw(25) << "Total IDLE TACTS: "		<< idle						<< std::endl;
	std::cout << std::setw(25) << "Total COMPLETED TASKS: "	<< completed				<< std::endl;
	std::cout << std::setw(25) << "Total REJECTIONS: "		<< refusals					<< std::endl;
	std::cout << std::setw(25) << "CPI: "					<< (tact * 1.0) / completed << std::endl;
}