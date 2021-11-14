#include "ranking.h"

#include <stdio.h>  // fopen, fread, fwrite
#include "raylib.h" // FileExists
#include <limits.h>


/**
 * Write the ranking to a binary file
 * 
 * Arguments:
 *     ranking (Ranking): Ranking to be written to the file.
 */
static void writeRanking(Ranking ranking) {
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

/**
 * Load and return the current ranking. 
 */
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

/**
 * Save an entry into the ranking.
 * 
 * Arguments:
 *     entry (RankingEntry): entry to be added to ranking
 */
void saveOnRanking(RankingEntry entry) {
    // Loading current ranking
    Ranking ranking = getRanking();

    // The ranking will be sorted using insertion sort

    // Auxiliar to hold the last entry
    RankingEntry lastEntry = entry;

    for (int i = 0; i < RANKING_ENTRIES; i++) {
        // If the entry score is higher than the current entry, swap
        // the last entry and the current entry
        if (entry.score > ranking.entries[i].score) {
            // If it is pushing an entry down, swaps the current 
            // entry with the last entry
            RankingEntry tmp = ranking.entries[i];
            ranking.entries[i] = lastEntry;
            lastEntry = tmp;
        }
    }

    // Save new ranking on disk
    writeRanking(ranking);
}
