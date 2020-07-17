#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
using vs = std::vector<std::string>;

using vi = std::vector<int>;

std::vector<vi> vs_to_vi(const std::vector<vs>& ip_pool_vs)
{

    std::vector<vi> ip_pool_vi(ip_pool_vs.size(), vi(ip_pool_vs.at(0).size()));
    auto ip_vs = ip_pool_vs.begin();
    auto ip_vi = ip_pool_vi.begin();
    for (; ip_vs != ip_pool_vs.end(); ++ip_vs, ++ip_vi) {

        auto ip_s = (*ip_vs).begin();
        auto ip_i = (*ip_vi).begin();

        for (; ip_s != (*ip_vs).end(); ++ip_s, ++ip_i)
            *ip_i = std::stoi(*ip_s);
    }
    return ip_pool_vi;
}

vs split(const std::string& str, char d)
{
    vs r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void ip_separate(std::vector<vs>& ip_pool)
{

    for (std::string line; std::getline(std::cin, line);) {
        vs v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }
}

void ip_print(const std::vector<vi>& ip_pool)
{
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip) {
        for (vi::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
            if (ip_part != ip->cbegin()) {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

void ip_sort(std::vector<vi>& ip_pool)
{
    std::sort(ip_pool.rbegin(), ip_pool.rend());
}

std::vector<vi> filter_any(const std::vector<vi>& ip_pool, int ip_1)
{
    std::vector<vi> ip_filtered(ip_pool.size(), vi(ip_pool.at(0).size(), {}));
    auto it = std::copy_if(ip_pool.cbegin(), ip_pool.cend(), ip_filtered.begin(), [ip_1](vi ip) {
        return std::any_of(ip.begin(), ip.end(), [=](int i) { return i == ip_1; });
    });

    ip_filtered.resize(std::distance(ip_filtered.begin(), it));
    return ip_filtered;
}

std::vector<vi> filter(const std::vector<vi>& ip_pool, int ip_1, int ip_2)
{

    std::vector<vi> ip_filtered(ip_pool.size(), vi(ip_pool.at(0).size()), {});
    auto it = std::copy_if(ip_pool.cbegin(), ip_pool.cend(), ip_filtered.begin(), [ip_1, ip_2](vi ip) {
        return ip.at(0) == ip_1 && ip.at(1) == ip_2;
    });

    ip_filtered.resize(std::distance(ip_filtered.begin(), it));
    return ip_filtered;
}

int main()
{
    try {

        std::vector<vi> ip_pool;
        {

            std::vector<vs> ip_pool_vs;
            ip_separate(ip_pool_vs);
            ip_pool = vs_to_vi(ip_pool_vs);
        }

        std::vector<vi> ip_res;

        // TODO reverse lexicographically sort

        ip_sort(ip_pool);
        std::copy(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_res));
        //        ip_print(ip_pool);
        // TODO filter by first byte and output
        {

            auto filter = [=](const std::vector<vi>& ip_pool, int ip_1) {
                std::vector<vi> ip_filtered(ip_pool.size(), vi(ip_pool.at(0).size(), {}));
                auto it = std::copy_if(ip_pool.cbegin(), ip_pool.cend(), ip_filtered.begin(), [ip_1](vi ip) {
                    return ip.at(0) == ip_1;
                });

                ip_filtered.resize(std::distance(ip_filtered.begin(), it));
                return ip_filtered;
            };

            int i_filter = 1;
            auto ip = filter(ip_pool, i_filter);
            std::copy(ip.begin(), ip.end(), std::back_inserter(ip_res));
        }

        // TODO filter by first and second bytes and output

        {
            int i_filter1 = 46, i_filter2 = 70;

            auto ip = filter(ip_pool, i_filter1, i_filter2);
            std::copy(ip.begin(), ip.end(), std::back_inserter(ip_res));
        }

        // TODO filter by any byte and output
        {
            int i_filter = 46;

            auto ip = filter_any(ip_pool, i_filter);
            std::copy(ip.begin(), ip.end(), std::back_inserter(ip_res));
        }
        ip_print(ip_res);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
