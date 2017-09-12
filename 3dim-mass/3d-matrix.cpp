#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

/*Класс трехмерных массивов*/
class mass_3d
{
private:
	int x, y, z;													// определяем ширину, высоту и глубину массива
	int ***mass;													// создаем трехмерный массив
public:
	mass_3d() : x(1), y(1), z(1) {};								// конструктор по дефолту
	mass_3d(mass_3d &a);											// присваивание при объявлении
	mass_3d(int x, int y, int z);									// обычный конструктор
	~mass_3d();														// деструктор
	void input_mass();												// ввод матрицы (клавиатура)
	void input_file(int _x, int _y, int _z, string filename);		// ввод матрицы (файл)
	void all_to_output_file(string filename);						// вывод матрицы (более общий - файл)
	void output_mass();												// вывод матрицы (экран)
	void output_file(string filename);								// вывод матрицы (файл)
	void mass_size();												// размер матрицы
	void mirror();													// отражение матрицы
	void transpose();												// транспонирование
	void turn_right_front();										// поворот от себя вправо (прямо-вправо)
	void turn_upper_front();										// поворот прямо от себя (прямо-вверх)
	void turn_right_clock();										// поворот вправо по часовой стрелке
	mass_3d& operator=(mass_3d &a);									// присваивание
	mass_3d& operator+=(mass_3d &a);								// сложение с перезаписью левой части
	mass_3d& operator-=(mass_3d &a);								// вычитание с перезаписью левой части
	mass_3d& operator*=(mass_3d &a);								// умножение с перезаписью левой части
	mass_3d& operator/=(mass_3d &a);								// деление с перезаписью левой части
	friend ostream& operator<<(ostream& os, mass_3d&);				// перегрузка вывода 
};

/*Деструктор*/
mass_3d::~mass_3d()
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			delete[] mass[i][j];
		}
	delete[] mass[i];
	}
delete[] mass;
}

/*Присваивание - инициализация*/
mass_3d::mass_3d(mass_3d &a)
{
x = a.x;
y = a.y;
z = a.z;
mass = new int **[x];
for (int i = 0; i < x; i++)
{
	mass[i] = new int*[y];
	for (int j = 0; j < y; j++)
	{
		mass[i][j] = new int[z];
		for (int k = 0; k < z; k++)
		{
			mass[i][j][k] = a.mass[i][j][k];
		}
	}
}
}

/*Конструктор*/
mass_3d::mass_3d(int _x, int _y, int _z)
{
	x = _x;
	y = _y;
	z = _z;
}

/*Размер*/
void mass_3d::mass_size()
{
	cout << "Введите строки (x) матрицы: ";
	cin >> x;
	cout << "Введите столбцы (y) матрицы: ";
	cin >> y;
	cout << "Введите глубину (z) матрицы: ";
	cin >> z;
	cout << endl;
}

/*Ввод с клавиатуры*/
void mass_3d::input_mass()
{
	/*Заполнение*/
	mass = new int **[x];
	for (int i = 0; i < x; i++)
	{
		mass[i] = new int*[y];
		for (int j = 0; j < y; j++)
		{
			mass[i][j] = new int[z];
			for (int k = 0; k < z; k++)
			{
				cout << "(x: " << i << ", y: " << j << ", z: " << k << "): ";
				cin >> mass[i][j][k];
			}
		}
	}
	cout << endl;
}

/*Ввод из файла*/
void mass_3d::input_file(int _x, int _y, int _z, string filename)
{
	x = _x;
	y = _y;
	z = _z;
	ifstream f;
	f.open(filename);

	if (f.is_open() == 0)
	{
		cout << endl << "Ошибка: файл не существует или не может быть открыт" << endl;
		exit(1);
	}
	else
	{
		cout << "Файл <" << filename <<  "> успешно загружен!" << endl;
		/*Заполнение*/
		mass = new int **[x];
		for (int i = 0; i < x; i++)
		{
			mass[i] = new int*[y];
			for (int j = 0; j < y; j++)
			{
				mass[i][j] = new int[z];
				for (int k = 0; k < z; k++)
				{
					f >> mass[i][j][k];
				}
			}
		}
	}
	f.close();
}

/*Общая запись в файл*/
void mass_3d::all_to_output_file(string filename)
{
	cout << "Записать вывод в файл?" << endl << "1 - да, 0 - нет" << endl;
	bool choose;
	cin >> choose;
	if (choose)
	{
		ofstream file;
		file.open(filename);
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				for (int k = 0; k < z; k++)
				{
					cout << "(" << i << ", " << j << ", " << k << "): " << mass[i][j][k] << endl;
				}
			}
		}
		file.close();
		cout << "Файл был успешно записан";
	}
	else return;
}

/*Вывод на экран*/
void mass_3d::output_mass()
{
	cout << "Вывод: " << endl;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				cout << "(" << i << ", " << j << ", " << k << "): " << mass[i][j][k] << endl;
			}
		}
	}
}

/*Вывод в файл*/
void mass_3d::output_file(string filename)
{
	ofstream f;
	f.open(filename);
	f << "Вывод: " << endl;
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				f << "(" << i << ", " << j << ", " << k << "): " << mass[i][j][k] << endl;
			}
		}
	}
	f.close();
	cout << "Файл <" << filename << "> был успешно записан" << endl;
}

/*Перегрузка /= */
mass_3d& mass_3d::operator/=(mass_3d &a)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				mass[i][j][k] /= a.mass[i][j][k];
			}
		}
	}
	return *this;
}

/*Перегрузка *= */
mass_3d& mass_3d::operator*=(mass_3d &a)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				mass[i][j][k] *= a.mass[i][j][k];
			}
		}
	}
	return *this;
}

/*Перегрузка += */
mass_3d& mass_3d::operator+=(mass_3d &a)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				mass[i][j][k] += a.mass[i][j][k];
			}
		}
	}
	return *this;
}

/*Перегрузка -= */
mass_3d& mass_3d::operator-=(mass_3d &a)
{
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				mass[i][j][k] -= a.mass[i][j][k];
			}
		}
	}
	return *this;
}

/*Перегрузка = */
mass_3d& mass_3d::operator=(mass_3d &a)
{
	x = a.x;
	y = a.y;
	z = a.z;
	mass = new int **[x];
	for (int i = 0; i < x; i++)
	{
		mass[i] = new int*[y];
		for (int j = 0; j < y; j++)
		{
			mass[i][j] = new int[z];
			for (int k = 0; k < z; k++)
			{
				mass[i][j][k] = a.mass[i][j][k];
			}
		}
	}
	return *this;
}

/*Перегрузка + */
mass_3d operator+(mass_3d a, mass_3d b)
{
	mass_3d r;
	r = a;
	return r += b;
}

/*Перегрузка - */
mass_3d operator-(mass_3d a, mass_3d b)
{
	mass_3d r;
	r = a;
	return r -= b;
}

/*Перегрузка * */
mass_3d operator*(mass_3d a, mass_3d b)
{
	mass_3d r;
	r = a;
	return r *= b;
}

/*Перегрузка / */
mass_3d operator/(mass_3d a, mass_3d b)
{
	mass_3d r;
	r = a;
	return r /= b;
}

/*Перегрузка вывода*/
ostream& operator<<(ostream& os, mass_3d &object)
{
	os << endl;
	for (int i = 0; i < object.x; i++)
	{
		for (int j = 0; j < object.y; j++)
		{
			for (int k = 0; k < object.z; k++)
			{
				//os << "(" << i << ", " << j << ", " << k << "): " << object.mass[i][j][k] << endl;
				os << object.mass[i][j][k] << " ";
			}
		}
		os << endl;
	}
	os << endl;
	return os;
}

/*Отражение относительно осей*/
void mass_3d::mirror()
{
	cout << "Относительно какой оси следует выполнить отражение?" << endl << "(x (перед-зад), y (верх-дно), z (право-лево)):" << endl;
	char choose;
	cin >> choose;
	/*выполняем копирование массива во временный*/
	int ***temp = new int **[x];
	for (int i = 0; i < x; i++)
	{
		temp[i] = new int*[y];
		for (int j = 0; j < y; j++)
		{
			temp[i][j] = new int[z];
			for (int k = 0; k < z; k++)
			{
				temp[i][j][k] = mass[i][j][k];
			}
		}
	}
	/*относительно z*/
	if (choose == 'z')
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				for (int k = 0; k < z; k++)
				{
					mass[i][j][k] = temp[(x - 1) - i][j][k];
				}
			}
		}
	}
	/*относительно x*/
	if (choose == 'x')
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				for (int k = 0; k < z; k++)
				{
					mass[i][j][k] = temp[i][j][(z - 1) - k];
				}
			}
		}
	}
	/*относительно y*/
	if (choose == 'y')
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				for (int k = 0; k < z; k++)
				{
					mass[i][j][k] = temp[i][(y - 1) - j][k];
				}
			}
		}
	}
}

/*Транспонирование трехмерной матрицы (через перед. грань)*/
void mass_3d::transpose()
{
	int elem;
	for (int i = 0; i < x; i++)
	{
		for (int j = i; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				elem = mass[i][j][k];
				mass[i][j][k] = mass[j][i][k];
				mass[j][i][k] = elem;
			}
		}
	}
	if (z > 1)
	{
		int ***temp = new int **[x];
		for (int i = 0; i < x; i++)
		{
			temp[i] = new int*[y];
			for (int j = 0; j < y; j++)
			{
				temp[i][j] = new int[z];
				for (int k = 0; k < z; k++)
				{
					temp[i][j][k] = mass[(x - 1) - i][(y - 1) - j][(z - 1) - k];
				}
			}
		}
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				for (int k = 0; k < z; k++)
				{
					mass[i][j][k] = temp[i][j][k];
				}
			}
		}
	}
}

/*Поворот прямо от себя (прямо-вверх)*/
void mass_3d::turn_upper_front()
{
	int ***temp = new int **[x];
	for (int i = 0; i < x; i++)
	{
		temp[i] = new int*[y];
		for (int j = 0; j < y; j++)
		{
			temp[i][j] = new int[z];
			for (int k = 0; k < z; k++)
			{
				temp[i][j][k] = mass[i][k][j];
			}
		}
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				mass[i][j][k] = temp[i][(y - 1) - j][k];
			}
		}
	}
}

/*поворот вправо по часовой стрелке*/
void mass_3d::turn_right_clock()
{
	int ***temp = new int **[x];
	for (int i = 0; i < x; i++)
	{
		temp[i] = new int*[y];
		for (int j = 0; j < y; j++)
		{
			temp[i][j] = new int[z];
			for (int k = 0; k < z; k++)
			{
				temp[i][j][k] = mass[j][i][k];
			}
		}
	}
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < z; k++)
			{
				mass[i][j][k] = temp[i][(y - 1) - j][k];
			}
		}
	}
}

/*поворот вправо от себя (право-вперёд)*/
void mass_3d::turn_right_front()
{
	int ***temp = new int **[x];
	for (int i = 0; i < x; i++)
	{
		temp[i] = new int*[y];
		for (int j = 0; j < y; j++)
		{
			temp[i][j] = new int[z];
			for (int k = 0; k < z; k++)
			{
				temp[i][j][k] = mass[k][j][i];
			}
		}
	}
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				for (int k = 0; k < z; k++)
				{
					mass[i][j][k] = temp[i][j][(z - 1) - k];
				}
			}
		}
}

/*Вводное окно*/
int opener()
{
cout << endl << endl;
cout << "	________ ________                                     " << endl;
cout << "	\\_____  \\\\______ \\        _____ _____    ______ ______" << endl;
cout << "	  _(__  < |    |  \\      /     \\\\__  \\  /  ___//  ___/" << endl;
cout << "	 /       \\|    `   \\    |  Y Y  \\/ __ \\_\\___ \\ \\___ \\ " << endl;
cout << "	/______  /_______  /____|__|_|  (____  /____  >____  >" << endl;
cout << "	       \\/        \\/_____/     \\/     \\/     \\/     \\/ " << endl;
cout << "		Т р ё х м е р н ы й	м а с с и в" << endl << endl << endl;
cout << "		Что следует сделать?" << endl;
cout << "		1. Отражение трехмерной матрицы" << endl;
cout << "		2. Действия с матрицами (перегрузки)" << endl;
cout << "		3. Транспонирование трехмерной матрицы" << endl;
cout << "		4. Повороты трехмерной матрицы" << endl << endl;
cout << "		Ввод: ";
	int choose;
	cin >> choose;
	cout << endl << endl;
	return choose;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int choose = opener();
	if (choose == 4)
	{
		mass_3d A;
		A.input_file(3, 3, 3, "1.txt");
		cout << "1. Поворот прямо от себя (прямо-вверх)" << endl;
		cout << "2. поворот вправо по часовой стрелке" << endl;
		cout << "3. поворот вправо от себя (право-вперёд)" << endl;
		int num;
		cin >> num;
		cout << "Матрица А:" << A;
		if (num == 1)
		{
			A.turn_upper_front();
		}
		if (num == 2)
		{
			A.turn_right_clock();
		}
		if (num == 3)
		{
			A.turn_right_front();
		}
		cout << "Поворот:" << A;
	}
	if (choose == 3)
	{
		mass_3d A;
		A.input_file(3, 3, 3, "1.txt");
		cout << "Матрица А:" << A;
		A.transpose();
		cout << "Транспонированная матрица А:" << A;
	}
	if (choose == 1)
	{
		mass_3d A;
		A.input_file(2, 2, 2, "1.txt");
		cout << "Матрица А:" << A;
		A.mirror();
		cout << "Отраженная матрица А:" << A;
	}
	if (choose == 2)
	{
		mass_3d A, B, C;
		A.input_file(2, 2, 2, "1.txt");
		B.input_file(2, 2, 2, "2.txt");
		C = A + B;
		mass_3d D = A - B;
		mass_3d E = A * B;
		mass_3d F = A / B;
		cout << "Матрица А:" << A;
		cout << "Матрица B:" << B;
		cout << "Сложение:" << C;
		cout << "Вычитание: " << D;
		cout << "Покомпонентное умножение: " << E;
		cout << "Покомпонентное деление: " << F;
	}
	return 0;
}