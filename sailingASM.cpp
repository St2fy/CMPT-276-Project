#include "SailingASM.h"
#include <iostream>
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

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'\n";
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
}
bool SailingASM::getNextSailing(Sailing& sailing){
    if (!file.read(reinterpret_cast<char*>(&sailing), sizeof(Sailing))) {
        return false; // Reached end or error
    }
    return true;
}
void SailingASM::seekToBeginning() {
    if (file.is_open()) {
        file.seekg(0, std::ios::beg); // Seek to beginning for reading
    }
}
int SailingASM::getCurrentID() {
    file.clear();
    file.seekg(0, std::ios::end);
    std::streampos size = file.tellg();
    return static_cast<int>(size / sizeof(Sailing));
}
void SailingASM::deleteSailing() {
    if (!file.is_open()) {
        std::cerr << "Error: File is not open." << std::endl;
        return;
    }
    
    // Get current position (record to delete)
    std::streampos deletePos = file.tellg();
    
    // Seek to end to find last record
    file.seekg(0, std::ios::end);
    std::streampos endPos = file.tellg();
    
    // If we're already at end or file is empty, nothing to do
    if (deletePos == endPos || endPos == 0) {
        return;
    }
    
    // Calculate position of last record
    std::streampos lastRecordPos = endPos - sizeof(Sailing);
    
    // If we're deleting the last record, just truncate
    if (deletePos == lastRecordPos) {
        file.seekp(deletePos);
        file.close();
        
        // Truncate the file
        std::ofstream truncFile(filename, std::ios::binary | std::ios::trunc);
        truncFile.close();
        
        // Reopen the file
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
        file.seekg(deletePos);
        return;
    }
    
    // Read the last record
    file.seekg(lastRecordPos);
    Sailing lastRecord;
    if (!file.read(reinterpret_cast<char*>(&lastRecord),sizeof(Sailing))) {
        std::cerr << "Error: Failed to read last record for deletion." << std::endl;
        return;
    }
    
    // Write the last record over the record to be deleted
    file.seekp(deletePos);
    file.write(reinterpret_cast<const char*>(&lastRecord), sizeof(Sailing));
    
    // Truncate the file to remove the duplicate last record
    file.flush();
    file.close();
    
    // Truncate the file to new size wrong implementation
    std::ofstream truncFile(filename, std::ios::binary | std::ios::app);
    truncFile.close();
    
    // Reopen the file
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    file.seekg(deletePos);
}