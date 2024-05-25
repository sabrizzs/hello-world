#include <util.hpp>

struct sigaction sigIntAction;

int unlink_cb(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf){ 
        int rv = remove(fpath);

        if (rv)
            perror(fpath);

        return rv;
};

bool isNumber(const string& str){
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

bool fileExists(string path) {
    return access(path.c_str(), F_OK) == 0;
}

bool isDirectory(string path) {
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    return !S_ISREG(path_stat.st_mode);
}

int removeFile(string path) {
    if(remove(path.c_str()) == -1) {
        perror("remove :(\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int removeFolder(string path) {
    return nftw(path.c_str(), unlink_cb, 64, FTW_DEPTH | FTW_PHYS);
}

void printBytes(string src) {
    for(int i = 0; i < (int)src.length(); i++) {
        printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(src[i]));
        cout << endl;
    }
}

string printNetworkData(sockaddr_in data) {
    char buffer[MAX_IP_SIZE + 1];
    
    inet_ntop(AF_INET, &(data.sin_addr).s_addr, buffer, sizeof(buffer));

    string port = to_string(ntohs(data.sin_port));
    string ip = string(buffer);

    return ip + ":" + port;
}

void sigTermHandler(int sig_no) {
    printf("\n[Closing connection.]\n");
    removeFolder(ACTIVE_USERS_FOLDER);
    //Sets default behavior back
    sigaction(SIGTERM, &sigIntAction, NULL);
    kill(0, SIGTERM);
}

void setCleanUpHook() {
    struct sigaction action;
    bzero(&action, sizeof(action));
    action.sa_handler = &sigTermHandler;
    sigaction(SIGTERM, &action, &sigIntAction);
}

void resetCleanUpHook() {
    sigaction(SIGTERM, &sigIntAction, NULL);
}
