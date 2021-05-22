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

struct data dat;

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
void x_y_coordinates(int x, int y){
    coordinates.X = x; coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void Frame(){
    int a;
    x_y_coordinates(0,0);
    printf("_");
    for(a = 1; a < 78; a++){
        x_y_coordinates(a, 0);
        printf("_");
    }
    x_y_coordinates(78,0);
    printf("_");
    for(a = 1; a < 25; a++){
        x_y_coordinates(78, a);
        if(a == 6){
            printf("|");
        }else{
            printf("|");
        }
    }
    x_y_coordinates(78, 25);
    printf("|");
    for(a = 77; a > 0; a--){
        x_y_coordinates(a,25);
        if(a == 35){
            printf("_");
        }else{
            printf("_");
        }
    }
    x_y_coordinates(0,25);
    printf("|");
    for(a = 24; a > 0; a--){
        x_y_coordinates(0,a);
        if(a == 6){
            printf("|");
        }else{
            printf("|");
        }
    }

    for(a = 1; a < 78; a++){
        x_y_coordinates(a,6);
        if(a == 35){
            printf("_");
        }else{
            printf("_");
        }
    }

    for(a = 7; a < 25; a++){
        x_y_coordinates(35,a);
        printf("|");
    }
}

void Reset_Window(){
    int a,b;
    for(a = 37; a < 78; a++){
        for(b = 7; b < 25; b++){
            x_y_coordinates(a,b);printf(" ");
        }
    }
    return;
}

void window(){
    Frame();
    x_y_coordinates(33,3);
    SetColor(35);
    printf("RECORD SYSTEM");
}

void print_heading(const char st[]){
    Setting_Color_And_Background(35,15);
    x_y_coordinates(38,8);printf("RECORD SYSTEM : %s",st);
    Setting_Color_And_Background(17,15);
}

void adding_dat(){
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
        x_y_coordinates(print,10);printf("ID: ");gets(dat.id);
        x_y_coordinates(print,12);printf("Name: ");gets(dat.name);
        x_y_coordinates(print,14);printf("Faculty: ");gets(dat.faculty);
        x_y_coordinates(print,16);printf("Department: ");gets(dat.department);
        x_y_coordinates(print,18);printf("Email: ");gets(dat.email);
        x_y_coordinates(print,20);printf("Contact Number: ");gets(dat.contact_number);
        fwrite(&dat, sizeof(dat), 1, openfile);
//       fwrite("\n", sizeof("\n"), 1, openfile);
        x_y_coordinates(40,22); printf("New record is Added Successfully");
    }
    SetColor(35);
    fclose(openfile);
    return;
}

void search_dat(){
    Reset_Window();
    print_heading("Search Record");
    SetColor(45);
    char id[15];
    int isFound = 0;
    x_y_coordinates(37,10);printf("Enter ID to Search: ");fflush(stdin);
    gets(id);
    FILE *openfile;
    openfile = fopen("record.txt","rb");
    while(fread(&dat,sizeof(dat),1,openfile) == 1){
        if(strcmp(id, dat.id) == 0){
            isFound = 1;
            break;
        }
    }
    if(isFound == 1){
        x_y_coordinates(37,12);printf("The record is Found");
        x_y_coordinates(37,14);printf("ID: %s",dat.id);
        x_y_coordinates(37,15);printf("Name: %s",dat.name);
        x_y_coordinates(37,16);printf("Faculty: %s",dat.faculty);
        x_y_coordinates(37,17);printf("Department: %s",dat.department);
        x_y_coordinates(37,18);printf("Email: %s",dat.email);
        x_y_coordinates(37,19);printf("Contact Number: %s",dat.contact_number);
    }else{
        x_y_coordinates(37,12);printf("No record found in the database");
    }
    SetColor(35);
    fclose(openfile);
    return;
}

void modify_dat(){
    Reset_Window();
    print_heading("Modify Record");
    SetColor(45);
    char id[15];
    int isFound = 0, print = 37;
    x_y_coordinates(37,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(id);
    FILE *openfile;
    openfile = fopen("record.txt","rb+");
    while(fread(&dat, sizeof(dat),1,openfile) == 1){
        if(strcmp(id, dat.id) == 0){
            fflush(stdin);
            x_y_coordinates(print,12);printf("ID: ");gets(dat.id);
            x_y_coordinates(print,13);printf("Name: ");gets(dat.name);
            x_y_coordinates(print,14);printf("Faculty: ");gets(dat.faculty);
            x_y_coordinates(print,15);printf("Department: ");gets(dat.department);
            x_y_coordinates(print,16);printf("Email: ");gets(dat.email);
            x_y_coordinates(print,17);printf("Contact Number: ");gets(dat.contact_number);
            fseek(openfile,-sizeof(dat), SEEK_CUR);
            fwrite(&dat,sizeof(dat), 1, openfile);
            x_y_coordinates(40,22); printf("Record is Updated Successfully");
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        x_y_coordinates(print, 12);printf("No Record Found");
    }
    fclose(openfile);
    SetColor(35);
    return;
}

void delete_dat(){
    Reset_Window();
    print_heading("Delete Record");
    SetColor(45);
    FILE *openfile, *temporary;
    openfile = fopen("record.txt","rb");
    temporary = fopen("temp.txt", "wb");
    fclose(openfile);
    fclose(temporary);
    remove("record.txt");
    rename("temp.txt","record.txt");
    x_y_coordinates(37,12);printf("All data has been successfully deleted.");
    SetColor(35);
    return;
}

void main_window(){
    int option;
    SetColor(35);
    int x = 2;
    while(1){
        x_y_coordinates(x,8);printf("1. Add");
        x_y_coordinates(x,10);printf("2. Search");
        x_y_coordinates(x,12);printf("3. Modify Record");
        x_y_coordinates(x,14);printf("4. Delete Record");
        x_y_coordinates(x,16);printf("5. Exit");
        x_y_coordinates(x,18);printf("Enter your Choice: ");
        scanf("%d",&option);
        switch(option){
            case 1:
                adding_dat();
                break;
            case 2:
                search_dat();
                break;
            case 3:
                modify_dat();
                break;
            case 4:
                delete_dat();
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

