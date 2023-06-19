#include <iostream>
#include <fstream>
#include <string>

struct scan_info
{
    std::string model; // наименование модели
    int price; // цена
    double x_size; // горизонтальный размер области сканирования
    double y_size; // вертикальный размер области сканирования
    int optr; // оптическое разрешение
    int grey; // число градаций серого
};

void writeToFile(scan_info* info, int n)
{
    std::ofstream fout("scan_info.txt", std::ios::out | std::ios::binary);
    fout.write((char*)&n, sizeof(int));
    for (size_t i = 0; i < n; i++)
    {
        fout.write((char*)&info[i].price, sizeof(int));
        fout.write((char*)&info[i].x_size, sizeof(double));
        fout.write((char*)&info[i].y_size, sizeof(double));
        fout.write((char*)&info[i].optr, sizeof(int));
        fout.write((char*)&info[i].grey, sizeof(int));
        fout.write(info[i].model.c_str(), info[i].model.size() + 1);
    }
    fout.close();
}

void readFile(scan_info*& info, int& n)
{
    std::ifstream fin("scan_info.txt", std::ios::in | std::ios::binary);

    if (fin.is_open())
    {
        fin.read((char*)&n, sizeof(int));
        info = new scan_info[n];

        char* readByte = new char;
        for (int i = 0; i < n; i++)
        {
            fin.read((char*)&info[i].price, sizeof(int));
            fin.read((char*)&info[i].x_size, sizeof(double));
            fin.read((char*)&info[i].y_size, sizeof(double));
            fin.read((char*)&info[i].optr, sizeof(int));
            fin.read((char*)&info[i].grey, sizeof(int));

            *readByte = 1;
            while (*readByte != 0)
            {
                fin.read(readByte, 1);
                if (*readByte != 0)
                    info[i].model += *readByte;
            }
        }
        delete readByte;
    }
    else
    {
        info = nullptr;
        n = 0;
    }
    fin.close();
}

short replaceInfo(scan_info* info, int n, int i, scan_info new_info)
{
    if (0 <= i && i < n)
    {
        info[i] = new_info;
        return 0;
    }
    else
        return -1;
}

void dialog1()
{
    std::cout << "Enter Count: ";
    int n;
    if ((std::cin >> n))
    {
        if (n >= 6)
        {
            scan_info* scans = new scan_info[n];
            for (size_t i = 0; i < n;)
            {
                std::cin.ignore(INT_MAX, '\n');
                std::cout << "Enter Model: ";
                std::getline(std::cin, scans[i].model);
                std::cout << "Enter Info (price, x_size, y_size, optr, grey): ";
                if ((std::cin >> scans[i].price >> scans[i].x_size >> scans[i].y_size >> scans[i].optr >> scans[i].grey))
                    i++;
                else
                    std::cout << "Incorrect input!" << std::endl;
                std::cout << std::endl;
            }
            writeToFile(scans, n);
            delete[] scans;
        }
        else
            std::cout << "Count must be greater than or equal to 6." << std::endl;
    }
}

void dialog2()
{
    int n;
    scan_info* scans;
    readFile(scans, n);

    std::cout.width(2);
    std::cout << "id";
    std::cout.width(10);
    std::cout << "model";
    std::cout.width(10);
    std::cout << "price";
    std::cout.width(10);
    std::cout << "x_size";
    std::cout.width(10);
    std::cout << "y_size";
    std::cout.width(10);
    std::cout << "optr";
    std::cout.width(10);
    std::cout << "grey" << std::endl;;
    for (size_t i = 0; i < n; i++)
    {
        std::cout.width(2);
        std::cout << i;
        std::cout.width(10);
        std::cout << scans[i].model;
        std::cout.width(10);
        std::cout << scans[i].price;
        std::cout.width(10);
        std::cout << scans[i].x_size;
        std::cout.width(10);
        std::cout << scans[i].y_size;
        std::cout.width(10);
        std::cout << scans[i].optr;
        std::cout.width(10);
        std::cout << scans[i].grey << std::endl;;
    }

    std::cout << "\nEnter Id: ";
    int id;
    if ((std::cin >> id))
    {
        scan_info new_info;
        std::cin.ignore(INT_MAX, '\n');
        std::cout << "Enter Model: ";
        std::getline(std::cin, new_info.model);
        std::cout << "Enter Info (price, x_size, y_size, optr, grey): ";
        if ((std::cin >> new_info.price >> new_info.x_size >> new_info.y_size >> new_info.optr >> new_info.grey))
        {
            if (replaceInfo(scans, n, id, new_info) == 0)
            {
                std::cout << "Success!" << std::endl;
                writeToFile(scans, n);
            }
            else
                std::cout << "Fail!" << std::endl;
        }
        else
            std::cout << "Incorrect input!" << std::endl;
    }
    else
        std::cout << "Incorrect input!" << std::endl;

    delete[] scans;
}


int main()
{
    std::cout << "1. Enter scan info\n2. Raplce scan info\n\n>> ";
    int d;
    if ((std::cin >> d))
    {
        if (d == 1)
        {
            std::cout << std::endl;
            dialog1();
        }
        else if (d == 2)
        {
            std::cout << std::endl;
            dialog2();
        }
        else
            std::cout << "Unknown dialog!" << std::endl;
    }
    else
        std::cout << "Incorrect input!" << std::endl;;

    return 0;
}
