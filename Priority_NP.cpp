#include<iostream>
#include<vector>
#include <algorithm>

using namespace std;
struct process {
    int pid;
    int arrtime;
    int burstime;
    int remaintime;
    int priority; //higher is more urgent
    int wtime = 999;
    int turnaroundtime;
    int exitime;
};

bool compareArr(process p1, process p2) {
    return (p1.arrtime > p2.arrtime);
}

bool compareRem(process p1, process p2) {
    return (p1.remaintime > p2.remaintime);
}

bool comparePri(process p1, process p2) {
    return (p1.priority < p2.priority);
}

int main() {
    int n;
    int avgturnaround = 0, avgwait = 0;
    cout << "Enter no. of processes: ";
    cin >> n;
    int curtime = 0, ttlexec = 0;
    vector < process > notinqueue, waitqueue, inqueue, completed;
    for (int i = 1; i < n + 1; i++) {
        process a;
        a.pid = i;
        cout << "Enter the arrival time for pid " << i << ": ";
        cin >> a.arrtime;
        cout << "Enter the burst time for pid " << i << ": ";
        cin >> a.burstime;
        a.remaintime = a.burstime;
        cout << "Enter priorty (higher is more urgent): ";
        cin >> a.priority;
        ttlexec = ttlexec + a.burstime;
        notinqueue.push_back(a);
    }
    cout << endl << endl;
    sort(notinqueue.begin(), notinqueue.end(), compareArr);
    for (curtime; curtime <= ttlexec; curtime++) {
        int k1 = 999;
        if (!notinqueue.empty())
            k1 = notinqueue.back().arrtime;

        if (inqueue.empty()) {
            if (k1 == curtime) {
                process a = notinqueue.back();
                notinqueue.pop_back();
                inqueue.push_back(a);
                inqueue.back().remaintime--;
                cout << "'" << inqueue.back().pid << "' ";
                inqueue.back().wtime = 0;
                avgwait = avgwait + curtime;
                if (inqueue.back().remaintime == 0) {
                    inqueue.back().exitime = curtime + 1;
                    inqueue.back().turnaroundtime = inqueue.back().exitime - inqueue.back().arrtime;
                    avgturnaround = avgturnaround + inqueue.back().turnaroundtime;
                    completed.push_back(inqueue.back());
                    inqueue.pop_back();
                }
            }
        } else {
            if (k1 == curtime) {
                process a = notinqueue.back();
                notinqueue.pop_back();
                waitqueue.push_back(a);
            }
            if (!inqueue.empty()) {
                inqueue.back().remaintime--;
                cout << "'" << inqueue.back().pid << "' ";
            }
            if (inqueue.back().wtime != 999) {
                inqueue.back().wtime = curtime;
                avgwait = avgwait + curtime;
            }
            if (inqueue.back().remaintime == 0) {
                inqueue.back().exitime = curtime + 1;
                inqueue.back().turnaroundtime = inqueue.back().exitime - inqueue.back().arrtime;
                avgturnaround = avgturnaround + inqueue.back().turnaroundtime;
                process a = inqueue.back();
                completed.push_back(a);
                inqueue.pop_back();
                sort(waitqueue.begin(), waitqueue.end(), comparePri); //for non-primitive
                inqueue.push_back(waitqueue.back());
                waitqueue.pop_back();
            }
        }
    }

    avgturnaround = avgturnaround / n;
    avgwait = avgwait / n;
    cout << "\navg turnaround is: " << avgturnaround;
    cout << "\navg wait is: " << avgwait << endl;
    cout << "final results: " << endl;
    sort(completed.begin(), completed.end(), compareArr);
    for (int i = 0; i < n; i++) {
        cout << "Pid\tArrival Time\tBurst Time\tTurnaround Time\t\tExit Time\tPriority\n";
        cout << completed.back().pid << "\t\t" << completed.back().arrtime << "\t\t" <<
            completed.back().burstime << "\t\t" << completed.back().turnaroundtime << "\t\t" <<
            completed.back().exitime << "\t\t" << completed.back().priority << "\n";
        completed.pop_back();
    }
    return 0;
}