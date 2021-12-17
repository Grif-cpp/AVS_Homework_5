#include<iostream>
#include<fstream>
#include<thread>
#include"Country.h"
#include<cstring>
#include <mutex>

int main(int argc, char* argv[]) {
	clock_t start = clock();
    std::cout << "Start" << std::endl;
    std::string s;
    Country c1, c2;
    if (!strcmp(argv[1], "-f")) {
        std::ifstream ifst(argv[2]);
        c1.Field_in(ifst);
        c2.Field_in(ifst);
        s = argv[3];
    } else if (!strcmp(argv[1], "-n")) {
        c1.Random_field(atoi(argv[2]) , atoi(argv[3]));
        c2.Random_field(atoi(argv[4]), atoi(argv[5]));
        s = argv[6];
    }
    std::ofstream ofst(s);
    //
    //НАЧАТЬ ОБСТРЕЛ
    std::thread th1;
    std::thread th2;
    
    c1.Count_country_value();
    c2.Count_country_value();

    std::pair<int, int> point1, point2;
    while(c1.is_able_to_shoot && c2.is_able_to_shoot) {
        std::thread th1(&Country::Aim, c1, &c2, &point1);
        std::thread th2(&Country::Aim, c2, &c1, &point2);
        th1.join();
        th2.join();
        std::thread th3(&Country::Shoot, c1, &c2, point1);
        std::thread th4(&Country::Shoot, c2, &c1, point2);
        th3.join();
        th4.join();
    }
    // Конец обстрела
    ofst << "Country1:" << std::endl;
    c1.Out(ofst);
    ofst << std::endl;
    ofst << "Country2:" << std::endl;
    c2.Out(ofst);
    //
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << seconds << std::endl;
    return 0;
}