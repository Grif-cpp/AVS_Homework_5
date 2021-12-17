#include <mutex>
#include <vector>
class Country {
public:
    void Field_in(std::ifstream& f);

    void Random_field(int height, int width);

    void Count_country_value();

    void Aim(Country* country, std::pair<int, int>* point);

    void Shoot(Country* country, std::pair<int, int> point);

    void Out(std::ofstream& f);

    bool is_able_to_shoot = true;
    size_t country_value = 0;
    std::vector<std::vector<int>> field;

private:
    std::mutex mutex_;
    int width_ = 0;
    int height_ = 0;
    int damage_balance = 0;
    int ammo_balance = 0;
    static const int ammo_cost = 5;
};