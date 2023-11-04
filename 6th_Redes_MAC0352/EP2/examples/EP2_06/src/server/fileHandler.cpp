#include <fileHandler.hpp>

FileHandler::FileHandler() {
    if(!fileExists(TMP_FOLDER)) {
        if(mkdir(TMP_FOLDER, 0777) == -1) {
            perror("mkdir :(\n");
            exit(EXIT_DB);
        }
    }

    if(!fileExists(ACTIVE_USERS_FOLDER)) {
        if(mkdir(ACTIVE_USERS_FOLDER, 0777) == -1) {
            perror("mkdir :( \n");
            exit(EXIT_DB);
        }
    }
}

int FileHandler::createNewUser(User user, vector<string> content) {
    string filename = TMP_FOLDER + string("/") + user.username;
    if(fileExists(filename.c_str()))
        return -1;

    ofstream userFile(filename);
    if(!userFile.is_open()) {
        cerr << "[ERROR] Error creating user file! Closing connection." << endl;
        exit(EXIT_DB);
    }

    for(size_t i = 0; i < content.size(); i++) {
        userFile << content[i] << endl;
    }

    userFile.close();
    return 0;
}

int FileHandler::connectNewUser(User user, vector<string> content) {
    string filename = ACTIVE_USERS_FOLDER + string("/") + to_string(user.session);
    if(fileExists(filename.c_str()))
        return -1;

    ofstream userFile(filename);
    if(!userFile.is_open()) {
        cerr << "[ERROR] Error creating user file! Closing connection." << endl;
        exit(EXIT_DB);
    }

    for(size_t i = 0; i < content.size(); i++) {
        userFile << content[i] << endl;
    }

    userFile.close();
    return 0;
}

void FileHandler::writeFile(string filePath, vector<string> newContent) {
    ofstream file(filePath);

    if(!file.is_open()) {
        cerr << "[ERROR] Error openning file " << filePath << ". Closing connection." << endl;
        exit(EXIT_DB);
    }

    for(size_t i = 0; i < newContent.size(); i++) {
        file << newContent[i] << endl;
    }

    file.close();
}

vector<string> FileHandler::getFileContent(string filePath) {
    ifstream file(filePath);
    vector<string>fileContent;
    string lineContent;

    while (getline(file, lineContent)) {
        fileContent.push_back(lineContent);
    }

    file.close();
    return fileContent;
}

vector<string> FileHandler::getFilenamesInDirectory(string path) {
    vector<string> filenames;
    DIR *folder;
    struct dirent *file;

    if((folder = opendir(path.c_str())) == NULL) {
        perror("opendir :(\n");
        exit(EXIT_DB);
    }

    while ((file = readdir(folder)) != NULL) {
        if(string(file->d_name) == "." || string(file->d_name) == "..")
            continue;
    
        filenames.push_back(file->d_name);
    }

    return filenames;
}