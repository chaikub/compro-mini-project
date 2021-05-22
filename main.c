#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct data{
    char id[14];
    char name[30];
    char faculty[20];
    char department[20];
    char email[20];
    char contact_number[20];
};

struct data it;

void SetColor(int ForgC)
{
     WORD wordcolor;
     HANDLE aHandleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO conscrbufinfo;
     if(GetConsoleScreenBufferInfo(aHandleOutput, &conscrbufinfo))
     {
          wordcolor = (conscrbufinfo.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(aHandleOutput, wordcolor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wordColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);

     HANDLE aHandleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

     COORD coordinates = {0, 0};

     DWORD counting;

     CONSOLE_SCREEN_BUFFER_INFO conscrbufinfo;

     SetConsoleTextAttribute(aHandleOutput, wordColor);
     if(GetConsoleScreenBufferInfo(aHandleOutput, &conscrbufinfo))
     {

          FillConsoleOutputCharacter(aHandleOutput, (TCHAR) 32, conscrbufinfo.dwSize.X * conscrbufinfo.dwSize.Y, coordinates, &counting);
          FillConsoleOutputAttribute(aHandleOutput, conscrbufinfo.wAttributes, conscrbufinfo.dwSize.X * conscrbufinfo.dwSize.Y, coordinates, &counting );

          SetConsoleCursorPosition(aHandleOutput, coordinates);
     }
     return;
}

void Setting_Color_And_Background(int ForgC, int BackC)
{
     WORD wordColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wordColor);
     return;
}

COORD coordinates = {0,0};
void x_and_y_coordinates(int x, int y){
    coordinates.X = x; coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void Frame(){
    int a, b;
    x_and_y_coordinates(0,0);
    printf("_");
    for(a = 1; a < 78; a++){
        x_and_y_coordinates(a, 0);
        printf("_");
    }
    x_and_y_coordinates(78,0);
    printf("_");
    for(a = 1; a < 25; a++){
        x_and_y_coordinates(78, a);
        if(a == 6){
            printf("|");
        }else{
            printf("|");
        }
    }
    x_and_y_coordinates(78, 25);
    printf("|");
    for(a = 77; a > 0; a--){
        x_and_y_coordinates(a,25);
        if(a == 35){
            printf("_");
        }else{
            printf("_");
        }
    }
    x_and_y_coordinates(0,25);
    printf("|");
    for(a = 24; a > 0; a--){
        x_and_y_coordinates(0,a);
        if(a == 6){
            printf("|");
        }else{
            printf("|");
        }
    }

    for(a = 1; a < 78; a++){
        x_and_y_coordinates(a,6);
        if(a == 35){
            printf("_");
        }else{
            printf("_");
        }
    }

    for(a = 7; a < 25; a++){
        x_and_y_coordinates(35,a);
        printf("|");
    }

}

void Reset_Window(){
    int a,b;
    for(a = 37; a < 78; a++){
        for(b = 7; b < 25; b++){
            x_and_y_coordinates(a,b);printf(" ");
        }
    }
    return;
}

void window(){
    Frame();
    x_and_y_coordinates(33,3);
    SetColor(35);
    printf("RECORD SYSTEM");
}


void print_heading(const char st[]){
    Setting_Color_And_Background(31,28);
    x_and_y_coordinates(38,8);printf("RECORD SYSTEM : %s",st);
    Setting_Color_And_Background(17,15);
}


void adding_IT(){
    Reset_Window();
    print_heading("Add New");
    int print = 37;
    FILE *openfile;
    openfile = fopen("record.txt","ab+");
    SetColor(35);
    if(openfile == NULL){
        MessageBox(0,"Error","Warning",0);
    }else{
        fflush(stdin);
        x_and_y_coordinates(print,10);printf("ID: ");gets(it.id);
        x_and_y_coordinates(print,12);printf("Name: ");gets(it.name);
        x_and_y_coordinates(print,14);printf("Faculty: ");gets(it.faculty);
        x_and_y_coordinates(print,16);printf("Department: ");gets(it.department);
        x_and_y_coordinates(print,18);printf("Email: ");gets(it.email);
        x_and_y_coordinates(print,20);printf("Contact Number: ");gets(it.contact_number);
        fwrite(&it, sizeof(it), 1, openfile);
//       fwrite("\n", sizeof("\n"), 1, openfile);
        x_and_y_coordinates(40,22); printf("New IT is Added Successfully");
    }
    SetColor(35);
    fclose(openfile);
    return;
}

void search_IT(){
    Reset_Window();
    print_heading("Search Record");
    SetColor(45);
    char id[15];
    int isFound = 0;
    x_and_y_coordinates(37,10);printf("Enter ID to Search: ");fflush(stdin);
    gets(id);
    FILE *openfile;
    openfile = fopen("record.txt","rb");
    while(fread(&it,sizeof(it),1,openfile) == 1){
        if(strcmp(id, it.id) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        x_and_y_coordinates(37,12);printf("The record is Found");
        x_and_y_coordinates(37,14);printf("ID: %s",it.id);
        x_and_y_coordinates(37,15);printf("Name: %s",it.name);
        x_and_y_coordinates(37,16);printf("Faculty: %s",it.faculty);
        x_and_y_coordinates(37,17);printf("Department: %s",it.department);
        x_and_y_coordinates(37,18);printf("Email: %s",it.email);
        x_and_y_coordinates(37,19);printf("Contact Number: %s",it.contact_number);
    }else{
        x_and_y_coordinates(37,12);printf("No record found in the database");
    }
    SetColor(35);
    fclose(openfile);
    return;
}

void modify_IT(){
    Reset_Window();
    print_heading("Modify Record");
    SetColor(45);
    char id[15];
    int isFound = 0, print = 37;
    x_and_y_coordinates(37,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(id);
    FILE *openfile;
    openfile = fopen("record.txt","rb+");
    while(fread(&it, sizeof(it),1,openfile) == 1){
        if(strcmp(id, it.id) == 0){
            fflush(stdin);
            x_and_y_coordinates(print,12);printf("ID: ");gets(it.id);
            x_and_y_coordinates(print,13);printf("Name: ");gets(it.name);
            x_and_y_coordinates(print,14);printf("Faculty: ");gets(it.faculty);
            x_and_y_coordinates(print,15);printf("Department: ");gets(it.department);
            x_and_y_coordinates(print,16);printf("Email: ");gets(it.email);
            x_and_y_coordinates(print,17);printf("Contact Number: ");gets(it.contact_number);
            fseek(openfile,-sizeof(it), SEEK_CUR);
            fwrite(&it,sizeof(it), 1, openfile);
            x_and_y_coordinates(40,22); printf("New IT is Updated Successfully");
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        x_and_y_coordinates(print, 12);printf("No Record Found");
    }
    fclose(openfile);
    SetColor(35);
    return;
}


void delete_IT(){
    Reset_Window();
    print_heading("Delete Record");
    SetColor(45);
    char id[15];
    int isFound = 0, print = 37;
    FILE *openfile, *temporary;
    openfile = fopen("record.txt","rb");
    temporary = fopen("temp.txt", "wb");
    fclose(openfile);
    fclose(temporary);
    remove("record.txt");
    rename("temp.txt","record.txt");
    x_and_y_coordinates(37,12);printf("All data has been successfully deleted.");
    SetColor(35);
    return;
}

void main_window(){
    int option;
    SetColor(35);
    int x = 2;
    while(1){
        x_and_y_coordinates(x,8);printf("1. Add");
        x_and_y_coordinates(x,10);printf("2. Search");
        x_and_y_coordinates(x,12);printf("3. Modify Record");
        x_and_y_coordinates(x,14);printf("4. Delete Record");
        x_and_y_coordinates(x,16);printf("5. Exit");
        x_and_y_coordinates(x,18);printf("Enter your Choice: ");
        scanf("%d",&option);
        switch(option){
            case 1:
                adding_IT();
                break;
            case 2:
                search_IT();
                break;
            case 3:
                modify_IT();
                break;
            case 4:
                delete_IT();
                break;
            case 5:
                exit(0);
                break;
            default:
                break;
        }

    }

}

int main(){
    ClearConsoleToColors(17,15);
    SetConsoleTitle("RECORD SYSTEM");
    window();
    main_window();
    return 0;
}

