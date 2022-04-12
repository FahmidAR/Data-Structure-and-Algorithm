#include <cstdio>

int main()
{
    int choice, n;

    while(1)
    {
        printf("1. Generate average case\n");
        printf("2. Generate best case\n");
        printf("3. Generate worst case\n");
        printf("4. Apply Merge sort\n");
        printf("5. Apply Quicksort\n");
        printf("6. Print array\n");
        printf("> ");
        scanf("%d", &choice);

        switch(choice)
        {
        case 1:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            break;

        case 2:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            break;

        case 3:
            printf("Number of elements: ");
            scanf("%d", &n);
            // do yourself
            break;

        case 4:
            printf("Applying merge sort\n");
            // do yourself
            // this should transform the given array into a sorted array
            printf("Time taken to finish: <your time>\n");
            break;

        case 5:
            printf("Applying quicksort\n");
            // do yourself
            // this should transform the given array into a sorted array
            printf("Time taken to finish: <your time>\n");
            break;

        case 6:
            printf("Array\n");
            // do yourself
            break;
        }
    }
}

