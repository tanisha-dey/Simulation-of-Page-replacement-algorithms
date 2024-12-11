#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Function for FIFO Page Replacement
void fifo(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], count = 0, page_faults = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1; // Initialize frames to -1 (empty)
    }

    printf("\n=== FIFO Page Replacement ===\n");
    printf("Page | Frame Contents           | Status\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            frame[count] = page; // Replace page in FIFO order
            count = (count + 1) % frames;
            page_faults++;
            printf("%4d | ", page);
            for (int j = 0; j < frames; j++) {
                if (frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("        | Page Fault\n");
        } else {
            printf("%4d | ", page);
            for (int j = 0; j < frames; j++) {
                if (frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("        | Hit\n");
        }
    }

    printf("-----------------------------------------\n");
    printf("Total Page Faults (FIFO): %d\n", page_faults);
}

// Function for LRU Page Replacement
void lru(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], last_used[MAX_FRAMES], page_faults = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;  // Initialize frames to -1 (indicating empty)
        last_used[i] = -1;  // Initialize last_used to -1 (indicating no usage yet)
    }

    printf("\n=== LRU Page Replacement ===\n");
    printf("Page | Frame Contents           | Status\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                last_used[j] = i;  // Update usage time for the found page
                break;
            }
        }

        if (!found) { // Page fault
            // Find the least recently used page's index
            int lru_index = 0;
            for (int j = 1; j < frames; j++) {
                if (frame[j] == -1 || last_used[j] < last_used[lru_index]) {
                    lru_index = j;
                }
            }
            frame[lru_index] = page;  // Replace the page at lru_index
            last_used[lru_index] = i; // Update usage time for the new page
            page_faults++;
            printf("%4d | ", page);
            for (int j = 0; j < frames; j++) {
                if (frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("        | Page Fault\n");
        } else {
            printf("%4d | ", page);
            for (int j = 0; j < frames; j++) {
                if (frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("        | Hit\n");
        }
    }

    printf("-----------------------------------------\n");
    printf("Total Page Faults (LRU): %d\n", page_faults);
}

// Function for Optimal Page Replacement
void optimal(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], page_faults = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;  // Initialize frames to -1 (indicating empty)
    }

    printf("\n=== Optimal Page Replacement ===\n");
    printf("Page | Frame Contents           | Status\n");
    printf("-----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frame
        for (int j = 0; j < frames; j++) {
            if (frame[j] == page) {
                found = 1;
                break;
            }
        }

        if (!found) { // Page fault
            // Find the optimal page to replace (the one that won't be used for the longest time)
            int replace_index = -1;
            int farthest = i;
            for (int j = 0; j < frames; j++) {
                int next_use = -1;
                for (int k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        next_use = k;
                        break;
                    }
                }

                // If the page is not found again, it is the best candidate for replacement
                if (next_use == -1) {
                    replace_index = j;
                    break;
                }

                // Otherwise, find the page that will be used farthest in the future
                if (next_use > farthest) {
                    farthest = next_use;
                    replace_index = j;
                }
            }

            frame[replace_index] = page;  // Replace the page
            page_faults++;
            printf("%4d | ", page);
            for (int j = 0; j < frames; j++) {
                if (frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("        | Page Fault\n");
        } else {
            printf("%4d | ", page);
            for (int j = 0; j < frames; j++) {
                if (frame[j] != -1)
                    printf("%d ", frame[j]);
                else
                    printf("- ");
            }
            printf("        | Hit\n");
        }
    }

    printf("-----------------------------------------\n");
    printf("Total Page Faults (Optimal): %d\n", page_faults);
}

// Main function to simulate all three algorithms
int main() {
    int pages[MAX_PAGES], n, frames;

    // Input page reference sequence and number of frames
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page sequence: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Simulate algorithms
    fifo(pages, n, frames);
    lru(pages, n, frames);
    optimal(pages, n, frames);

    return 0;
}
