#include "stdafx.h"
#include <fstream>
#include <iostream>
#include "conio.h"
#include <cstdlib>
#include <ctime>

using namespace std;

class Matrix
{
private:
	int x = 0;
	int y = 0;
public:
	int getX()
	{
		return x;
	}
	void setX(int x)
	{
		this->x = x;
	}
	int getY()
	{
		return y;
	}
	void setY(int y)
	{
		this->y = y;
	}
};


class Points
{
private:
	//static Matrix *bigmatrix; // ������ �����
	static Matrix* bigmatrix;
	static int n; // ���������� �����
	static int maximumX; // ������������ ���������� X
	static int maximumY; // ������������ ���������� Y
	static void setN()
	{
		cout << "Put amount of points" << endl;
		cin >> n;
	}
	static Matrix* setAndGetMatrix()
	{
		setN();
		Matrix *matrix = new Matrix[n];
		return matrix;
	}
public:
	static void formPoints() {
		bigmatrix = setAndGetMatrix();
		readFromFile();
		outPut();
		determineMaximumX();
		determineMaximumY();
	} // ������������ �������	
	static Matrix* getMatrix()
	{
		return bigmatrix;
	}
	static void readFromFile()
	{
		ifstream read("task.txt");
		if (!read.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}
		//read.getline(mass, 50);
		for (int i = 0; i < n; i++)
		{
			int x1, y1;
			read >> x1;
			bigmatrix[i].setX(x1);
			read >> y1;
			bigmatrix[i].setY(y1);
		}
		read.close();
	} // ������ �� ����
	static void outPut() // ����� �� ����� �����
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			print << "Error! File can't be open!" << endl;
		}
		for (int i = 0; i < n; i++)
		{
			print << i + 1 << " point is ";
			print << "(" << bigmatrix[i].getX() << ", ";
			print << bigmatrix[i].getY() << ")" << endl;
		}
		print.close();
	}
	static Matrix* getBigMatrix()
	{
		return bigmatrix;
	}
	static int getN()
	{
		return n;
	}
	static void determineMaximumX()
	{
		maximumX = 0;
		for (int i = 0; i < Points::n; i++)
		{
			if (bigmatrix[i].getX() > maximumX) maximumX = bigmatrix[i].getX();
		}
	}
	static void determineMaximumY()
	{
		maximumY = 0;
		for (int i = 0; i < Points::n; i++)
		{
			if (bigmatrix[i].getY() > maximumY) maximumY = bigmatrix[i].getY();
		}
	}
	static int getMaximumX()
	{
		return maximumX;
	}
	static int getMaximumY()
	{
		return maximumY;
	}
};
Matrix *Points::bigmatrix;
int Points::n;
int Points::maximumX;
int Points::maximumY;

class Connection�hromosome
{
private:
	int** random;
	int** out;
	int indexOut = 0;
	int* tmp1;
	int* tmp2;
	int p2 = 0;
public:
	void formConnection�hromosome(int ord) // ord - ����� ������ �� ����� 
	{
		formRandomArray(); // ������������ Random
		printRandomArray(ord); // ����� Random �� �����
		formTmp1(); // ������������ tmp1
		formTmp2(); // ������������ tmp2
		formOut(); // ������������ out
		Connection�hromosomeAlgorythm(); // ��� ��������
		printOut(ord);		
	}
	void formConnectionChromosomeForChild(int ord, int** random1, int** random2) // ������������ ���������� ������� ��� �������
	{
		random = new int*[Points::getN() - 1]; // ������������ RANDOM
		for (int i = 0; i < Points::getN() - 1; i++)
		{
			random[i] = new int[2];
		}
		for (int i = 0; i < Points::getN()/2; i++)   
		{
				for (int j = 0; j < 2; j++)
				{
					random[i][j] = random1[i][j];
				}
		}
		for (int i = Points::getN()/2 /*+1*/; i < Points::getN() - 1; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				random[i][j] = random2[i][j];
			}
		}
		printRandomArray(ord); // ����� Random �� �����
		formTmp1(); // ������������ tmp1
		formTmp2(); // ������������ tmp2
		formOut(); // ������������ out
		Connection�hromosomeAlgorythm(); // ��� ��������
		printOut(ord);
	}
	void Connection�hromosomeAlgorythm()
	{
		int localN = Points::getN();
			for (int i = 0; i < Points::getN() - 1; i++)
				for (int j = 0; j < 2; j++)
				{
					if ((i == 0) || (j == 0)) /* ������ ������������ ������� �����
											  ���� � ����� ����� ������ ���� ���������� ��
											  ������������ ������� ����� ����*/
					{
						int index = random[i][j] % localN;
						tmp2[p2] = tmp1[index];
						out[indexOut][j] = tmp1[index];
						tmp1[index] = 0;
						shiftZerosInTmp1();
						localN--;
						p2++;
						if ((i == 0) && (j == 1)) indexOut++;
					}
					else
					{
						int index = random[i][1] % (p2-1);
						out[indexOut][1] = tmp2[index];
						indexOut++;
					}
				}
	}
	void formRandomArray()
	{
		random = new int*[Points::getN() - 1]; // ������������ RANDOM
		for (int i = 0; i < Points::getN() - 1; i++)
		{
			random[i] = new int[2];

		}
		for (int i = 0; i < Points::getN() - 1; i++)
			for (int j = 0; j < 2; j++)
			{
				random[i][j] = rand() % 900 + 100; // �� 100 �� 999
			}
	}
	void printRandomArray(int ord) // ����� ���������� ������� �� �����
	{
			ofstream print("result.txt", ios_base::app); // ������ � ����� �����
			if (!print.is_open())
			{
				cout << "Error! File can't be open!" << endl;
			}
			print << ord + 1 << " random array:" << endl;
			for (int i = 0; i < Points::getN() - 1; i++)
				for (int j = 0; j < 2; j++)
				{
					if (j == 0) print << "(" << random[i][j] << ",";
					if (j == 1) print << random[i][j] << ")";
					if ((j == 1) && (i != Points::getN() - 1)) print << " ";
				}
			print << endl;
			print.close();
	}
	void formTmp1()
	{
		tmp1 = new int[Points::getN()];
		for (int i = 0; i < Points::getN(); i++)
		{
			tmp1[i] = i + 1;
		}
	}
	void shiftZerosInTmp1()
	{
		for (int i = 0; i < Points::getN(); i++)
		{
			if (tmp1[i] == 0)
			{
				for (int j = i; j < Points::getN() - 1; j++)
				{
					int tmp = tmp1[j];
					tmp1[j] = tmp1[j + 1];
					tmp1[j + 1] = tmp;
				}
			}
		}
	}
	void formTmp2()
	{
		tmp2 = new int[Points::getN()];
		for (int i = 0; i < Points::getN(); i++)
		{
			tmp2[i] = 0;
		}
	}
	void formOut()
	{
		out = new int*[Points::getN()-1];
		for (int i = 0; i < Points::getN() - 1; i++)			
		{
			out[i] = new int[2];
		}
		for (int i = 0; i < Points::getN() - 1; i++)
			for (int j = 0; j < 2; j++)
			{
				out[i][j] = 0;
			}
	}
	void printOut(int ord)
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			print << "Error! File can't be open!" << endl;
		}
		print << ord + 1 << " Out array:" << endl;
		for (int i = 0; i < Points::getN() - 1; i++)
			for (int j = 0; j < 2; j++)
			{
				if (j == 0) print << "(" << out[i][j] << ",";
				if (j == 1) print << out[i][j] << ")";
				if ((j == 1) && (i != Points::getN() - 1)) print << " ";
			}
		print << endl;
		print.close();
	}
	void printOutAfter(int ord)
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			print << "Error! File can't be open!" << endl;
		}
		print << ord + 1 << " Out array after modification:" << endl;
		for (int i = 0; i < Points::getN() - 1; i++)
			for (int j = 0; j < 2; j++)
			{
				if (j == 0) print << "(" << out[i][j] << ",";
				if (j == 1) print << out[i][j] << ")";
				if ((j == 1) && (i != Points::getN() - 1)) print << " ";
			}
		print << endl;
		print.close();
	}
	int** getOut()
	{
		return out;
	}
	void setOut(int **newOut)
	{
		out = newOut;
	}
	int** getRandomArray()
	{
		return random;
	}
};
class Order�hromosome
{
private:
	int *orderArray;
public:
	void formOrderChromosome(int order)
	{
		orderArray = new int[Points::getN() - 1];
		int *tmpArray = new int[Points::getN() - 1]; // ��������� ������ � �������, ������� ��� ���� � orderArray
		bool noThatNumber = false; // ����������, ���� �� ��� ����� �����
		int tmpNumber = 0; // ��������� ��������� ����� 
		int tmpPointer = 0; // ��������� ���������
		for (int i = 0; i < Points::getN() - 1; i++)
		{
			orderArray[i] = 0;
			tmpArray[i] = 0;
		}
		for (int i = 0; i < Points::getN() - 1; i++) 
		{
			while (noThatNumber == false)
			{
				noThatNumber = true;
				tmpNumber = 1 + rand() % (Points::getN()-1);
				for (int j = 0; j < tmpPointer; j++)
				{
					if (tmpNumber == tmpArray[j]) noThatNumber = false;
				}				
			}
			noThatNumber = false;
			orderArray[i] = tmpNumber;
			tmpArray[tmpPointer] = tmpNumber;
			tmpPointer++;
			
		}
		printOrderChromosome(order);
		
	}
	void printOrderChromosome(int order)
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			print << "Error! File can't be open!" << endl;
		}
		print << order+1 << " Order Array: ";
		for (int i = 0; i < Points::getN() - 1; i++)
		{
			print << orderArray[i] << " ";
		}
		print << endl;
		print.close();
	}
	int* getOrderArray()
	{
		return orderArray;
	}
	int** sortOutWithOrderArray(int** out) 
	{
		int** testOutArray = new int*[Points::getN() - 1];
		for (int i = 0; i < Points::getN() - 1; i++) /*������������ ��������� ������� out, ����� ������������ 
													 ��� ��� ���������� � ������������ � �������� order*/
		{
			testOutArray[i] = new int[2];
		}
		for (int i = 0; i < Points::getN() - 1; i++)
			for (int j = 0; j < 2; j++)
			{
				testOutArray[i][j] = out[i][j];
			}
		for (int i = 0; i < Points::getN()-1; i++)
		{
			int indexOrder = orderArray[i];
			out[i] = testOutArray[indexOrder-1]; // ���� ����������
		}
		return out;
	}
};
class Variant�hromosome
{
private:
	int *variantArray; // ������ �������
public:
	void formVariantChromosome(int order)
	{
		variantArray = new int[Points::getN() - 1];
		for (int i = 0; i < Points::getN()-1; i++)
		{
			variantArray[i] = 0 + rand() % 2;
		}
		printVariantChromosome(order);
	}
	void printVariantChromosome(int order)
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}		
		print << order+1 <<" Variant Array: ";
		for (int i = 0; i < Points::getN() - 1; i++)
		{
			print << variantArray[i] << " ";
		}
		print << endl;
		print.close();
	}
	int* getVariantArray()
	{
		return variantArray;
	}
	void changeArrayForMutant()
	{
		if ((variantArray[Points::getN() - 2]) == 0) variantArray[Points::getN() - 2] = 1;
		else
		if ((variantArray[Points::getN() - 2]) == 1) variantArray[Points::getN() - 2] = 0;
	}
};

class Species 
{
private:
	Connection�hromosome connection�hromosome;
	Order�hromosome orderChromosome;
	Variant�hromosome variant�hromosome;
	int** treeMatrix; // ���� ������
public:
	void setConnection�hromosome(int order)
	{
		connection�hromosome.formConnection�hromosome(order);
	}
	void setConnection�hromosomeForChild(int order,int** rand1, int** rand2)
	{
		connection�hromosome.formConnectionChromosomeForChild(order, rand1, rand2); 
	}
	void setVariant�hromosome(int order)
	{
		variant�hromosome.formVariantChromosome(order);
	}
	void setOrderChromosome(int order)
	{
		orderChromosome.formOrderChromosome(order);
	}
	void setTreeMatrix(int order)
	{
		treeMatrix = new int*[Points::getMaximumY()+1]; // ����� ���������� ������������ ���������, ����� ������� ��������� ������ [y][x]
		for (int i = 0; i < Points::getMaximumY()+1; i++)
		{
			treeMatrix[i] = new int[Points::getMaximumX()+1];
		}
		for (int i = 0; i < Points::getMaximumY()+1; i++)
			for (int j = 0; j < Points::getMaximumX()+1; j++)
		{
				treeMatrix[i][j] = 0;
		}
	}
	void printTreeMatrix(int order)
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}		
		print << order + 1 << " Tree array:" << endl;
		for (int i = 0; i < Points::getMaximumY()+1; i++)
			for (int j = 0; j < Points::getMaximumX()+1; j++)
			{
				print << treeMatrix[i][j] << " ";
				if (j == Points::getMaximumX()) print << endl;
			}
		print << endl;
		print.close();
	}
	void sortOutWithOrderArray(int order)
	{
		int **out = connection�hromosome.getOut();
		connection�hromosome.setOut(orderChromosome.sortOutWithOrderArray(out));
		connection�hromosome.printOutAfter(order);
	}
	void treeBuilding(int order)
	{
		int** vertexArray = connection�hromosome.getOut();
		int* variantArray = variant�hromosome.getVariantArray();
		Matrix* points = Points::getBigMatrix();
		for (int i = 0; i < Points::getN() - 1; i++)
		{
			//treeMatrix[Points::getMaximumY()-points[i].getY()][points[i].getX()] = 1; 
			/* � ������������ ��������� [Points::getMaximumY()-points[i].getY()][points[i].getX()]*/
			
			int firstPointNumber = vertexArray[i][0]; // ����� ����� �� ������� ������ �����
			int secondPointNumber = vertexArray[i][1]; // ����� ����� � ������� ������ �����
			Matrix firstPoint = points[firstPointNumber - 1]; // ����� �� ������� ������ �����
			Matrix secondPoint = points[secondPointNumber - 1]; // ����� � ������� ������ �����
			int realSecondPointY = Points::getMaximumY() - secondPoint.getY();
			if (variantArray[i] == 0) // ���� ����� ������ �� x
			{
				bool completed = false; // �������� ��� ������ �� ����� ����������� �� �
				int currentX = firstPoint.getX(); 
				int currentY = Points::getMaximumY() - firstPoint.getY();
				if (currentX < secondPoint.getX()) // ���� ������ ����� ����� ������ ������
				{ /* ����� 2 - �������, ����� 1 - �����*/
					while (completed == false)
					{
						treeMatrix[currentY][currentX] = 1;
						if ((currentX == secondPoint.getX())) completed = true;
						else currentX++;
					}
				} else
				if (currentX > secondPoint.getX()) // ���� ������ ����� ����� ����� ������
				{
					while (completed == false)
					{
						treeMatrix[currentY][currentX] = 1;
						if ((currentX == secondPoint.getX())) completed = true;
						else currentX--;
					}
				}
				/* ������� ������� �� �, ������ ������ �� y*/
				completed = false;
				if (currentY < realSecondPointY) // ���� ������ ����� ����� ���� ������
				{
					while (completed == false)
					{
						treeMatrix[currentY][currentX] = 1;
						if ((currentY == realSecondPointY)) completed = true;
						else currentY++;
					}
				}
				else
					if (currentY > realSecondPointY) // ���� ������ ����� ����� ���� ������
					{
						while (completed == false)
						{
							treeMatrix[currentY][currentX] = 1;
							if ((currentY == realSecondPointY)) completed = true;
							else currentY--;
						}
					}				
			} 
			else
			if (variantArray[i] == 1) // ���� ����� ������ �� y
			{
				bool completed = false; // �������� ��� ������ �� ����� ����������� �� �
				int currentX = firstPoint.getX();
				int currentY = Points::getMaximumY() - firstPoint.getY();
				/* ������ ������� ������ �� y, � ����� �� �*/
				if (currentY < realSecondPointY) // ���� ������ ����� ����� ���� ������
				{
					while (completed == false)
					{
						treeMatrix[currentY][currentX] = 1;
						if ((currentY == realSecondPointY)) completed = true;
						else currentY++;
					}
				}
				else
					if (currentY > realSecondPointY) // ���� ������ ����� ����� ���� ������
					{
						while (completed == false)
						{
							treeMatrix[currentY][currentX] = 1;
							if ((currentY == realSecondPointY)) completed = true;
							else currentY--;
						}
					}
				/////////////
				completed = false;
				////////////
				if (currentX < secondPoint.getX()) // ���� ������ ����� ����� ������ ������
				{
					while (completed == false)
					{
						treeMatrix[currentY][currentX] = 1;
						if ((currentX == secondPoint.getX())) completed = true;
						else currentX++;
					}
				}
				else
					if (currentX > secondPoint.getX()) // ���� ������ ����� ����� ����� ������
					{
						while (completed == false)
						{
							treeMatrix[currentY][currentX] = 1;
							if ((currentX == secondPoint.getX())) completed = true;
							else currentX--;
						}
					}
			}
		}
		/*�������� ��� ������� ��������*/
		for (int i = 0; i < Points::getN(); i++)
		{
			treeMatrix[Points::getMaximumY()- points[i].getY()][points[i].getX()] = 2;
		}
		printTreeMatrix(order);
	}
	int countTheLength(int order) // ������� � ���������� ����� ������
	{
		int lenght = 0;
		for (int i = 0; i < Points::getMaximumY() + 1; i++)
			for (int j = 0; j < Points::getMaximumX() + 1; j++)
			{
				if ((treeMatrix[i][j] == 1) || (treeMatrix[i][j] == 2)) lenght++;
			}
		lenght--;
		return lenght;
	}
	void printTheLength(int order) // ������� � ������� �� ����� ����� ������
	{
		int lenght = 0;
		for (int i = 0; i < Points::getMaximumY() + 1; i++)
			for (int j = 0; j < Points::getMaximumX() + 1; j++)
			{
				if ((treeMatrix[i][j] == 1) || (treeMatrix[i][j] == 2)) lenght++;
			}
		lenght--; 
		//cout <<"Length of "<< order + 1 << "tree is : " << lenght << endl;

		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}
		print << "Length of " << order + 1 << " tree is : " << lenght << endl<<endl;
		print.close();
	}
	int** getRandom()
	{
		return connection�hromosome.getRandomArray();
	}
	void changeVariantForMutant()
	{
		variant�hromosome.changeArrayForMutant();
	}
	void printRandomArray(int order)
	{
		connection�hromosome.printRandomArray(order);
	}
	void printOutArray(int order)
	{
		connection�hromosome.printOut(order);
	}
	void printVariantArray(int order)
	{
		variant�hromosome.printVariantChromosome(order);
	}
	void printOrderArray(int order)
	{
		orderChromosome.printOrderChromosome(order);
	}
	void printOutAfterArray(int order)
	{
		connection�hromosome.printOutAfter(order);
	}
	
};

class Algorythm 
{
private:

public:
	static void mainAlgorythm() // ������� ��������
	{
		unsigned long int min = 4294967000;
		unsigned long int oldmin = 4294967001;
		bool begin = true;
		int repeat = 0;
		Points::formPoints();
		//unsigned int start_time = clock();
		Species* species = new Species[30];
		while (repeat != 3) // ��� ���� repeat, ��� ������ ���������, �� ������ ����������������
		{			
			if (begin != true) Algorythm::nextGeneration();
			if (begin == true)
			{
				for (int i = 0; i < 10; i++) // 10 ���������
				{
					species[i].setConnection�hromosome(i); // ������� ��������� ����������
					species[i].setVariant�hromosome(i); // ������� ��������� �������
					species[i].setOrderChromosome(i); // ������� ��������� ������� ����������
					species[i].sortOutWithOrderArray(i); // ��������� ������ out �������� ��������� ������� ����������
					species[i].setTreeMatrix(i); // ������� �������� ������ � ������������ �� ����� �����������
					species[i].treeBuilding(i); // ������ ������ � ������� �� �����
					species[i].printTheLength(i); // ������� ����� ������ � ������� �� �����
				}
			}
			else
			{
				for (int i = 0; i < 10; i++)
				{
					species[i].printRandomArray(i);
					species[i].printOutArray(i);
					species[i].printVariantArray(i);
					species[i].printOrderArray(i);
					species[i].printOutAfterArray(i);
					species[i].treeBuilding(i); // ������ ������ � ������� �� �����
					species[i].printTheLength(i);
				}
			}
			for (int i = 10; i < 20; i++) // 10 ��������
			{
				int firstIndex = 0;
				int secondIndex = 0;
				if (i % 2 == 0) // ��� ���������� ������������� ���� �� ����������
				{
					firstIndex = i - 10;
					secondIndex = i - 9;
				}
				else if ((i % 2) != 0) // ��� ���������� ������������� ���� �� ����������
				{
					firstIndex = i - 10;
					secondIndex = i - 11;
				}
				species[i].setConnection�hromosomeForChild(i, species[firstIndex].getRandom(), species[secondIndex].getRandom());
				species[i].setVariant�hromosome(i); // ������� ��������� �������
				species[i].setOrderChromosome(i); // ������� ��������� ������� ����������
				species[i].sortOutWithOrderArray(i); // ��������� ������ out �������� ��������� ������� ����������
				species[i].setTreeMatrix(i); // ������� �������� ������ � ������������ �� ����� �����������
				species[i].treeBuilding(i); // ������ ������ � ������� �� �����
				species[i].printTheLength(i); // ������� ����� ������ � ������� �� �����
			}
			for (int i = 20; i < 30; i++) // 10 ��������
			{
				species[i] = species[i - 10];
				species[i].changeVariantForMutant(); // ������ ��������� �������
				species[i].printRandomArray(i);
				species[i].printOutArray(i);
				species[i].printVariantArray(i);
				species[i].printOrderArray(i);
				species[i].printOutAfterArray(i);
				species[i].setTreeMatrix(i); // ������� �������� ������ � ������������ �� ����� �����������
				species[i].treeBuilding(i); // ������ ������ � ������� �� �����
				species[i].printTheLength(i); // ������� ����� ������ � ������� �� �����
			}
			species = sortTenMinTrees(species);
			min = Algorythm::countAndPrintTheMinimumAndOrder(species);
			if (min == oldmin) repeat++;
			oldmin = min;
			begin = false;
			
		}
		unsigned int end_time = clock();
		//cout << "BEGIN " << start_time/1000.0 << endl;
		//cout << "END " << end_time/1000.0 << endl;
		//cout << "GENERAL " << end_time/1000.0 - start_time/1000.0 << endl;
	}
	static Species* sortTenMinTrees(Species* species) // ������� ����� ������ � 10 ������������ ���������
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}
		print << endl;
		int min = species[0].countTheLength(0);
		int treeNumber = 0;
		Species* newSpecies = new Species[30];
		for (int j = 0; j < 10; j++)
		{
			for (int i = 0; i < (30-j); i++)
			{
				if (min > species[i].countTheLength(i))
				{
					min = species[i].countTheLength(i);
					treeNumber = i;
				}
				newSpecies[j] = species[treeNumber];
			}
			Species tmp;
			tmp = species[treeNumber];
			species[treeNumber] = species[29 - j];
			species[29 - j] = tmp;
			print << "Minimal trees are " << treeNumber + 1 << " and its length is " << newSpecies[j].countTheLength(j) << endl;
			min = species[0].countTheLength(0);
			treeNumber = 0;
		}
		print << endl;
		print.close();
		return newSpecies;
		
	}
	static void startOfProgram()
	{
		ofstream print("result.txt"); // ������ � ����� �����
		if (!print.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}
		print << "--------------- START OF THE PROGRAM ---------------" << endl << endl;
		print.close();
	}
	static void nextGeneration()
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}
		print << endl << "--------------- NEXT GENERATION ---------------" << endl << endl;
		print.close();
	}
	static void endOfProgram()
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}
		print << endl << "--------------- THE END OF THE PROGRAM ---------------";
		print.close();
	}
	static unsigned long int countAndPrintTheMinimumAndOrder(Species species[30])
	{
		ofstream print("result.txt", ios_base::app); // ������ � ����� �����
		if (!print.is_open())
		{
			cout << "Error! File can't be open!" << endl;
		}
		unsigned long int min = species[0].countTheLength(0);
		int number = 0;
		for (int i = 0; i < 10; i++)
		{
			if (min > species[i].countTheLength(i))
			{
				min = species[i].countTheLength(i);
				number = i;
			}
		}
		print << "Minimal tree is " << number + 1 << " and its length is " << min << endl<<endl;
		species[number].printRandomArray(number);
		species[number].printOutArray(number);
		species[number].printVariantArray(number);
		species[number].printOrderArray(number);
		species[number].printOutAfterArray(number);
		species[number].treeBuilding(number);
		print << "Minimal tree is " << number + 1 << " and its length is " << min << endl;
		return min;
		print.close();
	}
};


int main()
{
	srand(time(0));
	setlocale(LC_ALL, "rus");
	Algorythm::startOfProgram();
	Algorythm::mainAlgorythm();
	Algorythm::endOfProgram();
	system("pause");
	return 0;
}

