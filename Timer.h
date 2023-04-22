#include <iostream>
#include <chrono>

using namespace std;
class Timer
{
public:
    Timer() : started_(false) {}

    void start()
    {
        if (!started_) {
            start_ = std::chrono::high_resolution_clock::now();
            started_ = true;
        }
    }

    void stop()
    {
        if (started_) {
            const auto stop = chrono::high_resolution_clock::now();
            const auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start_);
            cout << "Time taken: " << duration.count() << " milliseconds" << endl;
            started_ = false;
        }
    }

private:
    chrono::time_point<std::chrono::high_resolution_clock> start_;
    bool started_;
};

