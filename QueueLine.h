#include <ctime>
#include <functional>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>

using namespace std;

class QueueLine {

  struct stTicket {
    string Date, Time, prefix;
    int index;
  };

  string _prefix;
  int _avg_waiting_time;
  int _total = 0, _served = 0, _waiting = 0;
  queue<stTicket> _line;

  string _currentDate() {
    time_t t = time(0);
    tm *now = localtime(&t);

    int year, month, day;

    year = now->tm_year + 1900;
    month = now->tm_mon + 1;
    day = now->tm_mday;

    return to_string(day) + '/' + to_string(month) + '/' + to_string(year);
  }

  string _currentTime() {

    time_t t = time(0);
    tm *now = localtime(&t);

    return to_string(now->tm_hour) + ':' + to_string(now->tm_min) + ':' +
           to_string(now->tm_sec);
  }

  void _printTicket(stTicket ticket) {
    cout << "_____________________\n";
    cout << setw(10 + (ticket.prefix.size() / 2)) << ticket.prefix << "\n";
    cout << setw(10 + ((ticket.Date.size() + ticket.Time.size() + 3) / 2))
         << ticket.Date + " - " + ticket.Time << '\n';
    cout << " Waiting Clients: " << ticket.index << '\n';
    cout << "   Served Time In   " << '\n';
    cout << setw(7) << _avg_waiting_time * ticket.index << " Minutes" << '\n';
    cout << "_____________________\n";
  }

public:
  QueueLine(string prefix, int avg_waiting_time) {
    _prefix = prefix;
    _avg_waiting_time = avg_waiting_time;
  }

  void issueTicket() {
    stTicket newTiket = {_currentDate(), _currentTime(),
                         _prefix + to_string(_line.size() + 1)};
    _line.push(newTiket);
    _total++, _waiting++;
  }

  void serveNext() {
    if (!_line.empty()) {
      _line.pop();
      _waiting--, _served++;
    }
  }

  void printInfo() {

    cout << "_____________________\n";
    cout << setw(10 + (_prefix.size() / 2)) << _prefix << "\n\n";
    cout << "  Total  :" << _total << '\n';
    cout << "  Served :" << _served << '\n';
    cout << "  Waiting:" << _waiting << '\n';
    cout << "_____________________\n";
  }

  void printAllTickets() {
    queue<stTicket> temp = _line;

    for (int i = 0; i < temp.size(); i++) {
      temp.front().index = i;
      _printTicket(temp.front());
      cout << '\n';
      temp.pop();
    }
  }
};
