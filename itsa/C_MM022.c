#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int length;
    int* sub_lengths;
} Segment;


void maxTotalLength(int m, int n, Segment* segments, int** dp, int** selected_segments) {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            dp[i][j] = dp[i - 1][j];
            selected_segments[i][j] = selected_segments[i - 1][j];

            for (int k = 1; k <= segments[i - 1].length; k++) {
                if (j >= k) {
                    int current_length = 0;
                    for (int l = 0; l < k; l++) {
                        current_length += segments[i - 1].sub_lengths[l];
                    }
                    if (dp[i - 1][j - k] + current_length > dp[i][j]) {
                        dp[i][j] = dp[i - 1][j - k] + current_length;
                        selected_segments[i][j] = k;
                    }
                }
            }
        }
    }
}


void printSelectedSegments(int m, int n, Segment* segments, int** selected_segments) {
    int current_m = m;
    int current_n = n;

    while (current_m > 0 && current_n > 0) {
        int selected_count = selected_segments[current_m][current_n];
        if (selected_count > 0) {
            printf("(%d, %d) ", current_m, selected_count);
            current_m--;
            current_n -= selected_count;
        } else {
            current_m--;
        }
    }

    printf("\n");
}

int main() {
  int m, n;
  scanf("%d %d", &m, &n);

  Segment* segments = (Segment*)malloc(m * sizeof(Segment));
  int** dp = (int**)malloc((m + 1) * sizeof(int*));
  int** selected_segments = (int**)malloc((m + 1) * sizeof(int*));

  for (int i = 0; i <= m; i++) {
      dp[i] = (int*)malloc((n + 1) * sizeof(int));
      selected_segments[i] = (int*)malloc((n + 1) * sizeof(int));
  }


  for (int i = 0; i < m; i++) {
    scanf("%d", &segments[i].length);
    segments[i].sub_lengths = (int*)malloc(segments[i].length * sizeof(int));
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < segments[i].length; j++) {
      scanf("%d", &segments[i].sub_lengths[j]);
    }
  }



  maxTotalLength(m, n, segments, dp, selected_segments);


  printf("%d\n", dp[m][n]);
  printSelectedSegments(m, n, segments, selected_segments);

  for (int i = 0; i <= m; i++) {
      free(dp[i]);
      free(selected_segments[i]);
  }
  free(dp);
  free(selected_segments);

  for (int i = 0; i < m; i++) {
      free(segments[i].sub_lengths);
  }
  free(segments);

  return 0;
}
