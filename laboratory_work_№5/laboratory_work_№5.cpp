#include <iostream>
#include <string>
#include <tuple>
using namespace std;

//В одномерном массиве найти среднее арифметическое для элементов,
//расположенных между максимальным и минимальным.Если они следуют один за
//другим, считать его равным нулю.Количество элементов в массиве не более 200.
//Формат числа цц.ц.Массив распечатывать по десять элементов на строке.

//double: представляет вещественное число двойной точности с плавающей точкой

// Прототипы функции
int enter_the_number_of_arr_elements();
double create_an_arr_with_random_real_numbers(double* arr_of_numbers, int number_of_arr_elements);
double round_value(double value, int accuracy);
// Структурированные привязки
// tuple нужен, чтобы функция возвращала несколько значений, а не одно
// в <> пишутся какие типы значений принимает функция
tuple<double, int> finding_the_max_number_and_index(double* arr_of_numbers, int number_of_arr_elements);
tuple<double, int> finding_the_min_number_and_index(double* arr_of_numbers, int number_of_arr_elements);
tuple<int, int> determine_interval(int index_max_arr_number, int index_min_arr_number);
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
	// получаем количество эелементов в массиве, которую вводит пользователь
	int number_of_arr_elements = enter_the_number_of_arr_elements();
	const int n = number_of_arr_elements;
	//new double[n] - new = выделение памяти под массив(те создание динамического массива)
	double* arr_of_numbers = new double[n];
	// создаём массив
	create_an_arr_with_random_real_numbers(arr_of_numbers, n);
	// tie - получаем переменные
	// получаем максимальное число и его индекс
	tie(max_arr_number, index_max_arr_number) = finding_the_max_number_and_index(arr_of_numbers, n);
	// получаем минимальное число и его индекс
	tie(min_arr_number, index_min_arr_number) = finding_the_min_number_and_index(arr_of_numbers, n);
	// получаем интервал
	tie(index_initial, index_end) = determine_interval(index_max_arr_number, index_min_arr_number);
	// плучаем среднее арифметическое
	avg_numbers_arr = calculate_avg(arr_of_numbers, index_initial, index_end);

	// выводим массив, максимальное число его индекс, минимальное число его индекс и среднее арифметическое
	output_arr(arr_of_numbers, n);
	print_the_max_number_in_arr(max_arr_number, index_max_arr_number);
	print_the_min_number_in_arr(min_arr_number, index_min_arr_number);
	print_the_avg_in_arr(avg_numbers_arr);

	system("PAUSE");
	return 0;
}

int enter_the_number_of_arr_elements()
{
	// Пользователь вводит количество элелемнтов в массиве и это количество возвращает функция
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
	// Создаёт массив из случаёных чисел
	const int n = number_of_arr_elements;
	srand(time(NULL)); //рандомизация - инициализация ДСЧ

	// максимально какое число может сгенерироваться
	int BORDER_RANDOMAZER = 100;
	for (int i = 0; i < n; i++)
	{
		//rand() - диапазон Функция от 0 до RAND_MAX(32767)
		//RAND_MAX - это максимальное число, которое может выдать функция rand(); Обычно это число == 32767.
		// генерирует рандомное число
		double random_number = ((double)rand() / (double)RAND_MAX) * BORDER_RANDOMAZER;
		// помещаем число в массив
		arr_of_numbers[i] = round_value(random_number, 1);
	}
	return 0;
}

double round_value(double value, int accuracy)
{	
	// округляет число
	// accuracy - точность. Сколько знаков после запятой
	int rounding_to = pow(10, accuracy);
	return round(value * rounding_to) / rounding_to;
}

tuple<double, int> finding_the_max_number_and_index(double* arr_of_numbers, int number_of_arr_elements)
{
	// Возвращает максимальное число и её индекс
	// берём первоначальные значения для сравнения
	double max_arr_number = arr_of_numbers[0];
	int index_max_arr_number = 0;

	// поиск максимального числа
	for (int i = 1; i < number_of_arr_elements; i++)
	{
		if (arr_of_numbers[i] > max_arr_number)
		{
			max_arr_number = arr_of_numbers[i];
			index_max_arr_number = i;
		}
	}
	return make_tuple(max_arr_number, index_max_arr_number);
}

tuple<double, int> finding_the_min_number_and_index(double* arr_of_numbers, int number_of_arr_elements)
{
	// Возвращает минимальное число и её индекс
	// берём первоначальные значения для сравнения
	double min_arr_number = arr_of_numbers[0],
	       index_min_arr_number = 0;

	// поиск минимального числа
	for (int i = 1; i < number_of_arr_elements; i++)
	{
		if (arr_of_numbers[i] < min_arr_number)
		{
			min_arr_number = arr_of_numbers[i];
			index_min_arr_number = i;
		}
	}
	return make_tuple(min_arr_number, index_min_arr_number);
}

tuple<int, int> determine_interval(int index_max_arr_number, int index_min_arr_number)
{
	// Возвращает интервал в формате начало:конец начало<конец
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
	return make_tuple(index_initial, index_end);
}

double calculate_avg(double* arr_of_numbers, int index_initial, int index_end)
{
	// возвращает среднее арифметическое значение чисел, которые находятся в интервале
	// определение количества элементов
	int count_number_between_max_min_numbers = abs(index_initial - index_end) - 1;
	// первоначальные значения
	// сумма чисел лежащих в интервале
	double sum_numbers_arr_between_max_min_numbers = 0,
			// среднее арифметическая этих чисел
			avg_numbers_arr;
	// если количество элементов больше 0
	if (count_number_between_max_min_numbers)
	{
		// перебор элементов находящихся в интервале
		for (int i = index_initial + 1; i < index_end; i++)
		{
			// складываем числа
			sum_numbers_arr_between_max_min_numbers += arr_of_numbers[i];
		}
		// делим сумму чисел на их количество
		avg_numbers_arr = sum_numbers_arr_between_max_min_numbers / count_number_between_max_min_numbers;
	}
	else
	{
		// если количество элементов = 0
		avg_numbers_arr = count_number_between_max_min_numbers;
	}
	return avg_numbers_arr;
}

void output_arr(double* arr_of_numbers, int number_of_arr_elements)
{
	// Выводит массив
	// количество элементов (размер) массива 
	const int n = number_of_arr_elements;
	// переменная для формирования строки
	string str_numbers_arr;

	for (int i = 0; i < n; i++)
	{
		str_numbers_arr += "a[" + to_string(i) + "]=" + to_string(arr_of_numbers[i]);

		// перевод на следующую строку если выведено 10 элементов
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
