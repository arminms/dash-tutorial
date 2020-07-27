#include <iostream>
#include <algorithm>
#include <random>

#include <libdash.h>

using namespace std;

int main(int argc, char* argv[])
{
    dash::init(&argc, &argv);

    dash::Array<int> arr(512);

    std::mt19937 rd(static_cast<uint>(dash::myid()));
    std::uniform_real_distribution<float> dist(0, 100);

    std::generate(arr.lbegin(), arr.lend(), [&] () { return dist(rd); });

    if (dash::myid() == 1)
    {
        for (auto val : arr)
            cout << static_cast<int>(val) << " ";
        cout << endl;
    }

    dash::finalize();
}
