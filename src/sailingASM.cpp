/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 * @file sailingASM.cpp
 * @author Dimitri Vahlas, Louise Ho, Wailok He, Jason Li
 * @manages sailing file operations
 * @version 1
 * @date 2025-07-23
 * 
*/
#include "sailingASM.h"
#include <iostream>
#include <io.h>
#include <fstream>

std::fstream SailingASM::file;
const std::string SailingASM::filename = "sailings.dat";

void SailingASM::init() {
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);

     if (!file.is_open()) {
        // File doesn't exist; create it
        file.open(filename, std::ios::binary | std::ios::out);
        file.close();
        file.open(filename, std::ios::binary | std::ios::in | std::ios::out);
    }
}
void SailingASM::shutdown() {
    if (file.is_open()) {
        file.close();
    }
}
void SailingASM::addSailing(const Sailing& sailing){
    file.seekp(0, std::ios::end);
    file.write(reinterpret_cast<const char *>(&sailing), sizeof(Sailing));
    file.flush(); // Force write to disk
    file.clear(); // Clear any error flags
}
bool SailingASM::getNextSailing(Sailing& sailing){
    if (!file.read(reinterpret_cast<char*>(&sailing), sizeof(Sailing))) {
        file.clear(); // Clear EOF flag for subsequent operations
        return false; // Reached end or error
    }
    return true;
}
void SailingASM::seekToBeginning() {
    if (file.is_open()) {
        file.clear(); // Clear any error flags first
        file.seekg(0, std::ios::beg); // Seek to beginning for reading
        file.seekp(0, std::ios::beg); // Also reset write position
    }
}
int SailingASM::getCurrentID() {
    if (!file.is_open()) {
        return 0;
    }
    file.clear(); // Clear any error flags
    std::streampos currentPos = file.tellg(); // Save current position
    file.seekg(0, std::ios::end); // Seek to end
    std::streampos size = file.tellg(); // Get file size
    file.seekg(currentPos); // Restore position
    return static_cast<int>(size / sizeof(Sailing));
}
void SailingASM::deleteSailing() {
    if (!file.is_open()) {
        std::cerr << "Error: File is not open." << std::endl;
        return;
    }
    
    // Get current position (record to delete) - should be just after the record we found
    std::streampos deletePos = file.tellg() - static_cast<std::streamoff>(sizeof(Sailing));
    
    // Seek to end to find last record
    file.seekg(0, std::ios::end);
    std::streampos endPos = file.tellg();
    
    // If file is empty, nothing to do
    if (endPos == 0) {
        return;
    }
    
    // Calculate position of last record
    std::streampos lastRecordPos = endPos - static_cast<std::streamoff>(sizeof(Sailing));
    
    // If we're deleting the last record, just truncate
    if (deletePos == lastRecordPos) {
        file.close();
        FILE* cFile = fopen("sailings.dat", "rb+");
        if (cFile) {
            int fd = _fileno(cFile);
            _chsize(fd, static_cast<long>(deletePos));
            fclose(cFile);
        }
        // Reopen the file
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        file.seekg(deletePos);
        return;
    }
    
    // Read the last record
    file.seekg(lastRecordPos);
    Sailing lastRecord;
    if (!file.read(reinterpret_cast<char*>(&lastRecord), sizeof(Sailing))) {
        std::cerr << "Error: Failed to read last record for deletion." << std::endl;
        return;
    }
    
    // Write the last record over the record to be deleted
    file.seekp(deletePos);
    file.write(reinterpret_cast<const char*>(&lastRecord), sizeof(Sailing));
    file.flush();
    
    // Truncate the file to remove the last record
    file.close();
    FILE* cFile = fopen("sailings.dat", "rb+");
    if (cFile) {
        int fd = _fileno(cFile);
        _chsize(fd, static_cast<long>(lastRecordPos));
        fclose(cFile);
    }
    
    // Reopen the file
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    file.seekg(deletePos);
}

bool SailingASM::overwriteSailing(const Sailing& sailing, int index) {
    if (!file.is_open()) {
        std::cerr << "Error: File is not open." << std::endl;
        return false;
    }
    
    // Calculate position of the record to overwrite
    std::streampos position = static_cast<std::streamoff>(index) * sizeof(Sailing);
    
    // Seek to the position and write the new sailing
    file.seekp(position);
    file.write(reinterpret_cast<const char*>(&sailing), sizeof(Sailing));
    file.flush(); // Force write to disk
    file.clear(); // Clear any error flags
    
    return file.good(); // Return true if write was successful
}