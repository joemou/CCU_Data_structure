#include <stdio.h>

struct Activity {
    int start, finish, duration;
};

void activitySelection(struct Activity activities[], int n) {
    // Calculate duration for each activity
    for (int i = 0; i < n; i++) {
        activities[i].duration = activities[i].finish - activities[i].start;
    }

    // Sort activities by duration in descending order (using bubble sort for simplicity)
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (activities[j].duration < activities[j+1].duration) {
                struct Activity temp = activities[j];
                activities[j] = activities[j+1];
                activities[j+1] = temp;
            }
        }
    }

    // Select activities
    printf("Selected Activities:\n");
    int endTime = -1;
    for (int i = 0; i < n; i++) {
        if (activities[i].start > endTime) {
            printf("(%d, %d)\n", activities[i].start, activities[i].finish);
            endTime = activities[i].finish;
        }
    }
}

int main() {
    struct Activity activities[] = {{0,3}, {1,2}, {2,3}, {3,4}, {4,6}, {5,6}};
    int n = sizeof(activities)/sizeof(activities[0]);

    activitySelection(activities, n);

    return 0;
}


