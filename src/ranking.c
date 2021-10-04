#include <stdio.h>  // fopen, fread, fwrite
#include "raylib.h"

#include "ranking.h"
// Write ranking struct to file in disk
void writeRanking(Ranking ranking) {
    FILE *rankingFile = fopen("assets/ranking.dat", "wb");
    fwrite(&ranking, sizeof(Ranking), 1, rankingFile);
    fclose(rankingFile);
}

// Return current ranking
Ranking getRanking() {
    Ranking ranking;

    // If ranking file already exists
    if (FileExists("assets/ranking.dat")) {
        // read file from disk
        FILE *rankingFile = fopen("assets/ranking.dat", "rb");
        // Load data into ranking var
        fread(&ranking, sizeof(Ranking), 1, rankingFile);
        // close the file
        fclose(rankingFile);
    } else {
        // If the file does not exist, create an empty ranking
        for (int i = 0; i < 5; i++)
            ranking.entries[i] = (RankingEntry){.username = "", .score = 0};
        // And save it to disk
        writeRanking(ranking);
    }
    return ranking;
}

void saveOnRanking(RankingEntry entry) {
    // Load current ranking
    Ranking ranking = getRanking();

    // Hold the last entry in loop
    RankingEntry lastEntry;

    // Flag that indicates whether the entry is being inserted or moved down
    bool inserting = true;

    // Loop to place the entry on the correct position, according to its score.
    for (int i = 0; i < 5; i++) {
        // If the entry score is higher than the current entry, it was either
        // inserted or the current entry needs to be pushed down the list
        if (entry.score > ranking.entries[i].score) {
            // If it is inserting the new entry
            if (inserting) {
                // Save the old entry on lastEntry
                lastEntry = ranking.entries[i];
                // Replace it with the new entry
                ranking.entries[i] = entry;
                // Set the inserting flag to false
                inserting = false;
            } else {
                // If it is pushing an entry down
                
                // Swaps the current entry with the last entry, using a 
                // temporary variable
                RankingEntry tmp = ranking.entries[i];
                ranking.entries[i] = lastEntry;
                lastEntry = tmp;
            }
        }
    }

    // Save new ranking on disk
    writeRanking(ranking);
}
