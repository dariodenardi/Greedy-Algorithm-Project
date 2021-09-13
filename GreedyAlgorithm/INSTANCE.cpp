#include "INSTANCE.h"

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
void addItemInClass(int r, int n, int class_gen, int item, int * indexes, int * classes);

int readInstance(char *file_name, int& n, int& m, int& r, int * &weights, int * &capacities, int * &profits, int * &classes, int * &indexes, int * &setups, int * &b) {

	char path[200];
	strcpy(path, "./instances/");
	strcat(path, file_name);

	const char delim = '\t';
	bool nFind = false;
	bool mFind = false;
	bool rFind = false;
	bool weightsFind = false;
	bool capacitiesFind = false;
	bool profitsFind = false;
	bool classesFind = false;
	bool setupsFind = false;
	bool bFind = false;
	int nCheck = 0;
	int mCheck = 0;
	int rCheck = 0;

	std::ifstream file(path);
	if (file.is_open()) {
		std::string line;
		getline(file, line); // read first line
		while (getline(file, line)) {

			std::vector<std::string> out;
			tokenize(line, delim, out);
			
			if (strcmp("j items", out[0].c_str()) == 0) {
				n = strtol(out[1].c_str(), NULL, 10);
				nFind = true;
				classes = (int *)malloc(sizeof(int) * n);
				weights = (int *)malloc(sizeof(int) * n);
				if (mFind && nFind)
					profits = (int *)malloc(sizeof(int) * n * m);
			}
			else if (strcmp("k knapsacks", out[0].c_str()) == 0) {
				m = strtol(out[1].c_str(), NULL, 10);
				mFind = true;
				capacities = (int *)malloc(sizeof(int) * m);
				if (mFind && nFind)
					profits = (int *)malloc(sizeof(int) * n * m);
			}
			else if (strcmp("r classes", out[0].c_str()) == 0) {
				r = strtol(out[1].c_str(), NULL, 10);
				rFind = true;
				b = (int *)malloc(sizeof(int) * r);
				setups = (int *)malloc(sizeof(int) * r);
				indexes = (int *)malloc(sizeof(int) * r);
			}
			else if (strcmp("parameter w(j)", out[0].c_str()) == 0 && nFind) {

				while (getline(file, line) && strcmp(line.c_str(), "") != 0) {
					std::vector<std::string> out2;
					tokenize(line, delim, out2);

					weights[nCheck++] = strtol(out2[1].c_str(), NULL, 10);

					if (nCheck != strtol(out2[0].c_str(), NULL, 10))
						return 2;
				}

				// check if the number of read is correct
				if (nCheck != n)
					return 3;

				weightsFind = true;
			}
			else if (strcmp("parameter cap(i)", out[0].c_str()) == 0 && mFind) {

				while (getline(file, line) && strcmp(line.c_str(), "") != 0) {
					std::vector<std::string> out2;
					tokenize(line, delim, out2);

					capacities[mCheck++] = strtol(out2[1].c_str(), NULL, 10);

					if (mCheck != strtol(out2[0].c_str(), NULL, 10))
						return 2;
				}

				// check if the number of read is correct
				if (mCheck != m)
					return 3;

				capacitiesFind = true;
			}
			else if (strcmp("parameter p(i, j)", out[0].c_str()) == 0 && mFind && nFind) {
				
				nCheck = 0;
				mCheck = 0;
				while (getline(file, line) && strcmp(line.c_str(), "") != 0) {
					std::vector<std::string> out2;
					tokenize(line, delim, out2);

					profits[nCheck++ + mCheck*n] = strtol(out2[2].c_str(), NULL, 10);

					if (nCheck != strtol(out2[0].c_str(), NULL, 10))
						return 2;
					if (mCheck+1 != strtol(out2[1].c_str(), NULL, 10))
						return 2;

					if (nCheck == n && (mCheck+1) != m) {
						nCheck = 0;
						mCheck++;
					}
				}

				// check if the number of read is correct
				if (nCheck * (mCheck+1) != n*m)
					return 3;

				profitsFind = true;
			}
			else if (strcmp("parameter t(r,j)", out[0].c_str()) == 0 && nFind && rFind) {

				// initializate array
				for (int i = 0; i < r; i++) {
					classes[i] = -1;
					indexes[i] = i + 1;
				}

				nCheck = 0;
				while (getline(file, line) && strcmp(line.c_str(), "") != 0) {
					std::vector<std::string> out2;
					tokenize(line, delim, out2);

					addItemInClass(r, n, strtol(out2[1].c_str(), NULL, 10), nCheck, indexes, classes);
					nCheck++;

					if (nCheck != strtol(out2[0].c_str(), NULL, 10))
						return 2;
				}

				// check if class have at least one element
				for (int i = 0; i < r; i++) {
					if (classes[i] == -1)
						return 4;
				}

				// check if the number of read is correct
				if (nCheck != n)
					return 3;

				classesFind = true;
			}
			else if (strcmp("parameter s(r)", out[0].c_str()) == 0 && rFind) {

				while (getline(file, line) && strcmp(line.c_str(), "") != 0) {
					std::vector<std::string> out2;
					tokenize(line, delim, out2);

					setups[rCheck++] = strtol(out2[1].c_str(), NULL, 10);

					if (rCheck != strtol(out2[0].c_str(), NULL, 10))
						return 2;
				}

				// check if the number of read is correct
				if (rCheck != r)
					return 3;

				setupsFind = true;
			}
			else if (strcmp("parameter b(k)", out[0].c_str()) == 0 && rFind) {

				rCheck = 0;
				while (getline(file, line) && strcmp(line.c_str(), "") != 0) {
					std::vector<std::string> out2;
					tokenize(line, delim, out2);

					b[rCheck++] = strtol(out2[1].c_str(), NULL, 10);

					if (rCheck != strtol(out2[0].c_str(), NULL, 10))
						return 2;
				}

				// check if the number of read is correct
				if (rCheck != r)
					return 3;

				bFind = true;
			}

		} // while getline
		file.close();
	}
	else {
		std::cout << "Parameters: " << std::endl;
	}

	if (!nFind || !mFind || !rFind || !weightsFind || !capacitiesFind || !profitsFind || !classesFind || !setupsFind || !bFind)
		return 1;

	return 0;
}

void tokenize(std::string const &str, const char delim, std::vector<std::string> &out)
{
	size_t start;
	size_t end = 0;

	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

void addItemInClass(int r, int n, int class_gen, int item, int * indexes, int * classes) {

	for (int i = 0; i < r; i++) {

		// find the class
		if (i + 1 == class_gen) {
			// move an element forward (only if there is just an element)
			if (classes[indexes[i] - 1] == -1) {
				classes[indexes[i] - 1] = item;
			}
			else {
				for (int j = n - 1; j > indexes[i]; j--) {
					classes[j] = classes[j - 1];
				}

				classes[indexes[i]] = item;

				// update indexes
				for (int j = i; j < r; j++) {
					indexes[j] += 1;
				}
			}

			
		}

	} // for r

}

void printInstance(int n, int m, int r, int weights[], int capacities[], int profits[], int classes[], int indexes[], int setups[], int b[]) {
	std::cout << "Instance value:" << std::endl;

	std::cout << "j\t" << "i\t" << "p(i,j)\t" << "w(i)\t" << "class" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			std::cout << j + 1 << "\t" << i + 1 << "\t" << profits[j + i * n] << "\t" << weights[j] << "\t" << findClass(j, classes, indexes, r) + 1 << std::endl;
	std::cout << std::endl;

	if (capacities != NULL) {
		std::cout << "c(i)" << std::endl;
		for (int i = 0; i < m; i++)
			std::cout << capacities[i] << std::endl;
		std::cout << std::endl;
	}

	if (setups != NULL) {
		std::cout << "s(k)" << std::endl;
		for (int i = 0; i < r; i++)
			std::cout << setups[i] << std::endl;
		std::cout << std::endl;
	}

	if (b != NULL) {
		std::cout << "b(k)" << std::endl;
		for (int i = 0; i < r; i++)
			std::cout << b[i] << std::endl;
		std::cout << std::endl;
	}
}

void printInstance(int n, int m, int r, int weights[], int capacities[], int profits[], int itemKnapsack[], int itemIndex[], int classes[], int indexes[], int setups[], int b[]) {
	std::cout << "Instance value:" << std::endl;

	std::cout << "j\t" << "i\t" << "p(i,j)\t" << "w(i)\t" << "class" << std::endl;
	std::cout << "----------------------------------------" << std::endl;
	for (int j = 0; j < n; j++)
			std::cout << itemIndex[j] + 1 << "\t" << itemKnapsack[j] + 1 << "\t" << profits[j] << "\t" << weights[j] << "\t" << findClass(itemIndex[j], classes, indexes, r) + 1 << std::endl;
	std::cout << std::endl;

	if (capacities != NULL) {
		std::cout << "c(i)" << std::endl;
		for (int i = 0; i < m; i++)
			std::cout << capacities[i] << std::endl;
		std::cout << std::endl;
	}

	if (setups != NULL) {
		std::cout << "s(k)" << std::endl;
		for (int i = 0; i < r; i++)
			std::cout << setups[i] << std::endl;
		std::cout << std::endl;
	}

	if (b != NULL) {
		std::cout << "b(k)" << std::endl;
		for (int i = 0; i < r; i++)
			std::cout << b[i] << std::endl;
		std::cout << std::endl;
	}
}