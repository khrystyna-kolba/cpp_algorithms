#include<iostream>
#include<ctime>
#include<thread>
using namespace std;

void output(int** arr, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}
int** squarematrix(int& size) {
	cout << "input the size of matrix" << endl;
	cin >> size;
	int** arr = new int* [size];
	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			//arr[i][j] = rand() % 2;
			cin >> arr[i][j];
		}
	}
	return arr;

}



int main() {
	srand(time(NULL));
	int size;
	int** matrix = squarematrix(size);

	/*int** matrix = new int* [size];
	for (int i = 0; i < size; i++) {
		matrix[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cin>>matrix[i][j];
		}
	}*/


	int** arr = new int* [size];
	for (int i = 0; i < size; i++) {
		arr[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			arr[i][j] = matrix[i][j];
		}
	}
	cout << endl;
	output(matrix, size);
	cout << endl;
	//output(arr, size);
	auto start = chrono::high_resolution_clock::now();
	//this_thread::sleep_for(chrono::milliseconds(2000));
	//long way
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (arr[i][k] && arr[k][j]) {
					arr[i][j] = 1;
				}
			}
		}
		//cout << "im1" << endl;
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<long double> duration = (end - start);
	cout << "duration " << duration.count()<<"s" << endl;


	auto start1 = chrono::high_resolution_clock::now();
	//this_thread::sleep_for(chrono::milliseconds(2000));
	//faster?
	for (int k = 0; k < size; k++) {
		for (int i = 0; i < size; i++) {
			if (matrix[i][k] == 1 and i!=k) {
				for (int j = 0; j < size; j++) {
					if (matrix[k][j] == 1) {
						matrix[i][j] = 1;
					}
				}
			}
		}
		//cout << "im2" << endl;
	}
	auto end1 = chrono::high_resolution_clock::now();
	chrono::duration<long double> duration1 = (end1 - start1);
	cout << "duration " << duration.count() << "s" << endl;
	cout << "duration " << duration1.count() << "s" << endl;
	cout << endl;
	output(arr, size);
	cout << endl;
	output(matrix, size);
	for (int i = 0; i < size; i++) {
		delete[]matrix[i];
	}
	delete[]matrix;

	for (int i = 0; i < size; i++) {
		delete[]arr[i];
	}
	delete[]arr;
}