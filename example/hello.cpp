#include <iostream>
#include <libdash.h>

using namespace std;

int main(int argc, char* argv[])
{
    pid_t pid; char buf[100];
    dash::init(&argc, &argv);

    auto myid = dash::myid();
    auto size = dash::size();
    gethostname(buf, 100); pid = getpid();

    cout << "\033[38;5;" << dash::myid() + 9 << "m"
         << "'Hello world' from unit "
         << myid
         << " of "
         << size
         << " on "
         << buf
         << " pid="
         << pid
         << "\033[0m"
         << endl;

    dash::finalize();
}
