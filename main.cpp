#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <time.h>

using namespace std;

struct Film;
struct Sans;
struct CinemaSalon;
typedef vector<CinemaSalon> Cinema;


vector<Film> film;
Cinema cinema;
FILE *ptf = fopen("data.dat", "r");

struct CinemaSalon {
    string name;
    int cntOfSans;
    vector<Sans*> schedule;
    int cap;
};

struct Sans {
    Film *film;
    time_t startTime;
    time_t endTime;
    int cntOfEmptyChairs;
    bool expired;
};

struct Film {
    string name;
    int duration;
    string genre;
    string summary;
    vector<string> actors;
};

void addSans(Sans &sans, CinemaSalon &cSalon) {
    bool flg = false;
    for(int i = 0; i < cSalon.cntOfSans; ++i) {
        if(cSalon.schedule[i]->startTime <= sans.startTime && cSalon.schedule[i]->endTime >= sans.startTime) {
            flg = true;
        }
        else if(cSalon.schedule[i]->startTime <= sans.endTime && cSalon.schedule[i]->endTime >= sans.endTime) {
            flg = true;
        }
    }
    if(flg) {
        cout << "[!] in sans ba sans haye digar tadakhol darad.\n";
        return;
    }
    cSalon.cntOfSans += 1;
    cSalon.schedule.push_back(&sans);
    sans.cntOfEmptyChairs = cSalon.cap;
    cout << "[*] sans ba movafaghiat ezafe shod.\n";
}

void buyTicket(Sans &sans) {
    if(sans.cntOfEmptyChairs < 1) {
        cout << "[!] in sans por shode. shoma nemitavanid belit rezerve konid.\n";
        return;
    }
    sans.cntOfEmptyChairs -= 1;
}

void finalize() {
    fclose(ptf);
    FILE *pto = fopen("data.dat", "w");
    // cnt of salons
    fprintf(pto, "%d\n", cinema.size());
    for(int i = 0; i < cinema.size(); ++i) {
        fprintf(pto, "%s %d\n", cinema[i].name, cinema[i].cntOfSans);
        // now we output address of the cinema salons
        for(int j = 0; j < cinema[i].cntOfSans; ++i) {
            fprintf(pto, "%x ", cinema[i].schedule[j]);
        }
        fprintf(pto, "\n%d\n", cinema[i].cap);
    }
    // end of the salons infomrmations
    

}

void menu() {
    cout << "1- ezafe kardane sans\n";
    cout << "2- kharide belit\n";
    cout << "3- ezafe karane film\n";
    cout << "0- exit the program\n";
    cout << "your option:";
    int op;
    cin >> op;
    if(op == 0) {
        finalize();
        exit(1);
    } else if(op == 1) {
        cout << "filmi ra baraye in sans entekhab konid:\n";
        for(int i = 0; i < film.size(); ++i) {
            cout << i + 1 << "- " << film[i].name << endl;
        }
        cout << "kodum film made nazaretune?";
        int flm;
        cin >> flm;
        tm sTime;
        yar:;
        cout << "sale shorue sans ra be ghamari beguEid:";
        int x;
        cin >> x;
        if(x < 2020 || x > 2100) {
            cout << "[!] mah bayad adady beine 2020 va 2100 bashe.\n";
            goto yar;
        }
        sTime.tm_year = x;
        mth:;
        cout << "mahe shorue sans ra be ghamari beguEid:";
        int x;
        cin >> x;
        if(x < 1 || x > 12) {
            cout << "[!] mah bayad adady beine 1 va 12 bashe.\n";
            goto mth;
        }
        sTime.tm_mon = x;
        dy:;
        cout << "ruze shorue sans ra be ghamari beguEid:";
        int x;
        cin >> x;
        if(x < 1 || x > 31) {
            cout << "[!] ruz bayad adady beine 1 va 31 bashe.\n";
            goto dy;
        }
        sTime.tm_mday = x;
        hr:;
        cout << "saate shorue sans ra be ghamari beguEid:";
        int x;
        cin >> x;
        if(x < 0 || x > 23) {
            cout << "[!] saate bayad adady beine 0 va 23 bashe.\n";
            goto hr;
        }
        sTime.tm_hour = x;
        mnu:;
        cout << "daghighe shorue sans ra be ghamari beguEid:";
        int x;
        cin >> x;
        if(x < 0 || x > 59) {
            cout << "[!] daghighe bayad adady beine 0 va 59 bashe.\n";
            goto mnu;
        }
        sTime.tm_min = x;

        time_t sT = mktime(&sTime), eT = sT + film[flm - 1].duration;
        cout << "kodum salon mikhayn pakhsh she?\n";
        for(int i = 0; i < cinema.size(); ++i) {
            cout << i + 1 << "- " << cinema[i].name << " with capacity = " << cinema[i].cap << endl;
        }
        int cnm;
        encnm:;
        cout << "kodum salon?";
        cin >> cnm;
        if(cnm < 1 || cnm > cinema.size()) {
            cout << "[!] adade shoma bayad beine 1 ta " << cinema.size() << " bashe.\n";
            goto encnm;
        }
        Sans sans{&film[flm - 1], sT, eT, cinema[cnm - 1].cap, 0};
        addSans(sans, cinema[cnm - 1]);
    } else if(op == 2) {

    }

}

int main() {
    time_t now = time(0);
    cout << ctime(&now);
}