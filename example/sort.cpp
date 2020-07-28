#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <cmath>

#include <libdash.h>

using namespace std;

int main(int argc, char* argv[])
{
    int N = 512;

    dash::init(&argc, &argv);

    if (argc > 1)
        N = stoi(argv[1]);

    dash::Array<int> arr(N);

    std::mt19937 rd(static_cast<uint>(dash::myid()));
    // std::uniform_real_distribution<float> dist(0, 1);
    std::uniform_int_distribution<int> dist(0, 100);

    dash::generate(arr.begin(), arr.end(), [&] () { return dist(rd); });
    dash::sort(arr.begin(), arr.end());

    if (dash::myid() == 1)
    {
        int color = 9;
        cout << "N = " << N << ", Number of Processes = " << dash::size();
        for (size_t i = 0; i < arr.size(); ++i)
        {
            if (0 == i % size_t(ceil(float(N) / float(dash::size()))))
                cout << "\033[38;5;" << color++ << "m" << endl;
            cout << setw(4)
                 << static_cast<int>(arr[i]);
        }
        cout << "\033[0m" << endl;
    }

    dash::finalize();
}
