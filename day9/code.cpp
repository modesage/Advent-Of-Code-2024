#include <bits/stdc++.h>
using namespace std;


long long solve(const string& disk, bool moveWholeFiles) {
    vector<tuple<int, int, int>> files; // (pos, size, file_id)
    vector<tuple<int, int>> spaces;    //  (pos, size)
    vector<int> layout;                // Layout of the disk
    int fileId = 0, pos = 0;

    // Parse the disk data
    for (size_t i = 0; i < disk.size(); ++i) {
        int size = disk[i] - '0';
        if (i % 2 == 0) { // File blocks
            if (moveWholeFiles) {
                files.emplace_back(pos, size, fileId); // Track entire file
            }
            for (int j = 0; j < size; ++j) {
                layout.push_back(fileId);
                if (!moveWholeFiles) {
                    files.emplace_back(pos + j, 1, fileId); // Track individual blocks
                }
            }
            pos += size;
            fileId++;
        } else { // Free space blocks
            spaces.emplace_back(pos, size);
            for (int j = 0; j < size; ++j) {
                layout.push_back(-1); // Mark free space
            }
            pos += size;
        }
    }

    // Compact files into free spaces
    for (auto it = files.rbegin(); it != files.rend(); ++it) {
        auto [fPos, fSize, fId] = *it;
        for (auto& [sPos, sSize] : spaces) {
            if (sPos < fPos && fSize <= sSize) { // Check if file fits in free space
                for (int i = 0; i < fSize; ++i) {
                    layout[sPos + i] = layout[fPos + i]; // Move file block
                    layout[fPos + i] = -1;              // Clear original position
                }
                sPos += fSize;  // Update free space position
                sSize -= fSize; // Update free space size
                break;
            }
        }
    }

    // Compute checksum
    long long checksum = 0;
    for (size_t i = 0; i < layout.size(); ++i) {
        if (layout[i] != -1) {
            checksum += static_cast<long long>(i) * layout[i];
        }
    }

    return checksum;
}

int main() {
    ifstream inFile("input.txt");
    string diskData;
    inFile >> diskData;
    inFile.close();

    // Calculate results for both parts
    long long part1 = solve(diskData, false); // Part 1: Individual block movement
    long long part2 = solve(diskData, true);  // Part 2: Whole file movement

    cout << "Part 1: " << part1 << endl;
    cout << "Part 2: " << part2 << endl;

    return 0;
}
