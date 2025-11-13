#include <fstream>
using namespace std;

int main() {
    ifstream input("joseph.in");
    int N, P;
    input >> N >> P;
    input.close();

    int survivor = 0; 
    for (int n = 2; n <= N; n++) {
        survivor = (survivor + P) % n;
    }

    ofstream output("joseph.out");
    output << survivor + 1 << endl; 
    output.close();
}
