#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for tasks
struct Task {
    char title[100];
    char description[500];
    char due_date[20];
    int status; // 0 for incomplete, 1 for complete
};

// add a task
void addTask(struct Task* tasks, int* taskCount) {
    printf("Enter task title: ");
    scanf(" %[^\n]", tasks[*taskCount].title);
    
    printf("Enter task description: ");
    scanf(" %[^\n]", tasks[*taskCount].description);
    
    printf("Enter due date (YYYY-MM-DD): ");
    scanf(" %s", tasks[*taskCount].due_date);

    tasks[*taskCount].status = 0; // Set status as incomplete
    (*taskCount)++;
}

// display a list of tasks
void displayTasks(struct Task* tasks, int taskCount) {
    printf("Task List:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. Title: %s\n   Description: %s\n   Due Date: %s\n   Status: %s\n",
               i + 1, tasks[i].title, tasks[i].description, tasks[i].due_date,
               tasks[i].status ? "Complete" : "Incomplete");
    }
}

// mark a task as completed
void markTaskComplete(struct Task* tasks, int taskCount) {
    displayTasks(tasks, taskCount);

    int taskNumber;
    printf("Enter the number of the task to mark as complete: ");
    scanf("%d", &taskNumber);

    if (taskNumber > 0 && taskNumber <= taskCount) {
        tasks[taskNumber - 1].status = 1; // Set status as complete
        printf("Task marked as complete.\n");
    } else {
        printf("Invalid task number.\n");
    }
}

// delete a task
void deleteTask(struct Task* tasks, int* taskCount) {
    displayTasks(tasks, *taskCount);

    int taskNumber;
    printf("Enter the number of the task to delete: ");
    scanf("%d", &taskNumber);

    if (taskNumber > 0 && taskNumber <= *taskCount) {
        // Shift tasks to fill the gap
        for (int i = taskNumber - 1; i < *taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        (*taskCount)--;
        printf("Task deleted.\n");
    } else {
        printf("Invalid task number.\n");
    }
}

// Function to save tasks to a file
void saveTasksToFile(struct Task* tasks, int taskCount) {
    FILE* file = fopen("tasks.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s;%s;%s;%d\n", tasks[i].title, tasks[i].description,
                tasks[i].due_date, tasks[i].status);
    }

    fclose(file);
    printf("Tasks saved to file.\n");
}

// Function to load tasks from a file
void loadTasksFromFile(struct Task* tasks, int* taskCount) {
    FILE* file = fopen("tasks.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while (fscanf(file, " %99[^;];%499[^;];%19[^;];%d\n", tasks[*taskCount].title,
                  tasks[*taskCount].description, tasks[*taskCount].due_date,
                  &tasks[*taskCount].status) == 4) {
        (*taskCount)++;
    }

    fclose(file);
    printf("Tasks loaded from file.\n");
}

int main() {
    struct Task tasks[100]; // Assuming a maximum of 100 tasks
    int taskCount = 0;

    // Load tasks from file at the beginning
    loadTasksFromFile(tasks, &taskCount);

    int choice;
    do {
        printf("\n1. Add Task\n2. Display Tasks\n3. Mark Task Complete\n4. Delete Task\n5. Save Tasks\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                displayTasks(tasks, taskCount);
                break;
            case 3:
                markTaskComplete(tasks, taskCount);
                break;
            case 4:
                deleteTask(tasks, &taskCount);
                break;
            case 5:
                saveTasksToFile(tasks, taskCount);
                break;
            case 0:
                printf("Exiting the Task Manager.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}
