#include <iostream>

#include <libdash.h>

using namespace std;

int main(int argc, char* argv[])
{
    dash::init(&argc, &argv);

    dash::Array<int> arr(512);
    auto myid = dash::myid();

    for(auto i = 0; i < arr.lsize(); ++i)
        arr.local[i] = dash::myid();

    arr.barrier();

    if (dash::myid() == 0)
    {
        for (auto val : arr)
            cout << static_cast<int>(val) << " ";
        cout << endl;
    }

    dash::finalize();
}
