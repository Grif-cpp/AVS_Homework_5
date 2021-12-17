#include"Country.h"
#include<iostream>
#include <mutex>
#include <fstream>

void Country::Field_in(std::ifstream& f) {
    f >> width_ >> height_;
    field.resize(height_);
    for (int i = 0; i < height_; i++) {
        field[i].resize(width_);
        for (int j = 0; j < width_; j++) {
            f >> field[i][j];
        }
    }
}

void Country::Random_field(int height, int width) {
    width_ = width;
    height_ = height;
    field.resize(height_);
    for (int i = 0; i < height_; i++) {
        field[i].resize(width_);
        for (int j = 0; j < width_; j++) {
            field[i][j] = rand() % 1000;
        }
    }
}

void Country::Count_country_value() {
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            country_value += field[i][j];
        }
    }
}

void Country::Aim(Country *country, std::pair<int, int> *point) {
    while (true) {
        int x = rand() % country->height_;
        int y = rand() % country->width_;
        if (country->field[x][y] != -1) {
            *point = std::make_pair(x, y);
            break;
        }
    }
}

void Country::Shoot(Country *country, std::pair<int,int> point) {
    mutex_.lock();
    ammo_balance += ammo_cost;
    
    damage_balance += country->field[point.first][point.second];
    country->field[point.first][point.second] = -1;
    if (damage_balance >= country->country_value || ammo_balance >= country->country_value) {
        is_able_to_shoot = false;
    }
    mutex_.unlock();
}

void Country::Out(std::ofstream& f) {
    f << "Ammo_balance: " << ammo_balance << "    ";
    f << "Damage_balance: " << damage_balance << std::endl;
}