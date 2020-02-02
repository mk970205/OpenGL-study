#include "log.h"

using namespace std;

string GL_LOG_FILE("log.txt");

bool gl_restart_log() {
    ofstream log_file(GL_LOG_FILE);
    if (!log_file) {
        cerr << "could not open GL_LOG_FILE " + GL_LOG_FILE + "." << endl;
        return false;
    }

    time_t now = time(NULL);
    char buffer[30];
    ctime_s(buffer, 30, &now);
    string date(buffer);
    log_file << "GL_LOG restarted. local time: " + date << endl;

    return true;
}

bool gl_log(string message) {
    ofstream log_file(GL_LOG_FILE);
    if (!log_file) {
        cerr << "could not open GL_LOG_FILE " + GL_LOG_FILE + "." << endl;
        return false;
    }

    log_file << message << endl;
    return true;
}