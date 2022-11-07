#include <iostream>
#include <string>
#include <tuple>
using namespace std;

//В одномерном массиве найти среднее арифметическое для элементов,
//расположенных между максимальным и минимальным.Если они следуют один за
//другим, считать его равным нулю.Количество элементов в массиве не более 200.
//Формат числа цц.ц.Массив распечатывать по десять элементов на строке.

//double: представляет вещественное число двойной точности с плавающей точкой

int enter_the_number_of_arr_elements();
double create_an_arr_with_random_real_numbers(double* arr_of_numbers, int number_of_arr_elements);
double round_value(double value, int accuracy);
// Структурированные привязки
std::tuple<double, int> finding_the_max_number_and_index(double* arr_of_numbers, int number_of_arr_elements);
std::tuple<double, int> finding_the_min_number_and_index(double* arr_of_numbers, int number_of_arr_elements);
std::tuple<int, int> determine_interval(int index_max_arr_number, int index_min_arr_number);
double calculate_avg(double* arr_of_numbers, int index_initial, int index_end);
void output_arr(double* arr_of_numbers, int number_of_arr_elements);
void print_the_max_number_in_arr(int max_arr_number, int index_max_arr_number);
void print_the_min_number_in_arr(int min_arr_number, int index_min_arr_number);
void print_the_avg_in_arr(double avg_numbers_arr);

int main()
{
	double max_arr_number, min_arr_number, avg_numbers_arr;
	int index_max_arr_number, index_min_arr_number, index_initial, index_end;

	setlocale(LC_ALL, "ru");
	int number_of_arr_elements = enter_the_number_of_arr_elements();
	const int n = number_of_arr_elements;
	//new double[n] - new = выделение памяти под массив(те создание динамического массива)
	double* arr_of_numbers = new double[n];
	create_an_arr_with_random_real_numbers(arr_of_numbers, n);
	std::tie(max_arr_number, index_max_arr_number) = finding_the_max_number_and_index(arr_of_numbers, n);
	std::tie(min_arr_number, index_min_arr_number) = finding_the_min_number_and_index(arr_of_numbers, n);
	std::tie(index_initial, index_end) = determine_interval(index_max_arr_number, index_min_arr_number);
	avg_numbers_arr = calculate_avg(arr_of_numbers, index_initial, index_end);
	
	output_arr(arr_of_numbers, n);
	print_the_max_number_in_arr(max_arr_number, index_max_arr_number);
	print_the_min_number_in_arr(min_arr_number, index_min_arr_number);
	print_the_avg_in_arr(avg_numbers_arr);

	system("PAUSE");
	return 0;
}

int enter_the_number_of_arr_elements()
{
	int number_of_arr_elements = 0;

	while (true)
	{
		cout << "Введите количество элементво в массиве (не больше 200): ";
		cin >> number_of_arr_elements;
		if (number_of_arr_elements > 200)
			cout << "Ошибка: количество элементов в массиве не должно превышать 200\n";
		else
			break;
	}
	return number_of_arr_elements;
}

double create_an_arr_with_random_real_numbers(double* arr_of_numbers, int number_of_arr_elements)
{
	const int n = number_of_arr_elements;
	srand(time(NULL)); //рандомизация - инициализация ДСЧ

	string str_numbers_arr;
	int BORDER_RANDOMAZER = 100;
	for (int i = 0; i < n; i++)
	{
		//rand() - диапазон Функция от 0 до RAND_MAX(32767)
		//RAND_MAX - это максимальное число, которое может выдать функция rand(); Обычно это число == 32767.
		double random_number = ((double)rand() / (double)RAND_MAX) * BORDER_RANDOMAZER;
		arr_of_numbers[i] = round_value(random_number, 1);
	}
	return 0;
}

double round_value(double value, int accuracy)
{
	int rounding_to = pow(10, accuracy);
	return round(value * rounding_to) / rounding_to;
}

std::tuple<double, int> finding_the_max_number_and_index(double* arr_of_numbers, int number_of_arr_elements)
{
	double max_arr_number = arr_of_numbers[0];
	int index_max_arr_number = 0;

	for (int i = 1; i < number_of_arr_elements; i++)
	{
		if (arr_of_numbers[i] > max_arr_number)
		{
			max_arr_number = arr_of_numbers[i];
			index_max_arr_number = i;
		}
	}
	return std::make_tuple(max_arr_number, index_max_arr_number);
}

std::tuple<double, int> finding_the_min_number_and_index(double* arr_of_numbers, int number_of_arr_elements)
{
	double min_arr_number = arr_of_numbers[0],
	       index_min_arr_number = 0;

	for (int i = 1; i < number_of_arr_elements; i++)
	{
		if (arr_of_numbers[i] < min_arr_number)
		{
			min_arr_number = arr_of_numbers[i];
			index_min_arr_number = i;
		}
	}
	return std::make_tuple(min_arr_number, index_min_arr_number);
}

std::tuple<int, int> determine_interval(int index_max_arr_number, int index_min_arr_number)
{
	int index_initial, index_end;

	if (index_min_arr_number < index_max_arr_number)
	{
		index_initial = index_min_arr_number;
		index_end = index_max_arr_number;
	}
	else
	{
		index_initial = index_max_arr_number;
		index_end = index_min_arr_number;
	}
	return std::make_tuple(index_initial, index_end);
}

double calculate_avg(double* arr_of_numbers, int index_initial, int index_end)
{
	int count_number_between_max_min_numbers = abs(index_initial - index_end) - 1;
	double sum_numbers_arr_between_max_min_numbers = 0,
	       avg_numbers_arr;
	if (count_number_between_max_min_numbers)
	{
		for (int i = index_initial + 1; i < index_end; i++)
		{
			sum_numbers_arr_between_max_min_numbers += arr_of_numbers[i];
		}
		avg_numbers_arr = sum_numbers_arr_between_max_min_numbers / count_number_between_max_min_numbers;
	}
	else
	{
		avg_numbers_arr = count_number_between_max_min_numbers;
	}
	return avg_numbers_arr;
}

void output_arr(double* arr_of_numbers, int number_of_arr_elements)
{
	const int n = number_of_arr_elements;
	string str_numbers_arr;

	for (int i = 0; i < n; i++)
	{
		str_numbers_arr += "a[" + std::to_string(i) + "]=" + std::to_string(arr_of_numbers[i]);

		if ((i + 1) % 10 == 0)
		{
			str_numbers_arr += "\n";
		}
		else if (n - i != 1)
		{
			str_numbers_arr += ", ";
		}
	}
	cout << str_numbers_arr << "\n";
}

void print_the_max_number_in_arr(int max_arr_number, int index_max_arr_number)
{
	cout << "Максимальное значение в массиве = " << max_arr_number << "\nиндекс: " << index_max_arr_number << "\n";
}

void print_the_min_number_in_arr(int min_arr_number, int index_min_arr_number)
{
	cout << "Минимальное значение в массиве = " << min_arr_number << "\nиндекс: " << index_min_arr_number << "\n";
}

void print_the_avg_in_arr(double avg_numbers_arr)
{
	cout << "Среднее арифметическое между максимальным и минимальным значением = " << avg_numbers_arr << "\n";
}
