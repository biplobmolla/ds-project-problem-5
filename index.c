#include <stdio.h>
#include <stdlib.h>

typedef struct Voter
{
    int id;
    struct Voter *next;
} Voter;

typedef struct Line
{
    int lineNum;
    int numVoters;
    Voter *head;
    struct Line *next;
} Line;

Voter *createVoter(int id)
{
    Voter *newVoter = (Voter *)malloc(sizeof(Voter));
    newVoter->id = id;
    newVoter->next = NULL;
    return newVoter;
}

Line *createLine(int lineNum)
{
    Line *newLine = (Line *)malloc(sizeof(Line));
    newLine->lineNum = lineNum;
    newLine->numVoters = 0;
    newLine->head = NULL;
    newLine->next = NULL;
    return newLine;
}

void addVoter(Line *line, int voterId)
{
    Voter *newVoter = createVoter(voterId);

    if (line->head == NULL)
    {
        line->head = newVoter;
    }
    else
    {
        Voter *current = line->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newVoter;
    }

    line->numVoters++;
}

void listVoter(int voterId, Line *voteCastedLine)
{
    Voter *newVoter = createVoter(voterId);

    if (voteCastedLine->head == NULL)
    {
        voteCastedLine->head = newVoter;
    }
    else
    {
        Voter *current = voteCastedLine->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newVoter;
    }

    voteCastedLine->numVoters++;
}

void removeVoter(Line *line, int voterId, Line *voteCastedLine)
{
    if (line->head == NULL)
    {
        return;
    }
    listVoter(voterId, voteCastedLine);
    Voter *removedVoter = line->head;
    line->head = line->head->next;
    free(removedVoter);

    line->numVoters--;
}

void displayStatus(Line *lines, int numLines, Line *voteCastedLine)
{
    system("cls");
    printf("Polling Center Status:\n");

    for (int i = 0; i < numLines; i++)
    {
        Line *currentLine = lines + i;
        printf("Line %d: %d voters\n", currentLine->lineNum, currentLine->numVoters);

        if (currentLine->head != NULL)
        {
            printf("Voters in Line %d: ", currentLine->lineNum);
            Voter *currentVoter = currentLine->head;
            while (currentVoter != NULL)
            {
                printf("%d ", currentVoter->id);
                currentVoter = currentVoter->next;
            }
            printf("\n");
        }
    }
    printf("Vote Casted Line: %d voters\n", voteCastedLine->numVoters);
    if (voteCastedLine->head != NULL)
    {
        printf("Voters in Line: ");
        Voter *currentVoter2 = voteCastedLine->head;
        while (currentVoter2 != NULL)
        {
            printf("%d ", currentVoter2->id);
            currentVoter2 = currentVoter2->next;
        }
        printf("\n");
    }
}

int main()
{
    int numLines, numVoters;

    printf("Enter the number of lines: ");
    scanf("%d", &numLines);

    printf("Enter the number of voters: ");
    scanf("%d", &numVoters);

    Line *lines = (Line *)malloc(numLines * sizeof(Line));
    Line *voteCastedLine = (Line *)malloc(sizeof(Line));
    voteCastedLine->head = NULL;
    voteCastedLine->numVoters = 0;
    for (int i = 0; i < numLines; i++)
    {
        lines[i] = *createLine(i + 1);
    }

    for (int i = 0; i < numVoters; i++)
    {
        int lineIndex = i % numLines;
        addVoter(&lines[lineIndex], i + 1);
    }

    while (numVoters > 0)
    {
        displayStatus(lines, numLines, voteCastedLine);

        printf("\nEnter the line number where the voter wants to cast the vote: ");
        int chosenLine;
        scanf("%d", &chosenLine);

        if (chosenLine <= 0 || chosenLine > numLines)
        {
            printf("Invalid line number. Please try again.\n");
            continue;
        }

        Line *chosenLinePtr = &lines[chosenLine - 1];

        if (chosenLinePtr->numVoters == 0)
        {
            printf("No voters in Line %d. Please choose another line.\n", chosenLine);
            continue;
        }

        removeVoter(chosenLinePtr, chosenLinePtr->head->id, voteCastedLine);
        numVoters--;
        printf("Voter successfully cast the vote.\n");
    }

    printf("\nAll voters have completed vote casting.\n");
    free(lines);

    return 0;
}
