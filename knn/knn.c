#include <stdio.h>
#include "util.h"
#ifdef CUSTOM_INSTR
    #include "libhelper.h"
#endif
#define SAMPLES 200
#define SQUARE 200
#define DIMS 2
#define K 3

int X[SAMPLES][DIMS];
int Y[SAMPLES];

void train() {
    for (int i = 0; i < SAMPLES; i++) {
        for (int j = 0; j < DIMS; j++) {
            int rand = abs(get_random() % SQUARE);
            X[i][j] = rand;
        }
        // works for dims = 2
        int x = X[i][0];
        int y = X[i][1];
        if (x < SQUARE / 2) {
            Y[i] = y < SQUARE / 2 ? 1 : 3;
        } else {
            Y[i] = y < SQUARE / 2 ? 2 : 4;
        }
    }
}

void write_dataset() {
    FILE *fp = fopen("visualization/data.json", "wr");
    if (fp == NULL) return;

    fprintf(fp, "{ \"X\": [");

    for (int i = 0; i < SAMPLES; i++) {
        fprintf(fp, "[%d, %d]", X[i][0], X[i][1]);
        if (i != SAMPLES - 1) {
            fprintf(fp, ", ");
        }
    }
    fprintf(fp, "], \"Y\": [");
    for (int i = 0; i < SAMPLES; i++) {
        fprintf(fp, "%d", Y[i]);
        if (i != SAMPLES - 1) {
            fprintf(fp, ", ");
        }
    }
    fprintf(fp, "]}");
    fclose(fp);
}

void get_top_K_index(int top_indices[], int sample_x, int sample_y) {
    int lowest_dist[K] = {SQUARE, SQUARE, SQUARE};
    for (int i = 0; i < SAMPLES; ++i) {
        int x = X[i][0];
        int y = X[i][1];
#ifdef CUSTOM_INSTR
        int dist = absdsq(x, sample_x) + absdsq(y, sample_y);
#else
        int dist = abs(x - sample_x) * abs(x - sample_x) + abs(y - sample_y) * abs(y - sample_y);
#endif
        for (int j = 0; j < K; ++j) {
            if (dist < lowest_dist[j]) {
                for (int l = K - 1; l > j; l--) {
                    lowest_dist[l] = lowest_dist[l - 1];
                    top_indices[l] = top_indices[l - 1];
                }
                lowest_dist[j] = dist;
                top_indices[j] = i;
                break;
            }
        }
    }
}

int get_majority_label(int top_indices[]) {
    int top_labels[K];
    for (int i = 0; i < K; ++i) {
        top_labels[i] = Y[top_indices[i]];
    }

    bubble_sort(top_labels, K);
    int current_label = top_labels[0];
    int current_count = 1;
    int biggest_label = current_label;
    int biggest_count = current_count;
    for (int i = 1; i < K; i++) {
        if (top_labels[i - 1] == top_labels[i]) {
            current_count++;
            if (current_count > biggest_count) {
                biggest_count = current_count;
                biggest_label = current_label;
            }
        } else {
            current_count = 1;
            current_label = top_labels[i];
        }
    }
    return biggest_label;
}

void predict(int X_sample[][DIMS], int n_X) {
    for (int g = 0; g < n_X; ++g) {
        int top_indices[K];
        get_top_K_index(top_indices, X_sample[g][0], X_sample[g][1]);
        int result = get_majority_label(top_indices);
        printf("Prediction: %d \n", result);
    }
}

int main(void) {
    train();
    write_dataset();
    int samples[][DIMS] = {{50,  50},
                           {150, 150}};
    predict(samples, 2);
    return 0;
}
