#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
int main()
{
	setlocale(LC_ALL, "Russian");
	int N, BurstTime[10], ArrivalTime[10], process[10];
	do
	{
		printf("Введите количество процессов: "); scanf_s("%d", &N);
	} while (N <= 0 || N > 10);

	for (int i = 0; i < N; i++)
	{
		printf("\nВведите характеристики для процесса %d:\n", i + 1);
		do
		{
			printf("Время выполнения: "); scanf_s("%d", &BurstTime[i]);
		} while (BurstTime[i] < 1);
		do
		{
			printf("Время появления: "); scanf_s("%d", &ArrivalTime[i]);
		} while (ArrivalTime[i] < 0);
		process[i] = i + 1;
	}
	printf("\n");

	int pos, temp;
	for (int i = 0; i < N; i++) // Сортировка процессов по времени появления (от наименьшего к наибольшему)
	{
		pos = i;
		for (int j = i + 1;j < N; j++)
		{
			if (ArrivalTime[j] < ArrivalTime[pos])
				pos = j;
		}

		temp = ArrivalTime[i];
		ArrivalTime[i] = ArrivalTime[pos];
		ArrivalTime[pos] = temp;

		temp = BurstTime[i];
		BurstTime[i] = BurstTime[pos];
		BurstTime[pos] = temp;

		temp = process[i];
		process[i] = process[pos];
		process[pos] = temp;
	}

	for (int i = 0; i < BurstTime[0]; i++) printf("%d", process[0]);
	int TotalTime = BurstTime[0]; // Время работы программы

	for (int i = 1; i < N; i++) // Сортировка процессов по времени выполнения (от наименьшего к наибольшему)
	{
		pos = i;
		for (int j = i + 1;j < N; j++)
		{
			if (BurstTime[j] < BurstTime[pos])
				pos = j;
		}

		temp = ArrivalTime[i];
		ArrivalTime[i] = ArrivalTime[pos];
		ArrivalTime[pos] = temp;

		temp = BurstTime[i];
		BurstTime[i] = BurstTime[pos];
		BurstTime[pos] = temp;

		temp = process[i];
		process[i] = process[pos];
		process[pos] = temp;
	}

	int WaitingTime[10]; // Время ожидания процессов
	WaitingTime[0] = 0; // Первый процесс сразу выполняется, то есть время ожидания = 0
	int flag[10];
	for (int i = 0; i < N; i++) // Флаги для каждого процесса которые показывают, выполнялся ли процесс
		flag[i] = 1;
	int count = N - 1; // Всего процессов (не включая первый)
	while (count > 0) // Пока есть невыполненные процессы
	{
		for (int i = 1; i < N; i++)
		{
			if (ArrivalTime[i] <= TotalTime + 1 && flag[i] == 1) // Если время появления данного процесса меньше, чем текущее время работы программы И процесс ещё не выполнялся
			{
				for (int j = 0; j < BurstTime[i]; j++)
					printf("%d", process[i]); // Активность процесса
				WaitingTime[i] = TotalTime - ArrivalTime[i]; // Время ожидания для данного процесса
				TotalTime = TotalTime + BurstTime[i]; // Новое текущее время работы
				count--; // Уменьшаем количество невыполненных процессов
				flag[i] = 0; // Убираем флаг с процесса, чтобы он не работал второй раз
				i = 0; // Обнуляем счётчик для пробега с начала (если какой-то из процессов не выполнялся ранее, он может выполниться сейчас)
			}
		}
	}
	printf("\n\nПроцесс\t   Время выполнения   Потерянное время       Общее время в системе");
	for (int i = 0; i < N; i++)
	{
		int TurnAroundTime = BurstTime[i] + WaitingTime[i]; // Общее время процесса в системе
		printf("\n   %d\t\t%d\t\t\t%d\t\t  %d", process[i], BurstTime[i], WaitingTime[i], TurnAroundTime);
	}
	printf("\n\n");

	system("pause");
	return 0;
}
