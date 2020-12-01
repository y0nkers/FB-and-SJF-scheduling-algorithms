#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int main()
{
	setlocale(LC_ALL, "Russian");
	int N, process[10], priority[10], BurstTime[10], ArrivalTime[10];
	do
	{
		printf("Введите количество процессов: "); scanf_s("%d", &N);
	} while (N <= 0 || N > 10);
	int foregroundCount = 0, backgroundCount = 0, tempBurst[10];
	for (int i = 0; i < N; i++)
	{
		printf("\nВведите характеристики для процесса №%d\n", i + 1);
		do
		{
			printf("Приоритет процесса: "); scanf_s("%d", &priority[i]);
		} while (priority[i] < 1 || priority[i] > 2);
		if (priority[i] == 2) foregroundCount++;
		else backgroundCount++;
		do
		{
			printf("Время выполнения: "); scanf_s("%d", &BurstTime[i]);
		} while (BurstTime[i] < 1);
		do
		{
			printf("Время появления: "); scanf_s("%d", &ArrivalTime[i]);
		} while (ArrivalTime[i] < 0);
		process[i] = i + 1;
		tempBurst[i] = BurstTime[i];
	}

	int pos, swap;
	for (int i = 0; i < N; i++) // Сортировка процессов по времени появления (от наименьшего к наибольшему)
	{
		pos = i;
		for (int j = i + 1;j < N; j++)
		{
			if (ArrivalTime[j] < ArrivalTime[pos])
				pos = j;
		}

		swap = ArrivalTime[i];
		ArrivalTime[i] = ArrivalTime[pos];
		ArrivalTime[pos] = swap;

		swap = BurstTime[i];
		BurstTime[i] = BurstTime[pos];
		BurstTime[pos] = swap;

		swap = process[i];
		process[i] = process[pos];
		process[pos] = swap;

		swap = priority[i];
		priority[i] = priority[pos];
		priority[pos] = swap;

		swap = tempBurst[i];
		tempBurst[i] = tempBurst[pos];
		tempBurst[pos] = swap;
	}
	int TimeQuantum, TotalTime = 0, TurnAroundTime[10], WaitingTime[10];
	printf("\nВведите время кванта: "); scanf_s("%d", &TimeQuantum);
	while (foregroundCount > 0)
	{
		for (int i = 0; i < N; i++)
		{
			if (priority[i] == 2)
			{
				if (tempBurst[i] <= TimeQuantum && tempBurst[i] > 0)
				{
					TotalTime = TotalTime + tempBurst[i];
					TurnAroundTime[i] = TotalTime - ArrivalTime[i];
					WaitingTime[i] = TotalTime - ArrivalTime[i] - BurstTime[i];
					foregroundCount--;
					for (int j = 0; j < tempBurst[i]; j++)
						printf("%d", process[i]);
					tempBurst[i] = 0;
				}
				else if (tempBurst[i] > 0)
				{
					for (int j = 0; j < TimeQuantum; j++)
						printf("%d", process[i]);
					tempBurst[i] = tempBurst[i] - TimeQuantum;
					TotalTime = TotalTime + TimeQuantum;
				}
			}
		}
	}

	while (backgroundCount > 0)
	{
		for (int i = 0; i < N; i++)
		{
			if (priority[i] == 1)
			{
				if (tempBurst[i] <= TimeQuantum && tempBurst[i] > 0)
				{
					TotalTime = TotalTime + tempBurst[i];
					TurnAroundTime[i] = TotalTime - ArrivalTime[i];
					WaitingTime[i] = TotalTime - ArrivalTime[i] - BurstTime[i];
					backgroundCount--;
					for (int j = 0; j < tempBurst[i]; j++)
						printf("%d", process[i]);
					tempBurst[i] = 0;
				}
				else if (tempBurst[i] > 0)
				{
					for (int j = 0; j < TimeQuantum; j++)
						printf("%d", process[i]);
					tempBurst[i] = tempBurst[i] - TimeQuantum;
					TotalTime = TotalTime + TimeQuantum;
				}
			}
		}
	}
	printf("\n");

	printf("\nПроцесс   Приоритет   Время выполнения   Потерянное время   Общее время в системе");
	for (int i = 0; i < N; i++)
	{
		printf("\n   %d\t      %d\t           %d\t\t\t%d\t\t\t%d", process[i], priority[i], BurstTime[i], WaitingTime[i], TurnAroundTime[i]);
	}
	printf("\n\n");
	/*{
		if (tempBurst[i] <= TimeQuantum && tempBurst[i] > 0)
		{
			TotalTime = TotalTime + tempBurst[i];
			tempBurst[i] = 0;
		}
		else if (tempBurst[i] > 0)
		{
			tempBurst[i] = tempBurst[i] - TimeQuantum;
			TotalTime = TotalTime + TimeQuantum;
		}
		if (tempBurst[i] == 0)
		{
			x--;
			printf("\n   %d\t\t%d\t\t %d\t\t\t %d", process[i], BurstTime[i], TotalTime - ArrivalTime[i], TotalTime - ArrivalTime[i] - BurstTime[i]);
		}
	}*/

	system("pause");
	return 0;
}
