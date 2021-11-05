#include "ranking.h"

#include <stdio.h>  // fopen, fread, fwrite
#include "raylib.h" // FileExists
#include <limits.h>


// Write ranking struct to file in disk
void writeRanking(Ranking ranking) {
    // Opening file in binary write mode
    FILE *rankingFile = fopen("assets/ranking.dat", "wb");

    if (rankingFile == NULL) {
        printf("Unable to write to ranking file\n");
        return;
    }

    // Writing data to file
    fwrite(&ranking, sizeof(Ranking), 1, rankingFile);

    // Closing file
    fclose(rankingFile);
}

// Return current ranking
Ranking getRanking() {
    Ranking ranking;

    FILE *rankingFile = fopen("assets/ranking.dat", "rb");

    // If ranking file already exists
    if (rankingFile != NULL) {
        // Load data into ranking var
        fread(&ranking, sizeof(Ranking), 1, rankingFile);
        // close the file
        fclose(rankingFile);
    } else {
        // If the file does not exist, create an empty ranking
        for (int i = 0; i < RANKING_ENTRIES; i++) {
            RankingEntry entry = {.username = "", .score = INT_MIN};
            ranking.entries[i] = entry;
        }
        // And save it to disk
        writeRanking(ranking);
    }
    return ranking;
}

// Save entry on ranking file
void saveOnRanking(RankingEntry entry) {
    Ranking ranking = getRanking();
    RankingEntry lastEntry;

    // Flag that indicates whether the entry is being inserted or moved down
    bool inserting = true;

    for (int i = 0; i < RANKING_ENTRIES; i++) {
        // If the entry score is higher than the current entry, the 
        // entry need to pushed down the list
        if (entry.score > ranking.entries[i].score) {
            // If it is inserting the new entry
            if (inserting) {
                // Save the old entry and replace it with the new entry
                lastEntry = ranking.entries[i];
                ranking.entries[i] = entry;

                // Set the inserting flag to false
                inserting = false;
            } else {
                // If it is pushing an entry down, swaps the current 
                // entry with the last entry
                RankingEntry tmp = ranking.entries[i];
                ranking.entries[i] = lastEntry;
                lastEntry = tmp;
            }
        }
    }

    // Save new ranking on disk
    writeRanking(ranking);
}
