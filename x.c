#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_data(int block_allocation[], int processSize[], int n_process, int blockSize[], int n_Blocks)
{
    int fragmentation = 0;

    printf("Pro. No.\tProcess Size \tAllocated Block no.\n");
    for (int i = 0; i < n_process; i++)
    {
        printf("%d\t\t%d\t", i + 1, processSize[i]);
        if (block_allocation[i] != -1)
        {
            printf("\t %d", block_allocation[i] + 1);
        }
        else
        {
            printf("\t Not Allocated");
        }
        printf("\n");
    }

    for (int i = 0; i < n_Blocks; i++)
    {
        fragmentation = blockSize[i] + fragmentation;
    }

    printf("\nTotal fragmmentation : %d\n", fragmentation);
    printf("Averagefragmmentation : %f\n", (float)fragmentation / n_Blocks);

    printf("Wasted block  is : ");
    int check = 0;
    for (int i = 0; i < n_Blocks; i++)
    {
        int found = 0;
        for (int j = 0; j < n_process; j++)
        {
            if (block_allocation[j] == i)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            check = 1;
            printf("B%d[%d],", i + 1, blockSize[i]);
        }
    }
    if (check == 0)
        printf("0");
    printf("\n");
}

void bestFit(int blockSize[], int n_Blocks, int processSize[], int n_process)
{
    int block_allocation[n_process];
    memset(block_allocation, -1, sizeof(block_allocation));

    for (int i = 0; i < n_process; i++)
    {
        int Best_posi = -1;
        for (int j = 0; j < n_Blocks; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (Best_posi == -1)
                {
                    Best_posi = j;
                }
                else if (blockSize[Best_posi] > blockSize[j])
                {
                    Best_posi = j;
                }
            }
        }
        if (Best_posi != -1)
        {
            block_allocation[i] = Best_posi;
            blockSize[Best_posi] -= processSize[i];
        }
    }
    get_data(block_allocation, processSize, n_process, blockSize, n_Blocks);
}

void firstFit(int blockSize[], int n_Blocks, int processSize[], int n_process)
{
    int block_allocation[n_process];
    memset(block_allocation, -1, sizeof(block_allocation));

    for (int i = 0; i < n_process; i++)
    {
        for (int j = 0; j < n_Blocks; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                block_allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    get_data(block_allocation, processSize, n_process, blockSize, n_Blocks);
}
void worstFit(int blockSize[], int n_Blocks, int processSize[], int n_process)
{
    int block_allocation[n_process];
    // Initially no block is assigned to any process
    memset(block_allocation, -1, sizeof(block_allocation));

    // pick each process and find suitable memory_Blocks
    // according to its size ad assign to it
    for (int i = 0; i < n_process; i++)
    {
        // Find the best fit block for current process
        int Best_posi = -1;
        for (int j = 0; j < n_Blocks; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (Best_posi == -1)
                    Best_posi = j;
                else if (blockSize[Best_posi] < blockSize[j])
                    Best_posi = j;
            }
        }

        // If we could find a block for current process
        if (Best_posi != -1)
        {
            // allocate block j to p[i] process
            block_allocation[i] = Best_posi;

            // Reduce available memory in this block.
            blockSize[Best_posi] -= processSize[i];
        }
    }
    get_data(block_allocation, processSize, n_process, blockSize, n_Blocks);
}
int main()
{
    int n_process, n_Blocks, choice;

    printf("\n************** Which Algorithm would you like to Use .... ******************\n\n");
    printf("1. Best Fit\n2. First Fit\n3. Worst Fit\n4. Exit\n\n");
    printf("Enter your Algorithm no. You want to use... : ");
    scanf("%d", &choice);

    if (choice == 4)
    {
        exit(0);
    }

    printf("Enter number of memory_Blocks : ");
    scanf("%d", &n_Blocks);
    int *blockSize = (int *)malloc(n_Blocks * sizeof(int));
    printf("Enter the size of the memory_Blocks \n");
    for (int i = 0; i < n_Blocks; i++)
    {
        printf("Block no. %d :", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("\nEnter number of processes : ");
    scanf("%d", &n_process);
    int *processSize = (int *)malloc(n_process * sizeof(int));
    printf("Enter the size of the processes (kb)\n");
    for (int i = 0; i < n_process; i++)
    {
        printf("Process no. %d :", i + 1);
        scanf("%d", &processSize[i]);
    }
    printf("\n\n");
    switch (choice)
    {
    case 1:
    {
        printf("BEST_FIT\n");
        bestFit(blockSize, n_Blocks, processSize, n_process);
        break;
    }
    case 2:
    {
        printf("\nFIRST_FIT\n");
        firstFit(blockSize, n_Blocks, processSize, n_process);
        break;
    }

    case 3:
    {
        printf("\nWORST_FIT\n");
        worstFit(blockSize, n_Blocks, processSize, n_process);
        break;
    }
    default:
    {
        break;
    }
    }
    free(blockSize);
    free(processSize);
    printf("\nMemory Deallocation SUCCESSFUL......\n");

    return 0;
}