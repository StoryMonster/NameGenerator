#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>

std::vector<std::string> readFromFile(const std::string& filename)
{
    std::vector<std::string> names{};
    std::ifstream in(filename, std::ios_base::in);
    if (in.is_open())
    {
        //std::string name{};
        char txt[256] = {0};
        while (!in.eof())
        {
            //std::getline(in, name);
            in.getline(txt, 256);
            std::string name{txt};
            name.erase(std::remove(name.begin(), name.end(), '\r'), name.end());
            name.erase(std::remove(name.begin(), name.end(), '\n'), name.end());
            if (name.size() > 0)
            {
                names.push_back(name);   
            }
        }
        in.close();
    }
    return names;
}

std::string generateName()
{
    const std::string firstNameFile = "Resources/first_name.dat";
    const std::string lastNameFile = "Resources/last_name.dat";
    std::vector<std::string> lastNames = readFromFile(lastNameFile);
    std::vector<std::string> firstNames = readFromFile(firstNameFile);
    if (lastNames.empty() || firstNames.empty())
    {
        std::cout << "Some thing error in file " << firstNameFile << " or " << lastNameFile << std::endl;
        exit(-1);
    }

    std::random_device rd;
    std::default_random_engine e(rd());
    std::uniform_int_distribution<std::int32_t> distFirstName(0, firstNames.size()-1);
    std::uniform_int_distribution<std::int32_t> distLastName(0, lastNames.size()-1);
    return lastNames.at(distLastName(e)) + firstNames.at(distFirstName(e));
}


int main()
{
    std::cout << generateName() << std::endl;
}