#include <iostream>
#include <string>
#include <cmath>

#include <libdash.h>

using namespace std;

int main(int argc, char* argv[])
{
    int N = 100;

    dash::init(&argc, &argv);

    if (argc > 1)
        N = stoi(argv[1]);

    dash::Array<int> arr(N);
    auto myid = dash::myid();

    if (dash::myid() == 0)
        for(auto i = 0; i < arr.size(); ++i)
            arr[i] = i;
    arr.barrier();

    if (dash::myid() == 0)
    {
        int color = 9;
        cout << "N = " << N << ", Number of Units = " << dash::size();
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
