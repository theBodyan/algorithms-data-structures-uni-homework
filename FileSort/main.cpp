#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>

#define min(a, b) (a < b ? a : b)
#define fileNameSize 8
#define itemsInFile 1000

void find_minValueAndItsColumn(int** elementFromRow_itsColumn, int* minValueAndItsColumn, size_t s, int numOfElementsToPickFromFile);
bool is_file_empty(std::ifstream& pFile);
bool are_Open(std::ofstream*, size_t);
bool are_Open(std::ifstream*, size_t);
bool initializeArrayOfFiles(std::ofstream*, char** fileNames, size_t arf_size, int half);
bool initializeArrayOfFiles(std::ifstream*, char** fileNames, size_t arf_size, int half);
char* gen_random_names(size_t len = fileNameSize);
char** gen_N_random_names(int num);
void splitFile(std::ofstream* sortFilesFirstHalf, std::ifstream& originalFile, int n);
void mergeFiles(std::ifstream* inputFiles, std::ofstream* outputFiles, int n, int numOfElementsToPickFromFile);
void externalMergeSort(const char* path, size_t n);
void fillFileRandNumbers(const char* path);

int main()
{
    std::string path;
    srand(time(0));
    std::cout << "Enter the file path: " << std::endl;
    std::getline(std::cin, path);
    std::ifstream p(path.c_str());

    if (is_file_empty(p))
    {
        p.close();
        fillFileRandNumbers(path.c_str());
    }

    externalMergeSort(path.c_str(), 16);
}

void fillFileRandNumbers(const char* path)
{
    std::ofstream f(path);
    for (int i = 0; i < itemsInFile; i++)
    {
        f << rand() % 90 + 9;
        f << " ";
    }
}

// pass n/2 as s
void find_minValueAndItsColumn(int** elementFromRow_itsColumn, int* minValueAndItsColumn, size_t s, int numOfElementsToPickFromFile)
{
    for (int i = 0; i < s; i++)
    {
        if (elementFromRow_itsColumn[1][i] < numOfElementsToPickFromFile)
        {
            minValueAndItsColumn[0] = elementFromRow_itsColumn[0][i];
            minValueAndItsColumn[1] = i;
            i = s;
        }
    }
    for (int i = 0; i < s; i++)
    {
        if (minValueAndItsColumn[0] > elementFromRow_itsColumn[0][i] && elementFromRow_itsColumn[1][i] < (numOfElementsToPickFromFile)) // 2nd cond s.t. we don't exceed the range
        {
            minValueAndItsColumn[0] = elementFromRow_itsColumn[0][i];
            minValueAndItsColumn[1] = i;
        }
    }
    elementFromRow_itsColumn[1][minValueAndItsColumn[1]] += 1;
}

bool is_file_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

bool initializeArrayOfFiles(std::ofstream* arf, char** fileNames, size_t arf_size, int half) // arf = array of files
{
    if (half == 1)
    {
        for (int i = 0; i < arf_size; i++)
        {
            arf[i].open(fileNames[i]);
        }
    }
    else if (half == 2)
    {
        for (int i = 0; i < arf_size; i++)
        {
            arf[i].open(fileNames[arf_size + i]);
        }
    }
    else
    {
        std::cout << "Half can be either 1 or 2. Your value of half is: " << half << " . Bye!" << std::endl;
        return 0;
    }
    return are_Open(arf, arf_size);
}

bool initializeArrayOfFiles(std::ifstream* arf, char** fileNames, size_t arf_size, int half)
{
    if (half == 1)
    {
        for (int i = 0; i < arf_size; i++)
        {
            arf[i].open(fileNames[i]);
        }
    }
    else if (half == 2)
    {
        for (int i = 0; i < arf_size; i++)
        {
            arf[i].open(fileNames[arf_size + i]);
        }
    }
    else
    {
        std::cout << "Half can be either 1 or 2. Your value of half is: " << half << " . Bye!" << std::endl;
        return 0;
    }
    return are_Open(arf, arf_size);
}

bool are_Open(std::ofstream* arf, size_t arf_size) // check if files have opened
{
    for (int i = 0; i < arf_size; i++)
    {
        if (!(arf[i].is_open()))
        {
            return false;
        }
    }
    return true;
}

bool are_Open(std::ifstream* arf, size_t arf_size) // check if files have opened
{
    for (int i = 0; i < arf_size; i++)
    {
        if (!(arf[i].is_open()))
        {
            return false;
        }
    }
    return true;
}

void externalMergeSort(const char* path, size_t n) // n = 2*k, i.e. an even number.
{
    std::ifstream originalFile(path, std::ios_base::in);
    bool secondSortFileEmpty = false;
    bool filesInitialized = true;
    int loopCounter, numOfElementsToPickFromFile;
    numOfElementsToPickFromFile = 1;
    loopCounter = 0;

    char** fileNames = gen_N_random_names(n);
    std::ofstream* sortFilesFirstHalf = new std::ofstream[n / 2];

    (initializeArrayOfFiles(sortFilesFirstHalf, fileNames, n / 2, 1) == true ? filesInitialized= true : filesInitialized= false);
    if (!filesInitialized)
    {
        return;
    }

    splitFile(sortFilesFirstHalf, originalFile, n);

    delete[] sortFilesFirstHalf;

    while (!secondSortFileEmpty)
    {
        if (!(loopCounter % 2))
        {
            std::ifstream* sortFilesFirstHalf = new std::ifstream[n / 2];
            std::ofstream* sortFilesSecondHalf = new std::ofstream[n / 2];
            (initializeArrayOfFiles(sortFilesFirstHalf, fileNames, n / 2, 1) == true ? filesInitialized= true : filesInitialized= false);
            (initializeArrayOfFiles(sortFilesSecondHalf, fileNames, n / 2, 2) == true ? filesInitialized= true : filesInitialized= false);
            if (!filesInitialized)
            {
                return;
            }
            if (is_file_empty(sortFilesFirstHalf[1]))
            {
                secondSortFileEmpty = true;
            }

            mergeFiles(sortFilesFirstHalf, sortFilesSecondHalf, n, numOfElementsToPickFromFile);


            delete[] sortFilesFirstHalf;
            delete[] sortFilesSecondHalf;
        }
        else
        {
            std::ofstream* sortFilesFirstHalf = new std::ofstream[n / 2];
            std::ifstream* sortFilesSecondHalf = new std::ifstream[n / 2];
            (initializeArrayOfFiles(sortFilesFirstHalf, fileNames, n / 2, 1) == true ? filesInitialized= true : filesInitialized= false);
            (initializeArrayOfFiles(sortFilesSecondHalf, fileNames, n / 2, 2) == true ? filesInitialized= true : filesInitialized= false);
            if (!filesInitialized)
            {
                return;
            }
            if (is_file_empty(sortFilesSecondHalf[1]))
            {
                secondSortFileEmpty = true;
            }

            mergeFiles(sortFilesSecondHalf, sortFilesFirstHalf, n, numOfElementsToPickFromFile);

            delete[] sortFilesFirstHalf;
            delete[] sortFilesSecondHalf;
        }
        // update vars at the end of each iteration


        loopCounter++;
        numOfElementsToPickFromFile *= n / 2;
    }

    if (!(loopCounter % 2))
    {
        (std::rename(fileNames[n / 2], "Final.txt") == 0 ? std::cout << "Done!" << std::endl : std::cout << "An unprecedented error occured");
        for (int i = 0; i < n; i++)
        {
            if (i != n / 2)
            {
                (std::remove(fileNames[i]) == 0 ? std::cout << "Deleted." << std::endl : std::cout << "An unprecedented error occured during file deletion.");
            }
        }
    }
    else if (loopCounter % 2)
    {
        (std::rename(fileNames[0], "Final.txt") == 0 ? std::cout << "Done!" << std::endl : std::cout << "An unprecedented error occured");
        for (int i = 1; i < n; i++)
        {
            (std::remove(fileNames[i]) == 0 ? std::cout << "Deleted." << std::endl : std::cout << "An unprecedented error occured during file deletion.");
        }
    }

    for (int i = 0; i < n; i++)
    {
        delete[] fileNames[i];
    }
    delete[] fileNames;
}

void splitFile(std::ofstream* sortFilesFirstHalf, std::ifstream& originalFile, int n)
{
  for (int i = 0, a; !originalFile.eof(); i++)
  {
    if (originalFile >> a)
    {
      sortFilesFirstHalf[i % (n / 2)] << a << ' ';
    }
  }
}

void mergeFiles(std::ifstream* inputFiles, std::ofstream* outputFiles, int n, int numOfElementsToPickFromFile)
{
  /*
  each iteration we read ((n/2)^loopCounter) elements from each of n/2 files
  therefore, the set of elements for reading can be represented by a (n/2)x((n/2)^loopCounter) matrix.
  that's where the terminology of rows/columns comes from.
  */
  int** elementFromRow_itsColumn = new int* [2];
  int minValueAndItsColumn[2];
  elementFromRow_itsColumn[0] = new int[n / 2];
  elementFromRow_itsColumn[1] = new int[n / 2];

  int eof_count = 0;
  int g = 0; // counts iterations
  while (eof_count < n / 2)
  {
      for (int j = 0; j < (n / 2) * numOfElementsToPickFromFile && eof_count < n / 2; j++)
      {
          if (!j)
          {
              for (int i = 0; i < n / 2 && g == 0; i++)
              {
                  inputFiles[i] >> elementFromRow_itsColumn[0][i];
                  elementFromRow_itsColumn[1][i] = 0;
              }
          }
          find_minValueAndItsColumn(elementFromRow_itsColumn, minValueAndItsColumn, n / 2, numOfElementsToPickFromFile);
          outputFiles[g % (n / 2)] << minValueAndItsColumn[0];
          outputFiles[g % (n / 2)] << " ";
          if (inputFiles[minValueAndItsColumn[1]] >> elementFromRow_itsColumn[0][minValueAndItsColumn[1]]) {}
          else
          {
              j += (numOfElementsToPickFromFile - elementFromRow_itsColumn[1][minValueAndItsColumn[1]]);
              eof_count += 1;
              elementFromRow_itsColumn[1][minValueAndItsColumn[1]] = numOfElementsToPickFromFile + 1;
          }
      }
      for (int i = 0; i < n / 2; i++)
      {
          if (elementFromRow_itsColumn[1][i] != numOfElementsToPickFromFile + 1)
          {
              elementFromRow_itsColumn[1][i] = 0;
          }
      }
      g++;
  }
  delete[] elementFromRow_itsColumn[0];
  delete[] elementFromRow_itsColumn[1];
  delete[] elementFromRow_itsColumn;
}

char* gen_random_names(size_t len)
{
    char* s = new char[len + 1];
    for (size_t i = 1; i < len - 4; i++)
    {
        int randomChar = rand() % (26 + 26 + 10);
        if (randomChar < 26)
            s[i] = 'a' + randomChar;
        else if (randomChar < 26 + 26)
            s[i] = 'A' + randomChar - 26;
        else
            s[i] = '0' + randomChar - 26 - 26;
    }
    s[0] = 'f';
    s[len - 4] = '.';
    s[len - 3] = 't';
    s[len - 2] = 'x';
    s[len - 1] = 't';
    s[len] = 0;
    return s;
}

char** gen_N_random_names(int num)
{
    char** n_names = new char*[num];
    for (int i = 0; i < num; i++)
    {
        n_names[i] = gen_random_names();
    }
    return n_names;
}
