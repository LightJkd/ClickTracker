#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>

using namespace std;
using namespace std::chrono;

vector<long long> delays;
atomic<bool> recording(false);
atomic<bool> replaying(false);
atomic<int> clickCount(0);

void recordClicks();
void replayClicks();
void saveClicks(const string& filename);
void loadClicks(const string& filename);

int main() {
    cout << "Press 'J' to start/stop recording clicks." << endl;
    cout << "Press 'R' to start/stop replaying clicks." << endl;
    cout << "Press 'H' to save recorded clicks to a file." << endl;
    cout << "Press 'L' to load clicks from a file." << endl;
    cout << "\nThe more you click, the better it gets!" << endl;

    while (true) {
        if (GetAsyncKeyState('J') & 0x8000) {
            if (!recording) {
                recording = true;
                cout << "Recording started..." << endl;
                thread recordThread(recordClicks);
                recordThread.detach();
            } else {
                recording = false;
                cout << "Recording stopped." << endl;
            }
            this_thread::sleep_for(milliseconds(200));
        }

        if (GetAsyncKeyState('R') & 0x8000) {
            if (!replaying) {
                replaying = true;
                cout << "Replaying clicks..." << endl;
                thread replayThread(replayClicks);
                replayThread.detach();
            } else {
                replaying = false;
                cout << "Replay stopped." << endl;
            }
            this_thread::sleep_for(milliseconds(200));
        }

        if (GetAsyncKeyState('H') & 0x8000) {
            saveClicks("clicks.txt");
            cout << "Clicks saved to clicks.txt" << endl;
            this_thread::sleep_for(milliseconds(200));
        }

        if (GetAsyncKeyState('L') & 0x8000) {
            loadClicks("clicks.txt");
            cout << "Clicks loaded from clicks.txt" << endl;
            this_thread::sleep_for(milliseconds(200));
        }

        this_thread::sleep_for(milliseconds(10));
    }

    return 0;
}

void recordClicks() {
    auto startTime = high_resolution_clock::now();
    clickCount = 0;
    while (recording) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            auto currentTime = high_resolution_clock::now();
            auto delay = duration_cast<microseconds>(currentTime - startTime).count();
            startTime = currentTime;

            delays.push_back(delay);
            ++clickCount;

            if (clickCount % 50 == 0) {
                cout << clickCount << " clicks" << endl;
            }

            while (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                this_thread::sleep_for(milliseconds(1));
            }
        }
        this_thread::sleep_for(milliseconds(1));
    }
}

void replayClicks() {
    while (replaying) {
        auto startTime = high_resolution_clock::now();
        for (size_t i = 0; i < delays.size(); ++i) {
            if (!replaying) {
                break;
            }

            this_thread::sleep_until(startTime + microseconds(delays[i]));

            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

            startTime += microseconds(delays[i]);
        }
    }
}

void saveClicks(const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return;
    }

    for (const auto& delay : delays) {
        outFile << delay << endl;
    }

    outFile.close();
}

void loadClicks(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Failed to open file for reading." << endl;
        return;
    }

    delays.clear();
    long long delay;
    while (inFile >> delay) {
        delays.push_back(delay);
    }

    inFile.close();
}
