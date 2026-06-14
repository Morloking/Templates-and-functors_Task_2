#include <iostream>
#include <exception>


template <class T>
class MainArray {
public:
	MainArray(int rows, int columns) :
		rows(rows),
		columns(columns),
		sizeArr(rows*columns),
		data(new T[sizeArr])
	{};
	//non const Subclass start
	class SubArray {

	public:
		SubArray(MainArray& mainArr, size_t row) :
			mainArr(mainArr),
			row(row)
		{};


		//second []
		T& operator[](size_t column) {
			if (column >= mainArr.columns) {
				throw std::runtime_error("Invalid column index");
			}
			int linearFinalIndex = row * mainArr.columns + column;
			return mainArr.data[linearFinalIndex];
		}
		
	private:
		MainArray& mainArr;
		size_t row;
	};
	// non const Subclass end

	// const Subclass start
	class ConstSubArray {
	public:
		ConstSubArray(const MainArray& mainArr, size_t row) :
			mainArr(mainArr),
			row(row)
		{};

		const T& operator[](size_t column) const {
			if (column >= mainArr.columns) {
				throw std::runtime_error("Invalid column index");
			}
			int linearFinalIndex = row * mainArr.columns + column;
			return mainArr.data[linearFinalIndex];
		}

	private:
		const MainArray& mainArr;
		size_t row;
	};

	// const Subclass end
	
	//first []
	const ConstSubArray operator[](size_t row) const {
		if (row >= rows) {
			throw std::runtime_error("Invalid row index");
		}
		return ConstSubArray(*this, row);
	}
	SubArray operator[](size_t row) {
		if (row >= rows) {
			throw std::runtime_error("Invalid row index");
		}
		return SubArray(*this, row);
	}

	size_t size() const {
		return sizeArr;
	}

	~MainArray() {
		delete[] data;
	};

private:
	int rows,
		columns;
	size_t sizeArr;
	T* data;
};


int main() {
	MainArray <int> arr(2,2);
	//test
	auto test = MainArray<int>(2, 3);
	test[0][0] = 4;
	std::cout << test[0][0]; // выводит 4
	return 0;
}