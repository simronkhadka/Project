#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

//structure to add contact details
struct Contact
{
    char name[100];
    char phone[15];
    char address[30];
};

//add function to add contact details
void add()
{
    //1. create a contact
    struct Contact con;
    //2. input contact details
    printf("Please enter name:>");
    scanf(" %[^\n]", con.name);
    printf("Please enter phone:>");
    scanf(" %s", con.phone);
    printf("Please enter address:>");
    scanf(" %[^\n]", con.address);

    //3. save contact details to file
    FILE* pf = fopen("Contact/contact.txt", "a+");
    if(pf == NULL)
    {
        printf("open file failed!\n");
        return;
    }
    fprintf(pf, "%s; %s; %s;\n", con.name, con.phone, con.address);
    fclose(pf);
    pf = NULL;
    printf("Add successfully!\n");
}

//delete function to delete contact details
void deleteByName()
{
    //1. input name to delete
    char name[100];
    printf("Please enter name to delete:>");
    scanf(" %[^\n]", name);

    //2. open file
    FILE* pf = fopen("Contact/contact.txt", "r");
    if(pf == NULL)
    {
        printf("open file failed!\n");
        return;
    }

    //3. create a temp file
    FILE* pfTemp = fopen("Contact/temp.txt", "w");
    if(pfTemp == NULL)
    {
        printf("open file failed!\n");
        return;
    } 
    //4. read file and write to temp file
    char buff[1024] = {0};
    while(fgets(buff, 1024, pf) != NULL)
    {
        //5. compare name
        if(strncmp(buff, name, strlen(name)) == 0)
        {
            continue;
        }
        //6. write to temp file
        fputs(buff, pfTemp);

    }

    //7. close file
    fclose(pf);
    pf = NULL;
    fclose(pfTemp);
    pfTemp = NULL;

    //8. remove old file
    remove("../Contact/contact.txt");

    //9. rename temp file to old file
    rename("Contact/temp.txt", "Contact/contact.txt");

    printf("Delete successfully!\n");
}

//function to search contacts

void searchByName()
{
    //1. input name to search
    char name[100];
    printf("Please enter name to search:>");
    scanf(" %[^\n]", name);

    //2. open file
    FILE* pf = fopen("Contact/contact.txt", "r");
    if(pf == NULL)
    {
        printf("open file failed!\n");
        return;
    }

    //3. read file and compare name
    struct Contact con;
    int flag =1;
        while(fscanf(pf, "%[^;]; %[^;]; %[^;];\n", con.name, con.phone, con.address) == 3)
    {
        //3. compare number
        if(strcmp(con.name, name) == 0)
        {
            flag = 0;
            printf("\nName: %s\nPhone: %s\nAddress: %s\n", con.name, con.phone, con.address);
            sleep(2);
            break;
        }
    }

    if(flag ==1)
        printf("No Records Found\n");
    //5. close file
    fclose(pf);
    pf = NULL;

    //press enter to continue
    printf("Press Enter to continue\n");
    while(getchar() != '\n');
    getchar();
    system("clear");
}

void searchByNumber()
{
  struct Contact con;
    //1. input number to search
    char number[15];
    printf("Please enter number to search:>");
    scanf(" %s", number);

    //2. open file
    FILE* pf = fopen("Contact/contact.txt", "r");
    if(pf == NULL)
    {
        printf("open file failed!\n");
        return;
    }

    int flag =1;
    while(fscanf(pf, "%[^;]; %[^;]; %[^;];", con.name, con.phone, con.address) == 3)
    {
        //3. compare number
        if(strcmp(con.phone, number) == 0)
        {
            flag = 0;
            printf("\nName: %s\nPhone: %s\nAddress: %s\n", con.name, con.phone, con.address);
            sleep(2);
            break;
        }
    }
    if(flag==1)
        printf("No such contact found\n");
    sleep(2);


    //4. close file
        fclose(pf);
        pf=NULL;

        //press enter to continue
        printf("Press enter to continue\n");
        while(getchar() != '\n');
        getchar();
}

void search()
{
    system("clear");
    //choose search by name or number
    printf("Do you want to search by Name or Number?\n");
    printf("1. Name \n2. Number\n");
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            searchByName();
            break;
        case 2:
            searchByNumber();
            break;
        default:
            printf("Invalid choice\n");
    }
}

//function to show all the contacts in the file
void showContacts()
{
    //1. open file
    FILE* pf = fopen("Contact/contact.txt", "r");
    if(pf == NULL)
    {
        printf("open file failed!\n");
        return;
    }

    //2. read file and show all contacts 
    struct Contact con;
    int flag =1;
    int id=1;
        while(fscanf(pf, "%[^;]; %[^;]; %[^;]; ", con.name, con.phone, con.address) == 3)
    {
            flag =0;
            printf("\nS.N: %d\nName: %s\nPhone: %s\nAddress: %s\n",id, con.name, con.phone, con.address);
            id++;
    }

    if(flag==1)
        printf("No Records Found\n");
    //3. close file
    fclose(pf);
    pf = NULL;

    //press enter to continue
    printf("\nPress enter to continue\n");
    while(getchar() != '\n');
    getchar();
    system("clear");
}

//function to clear the whole contact file
void clear()
{
    //1. open file
    FILE* pf = fopen("Contact/contact.txt", "w");
    if(pf == NULL)
    {
        printf("open file failed!\n");
        return;
    }

    //2. close file
    fclose(pf);
    pf = NULL;
    printf("Contact Cleared Successfully!\n");

    //press enter to continue
    printf("Press enter to continue\n");
    while(getchar() != '\n');
    getchar();
    system("clear");
}

//function to modify the contact
void modifyByNumber()
{
    system("clear");
    //1. input number to modify
    char number[15];
    printf("Please enter number to modify:>");
    scanf(" %s", number);

    //2. open file
    FILE* pf = fopen("Contact/contact.txt", "r");
    if(pf == NULL)
    {
        printf("open file failed!\n");
        return;
    }

    //3. read file
    struct Contact con;
    int flag =1;
    FILE* pfTemp = fopen("Contact/temp.txt", "w");
        while(fscanf(pf, "%[^;]; %[^;]; %[^;];\n", con.name, con.phone, con.address) == 3)
    {
        //3. compare number
        if(strcmp(con.phone, number) == 0)
        {
            printf("Enter the new Name : ");
            scanf(" %[^\n]", con.name);
            printf("Enter the new Phone number : ");
            scanf(" %s", con.phone);
            printf("Enter the new Address : ");
            scanf(" %[^\n]", con.address);
            flag = 0;
        }
        //5. write to temp file
        fprintf(pfTemp, "%s; %s; %s;\n", con.name, con.phone, con.address);
    }

    //7. close file
    fclose(pf);
    pf = NULL;
    fclose(pfTemp);
    pfTemp = NULL;

    //8. remove old file
    remove("Contact/contact.txt");

    //9. rename temp file to old file
    rename("Contact/temp.txt", "Contact/contact.txt");

    if(flag==1){
        printf("No Records Found\n");
        return;
    }
    else
        printf("Modify successfully!\n");

    //press enter to continue
    printf("Press enter to continue\n");
    while(getchar() != '\n');
    getchar();
    system("clear");
}

void modifyByName()
{
    system("clear");
    //1. input name to modify
    char name[20];
    printf("Please enter name to modify:>");
    scanf(" %[^\n]", name);

    //2. open file
    FILE* pf = fopen("Contact/contact.txt", "r");
    if(pf == NULL)
    {
        printf("open file failed!\n");
        return;
    }

    //3. read file
    struct Contact con;
    int flag =1;
    FILE* pfTemp = fopen("Contact/temp.txt", "w");
    while(fscanf(pf, "%[^;]; %[^;]; %[^;];\n", con.name, con.phone, con.address) == 3)
    {
        //4. compare name
        if(strcmp(con.name, name) == 0)
        {
            flag = 0;
            printf("Please enter new name:>");
            scanf(" %[^\n]", con.name);
            printf("Please enter new phone:>");
            scanf(" %s", con.phone);
            printf("Please enter new address:>");
            scanf(" %[^\n]", con.address);
            fprintf(pfTemp, "%s; %s; %s;\n", con.name, con.phone, con.address);
            continue;
        }

        //5. write to temp file
        fprintf(pfTemp, "%s; %s; %s;\n", con.name, con.phone, con.address);
    }

    //7. close file
    fclose(pf);
    pf = NULL;
    fclose(pfTemp);
    pfTemp = NULL;

    //8. remove old file
    remove("Contact/contact.txt");

    //9. rename temp file to old file
    rename("Contact/temp.txt", "Contact/contact.txt");

    if(flag==1){
        printf("No Records Found\n");
        return;
    }
    else
        printf("Modify successfully!\n");
}

void modify()
{
    system("clear");
    //choose modify by name or number
    printf("Do you want to modify by Name or Number?\n");
    printf("1. Name \n2. Number\n");
    int choice;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
            modifyByName();
            break;
        case 2:
            modifyByNumber();
            break;
        default:
            printf("Invalid choice\n");
    }
}

int main()
{

    int input = 0;
    while(1)
    {
        printf("#################################\n");
        printf("## 1. add           2. delete ##\n");
        printf("## 3. search        4. modify ##\n");
        printf("## 5. show          6. clear  ##\n");
        printf("## 7. exit                    ##\n");
        printf("#################################\n");
        printf("Please select:>");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            system("clear");
            add();
            break;
        case 2:
        system("clear");
            deleteByName();
            break;
        case 3:
        system("clear");
            search();
            break;
        case 4:
            modify();
            break;
        case 5:
        system("clear");
            showContacts();
            break;
        case 6:
            clear();
            break;
        case 7:
            printf("Exit successfully!\n");
            sleep(2);
            return 0;
        default:
            printf("Invalid input!\n");
            sleep(2);
            system("clear");
            break;
        }
    }
    return 0;
}