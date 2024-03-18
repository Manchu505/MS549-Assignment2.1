#include <iostream>
#include <string>
#include <dirent.h> // Directory entry structure for Linux
#include <cstring>

using namespace std;

bool hasExtension(const string& fileName, const string& extension) {
    if (extension.empty()) return true; // If no extension is provided, always return true
    if (fileName.length() >= extension.length()) {
        return (0 == fileName.compare(fileName.length() - extension.length(), extension.length(), extension));
    }
    else {
        return false;
    }
}

void exploreDirectory(const string& directoryPath, const string& extension, int depth = 0) {
    DIR* dir = opendir(directoryPath.c_str()); // Open the directory
    if (dir == nullptr) {
        cerr << "Failed to open directory: " << directoryPath << endl;
        return;
    }

    dirent* entry;
    while ((entry = readdir(dir)) != nullptr) { // Read each entry in the directory
        // Skip the "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path of the entry
        string fullPath = directoryPath + "/" + entry->d_name;

        if (entry->d_type == DT_DIR) {
            // If the entry is a directory, recursively explore it
            exploreDirectory(fullPath, extension, depth + 1);
        }
        else if (hasExtension(entry->d_name, extension)) {
            // If the entry is a file and matches the extension (if provided), print its name with indentation
            cout << string(depth * 2, ' ') << entry->d_name << endl;
        }
    }

    closedir(dir); // Close the directory stream
}

int main() {
    string startPath, extension;
    cout << "Enter the starting directory path: ";
    cin >> startPath;
    cout << "Enter file extension to filter by (leave empty for all files): ";
    cin.ignore(); // Clear the newline character from the input buffer after reading startPath
    getline(cin, extension); // Use getline to allow empty input

    exploreDirectory(startPath, extension); // Start the recursive exploration

    return 0;
}
