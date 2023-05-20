#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <cstring>
using namespace std;
 
int sudoku[10][10];
int problem[10][10];
int row[10][10],column[10][10],block[4][4][10];
int known[10][10];
int f=0;
int cnt=0;
const int colour [10]={0,3,4,13,5,11,6,14,2,9};
void init(){
	for (int i=1;i<=9;i++){
		for (int j=1;j<=9;j++){
			if (sudoku[i][j]){
				row[i][sudoku[i][j]]=1;
				column[j][sudoku[i][j]]=1;
				block[(i-1)/3+1][(j-1)/3+1][sudoku[i][j]]=1;
			}
		}
	}
}
void print(int sudoku[][10]){
	cout<<"    1   2   3    4   5   6    7   8   9   "<<endl;
	cout<<"   =====================================  "<<endl;
	for (int i=1;i<=9;i++){
		cout<<i<<"|| ";
		for (int j=1;j<=9;j++){
			if (sudoku[i][j]){
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),colour[sudoku[i][j]]);
				cout<<sudoku[i][j];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			}
			else cout<<" ";
			if (j%3!=0) cout<<" | ";
			else cout<<" || ";
		}
		cout<<endl;
		if (i%3!=0)cout<<"   -------------------------------------  "<<endl;
		else       cout<<"   =====================================  "<<endl;
	}
 
}
void search(int x,int y){
	if (f) return;
	if (known[x][y]){
		search((9*x+y-9)/9+1,y%9+1);
	}
	else{
		if (x==10 && y==1) {
			f=1;
			cnt++;
		}
		for (int j=1;j<40;j++){
			int i=rand()%9+1;
			if (row[x][i]==0 && column[y][i]==0 && block[(x-1)/3+1][(y-1)/3+1][i]==0){
				sudoku[x][y]=i;
				row[x][i]=1;
				column[y][i]=1;
				block[(x-1)/3+1][(y-1)/3+1][i]=1;
				search((9*x+y-9)/9+1,y%9+1);
				if (!f){
					sudoku[x][y]=0;
					row[x][i]=0;
					column[y][i]=0;
					block[(x-1)/3+1][(y-1)/3+1][i]=0;
				}
			}
		}
	}
}
void search2(int x,int y){
	if (x!=10 && known[x][y]){
		search2((9*x+y-9)/9+1,y%9+1);
	}
	else{
		if (x==10 && y==1){
			cnt++;
		}
		else
		for (int i=1;i<=9;i++){
			if (row[x][i]==0 && column[y][i]==0 && block[(x-1)/3+1][(y-1)/3+1][i]==0){
				sudoku[x][y]=i;
				row[x][i]=1;
				column[y][i]=1;
				block[(x-1)/3+1][(y-1)/3+1][i]=1;
				search2((9*x+y-9)/9+1,y%9+1);
				sudoku[x][y]=0;
				row[x][i]=0;
				column[y][i]=0;
				block[(x-1)/3+1][(y-1)/3+1][i]=0;
			}
		}
	}
}
 
int main(){
	srand(time(0)*time(0)-0x5e2d6aa*rand()+time(0)*338339);
	search(1,1);
	int sum=0;
	int sudoku2[10][10]={0};
	for (int i=1;i<=9;i++){
		for (int j=1;j<=9;j++){
			problem[i][j]=sudoku2[i][j]=sudoku[i][j];
		}
	}
	cnt=0;
	while (cnt!=1){
		for (int i=1;i<=9;i++){
			for (int j=1;j<=9;j++){
				known[i][j]=1;
			}
		}
		sum=0;
		while (sum<50){
			int x=rand()%9+1,y=rand()%9+1;
			if (known[x][y]==0) continue;
			else {
				sum++;
				known[x][y]=0;
			}
		}
		for (int i=1;i<=9;i++){
			for (int j=1;j<=9;j++){
				if (known[i][j]==0) sudoku[i][j]=problem[i][j]=0; 
			}
		}
		cnt=0;
		f=0;
		memset(row,0,sizeof(row));
		memset(column,0,sizeof(column));
		memset(block,0,sizeof(block));
		init();
		search2(1,1);
		for (int i=1;i<=9;i++){
			for (int j=1;j<=9;j++){
				sudoku[i][j]=sudoku2[i][j];
				if (cnt!=1) problem[i][j]=sudoku2[i][j];
			}
		}
	}
	print(problem);
    char inputFilename[] = "sudoku_input.txt";

    // 1. 生成不重复的数独终局至文件
    ofstream inputFile;
    inputFile.open(inputFilename);
    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= 9; ++j) {
            inputFile << problem[i][j] << " ";
        }
        inputFile << endl;
    }
    inputFile.close();
	return 0;
}