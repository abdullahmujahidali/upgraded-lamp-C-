#include <iostream>
#include <fstream> // file functions
using namespace std;

// named constant for array size goes here
#define SIZE 11

// structure definition goes here
struct Player{
int jersey;
int rating;
};

// begin functions

int searchPlayer(int jersey,Player players[],int playerCount){
int index = -1;
for(int i=0;i<playerCount;i++){
if(players[i].jersey==jersey){
index = i;
return index; // stop search immediately
}
}
return index; // case when player not found, return -1
}


void outPutPlayersAboveRating(int rating,Player players[],int playerCount){
if(rating<1||rating>9){
cout<<endl<<"Invalid rating"<<endl;
return; // exit
}

cout<<endl<<"Players above "<<rating<<" rating: "<<endl;
for(int i=0;i<playerCount;i++){
if(players[i].rating>rating){
cout<<"Jersey number: "<<players[i].jersey<<", Rating: "<<players[i].rating<<endl;
}
}

}


void updatePlayerRating(int jersey,int new_rating,Player players[],int playerCount){
if(new_rating<1||new_rating>9){
cout<<endl<<"Rating not updated. Invalid rating"<<endl;
return; // exit
}
int index =searchPlayer(jersey,players,playerCount);
if(index==-1){
cout<<endl<<"Rating not updated. No such player"<<endl;
return; // exit
}
players[index].rating = new_rating; //update rating
}

int addAplayer(int jersey,int rating,Player players[],int playerCount){
if(jersey<0||jersey>99||rating<1||rating>9){
cout<<endl<<"Player not added. Invalid jersey or rating"<<endl;
return playerCount;
}

if(searchPlayer(jersey,players,playerCount)!=-1){
cout<<endl<<"Player not added. Jersey Number already taken"<<endl;
return playerCount;
}

if(playerCount<SIZE){
Player p;
p.jersey = jersey;
p.rating = rating;
players[playerCount] = p;
playerCount++;
}else{
cout<<endl<<"Error: Too many players"<<endl;
}
return playerCount;
}


int readFileToArray(Player players[],int playerCount){
ifstream infile("input.txt");
int jersey,rating;
while (infile >>jersey>>rating)
{
playerCount = addAplayer(jersey,rating,players,playerCount);
}
return playerCount;
}

void outputRoster(Player players[],int playerCount){
if(playerCount<1)
cout<<endl<<"Roster is empty"<<endl;
else{
cout<<"ROSTER"<<endl;
for(int i=0;i<playerCount;i++)
cout<<"Player "<<i+1<<" -- Jersey number: "<<players[i].jersey<<", Rating: "<<players[i].rating<<endl;
}

}

char displayMenu(){
cout<<"MENU"<<endl;
cout<<"a - Add player"<<endl;
cout<<"d - Remove player"<<endl;
cout<<"u - Update player rating"<<endl;
cout<<"r - Output players above a rating"<<endl;
cout<<"o - Output roster"<<endl;
cout<<"q - Quit"<<endl;
cout<<endl<<"Choose an option: "<<endl;
char choice;
cin>>choice;
return choice;
}

int deletePlayer(int jersey,Player players[],int playerCount){
if(playerCount<1)
cout<<endl<<"Roster is empty, no such player"<<endl;
else{

int index = searchPlayer(jersey,players,playerCount);
if(index==-1){
cout<<endl<<"No such player"<<endl;
}else{
// overwrite the player
for(int i=index;i<playerCount-1;i++){
players[i] = players[i+1]; // overwrite by shifting left
}
playerCount--; // reduce the count by 1

}


}
return playerCount;
}

int main()
{
Player players[SIZE]; // array to hold player information
int playerCount = 0; // keeps track of how many players are stored in the array
char menuOp;
int playerJersy; // used for interactive user input
int playerRating;
playerCount = readFileToArray(players,playerCount);

do{
menuOp = displayMenu();
switch(menuOp){
case 'a':
cout<<"Enter a new player's jersey number: "<<endl;cin>>playerJersy;
cout<<"Enter the player's rating: "<<endl;cin>>playerRating;
playerCount = addAplayer(playerJersy,playerRating,players,playerCount);
break;
case 'd':
cout<<"Enter player's jersey number to remove: "<<endl;cin>>playerJersy;
playerCount = deletePlayer(playerJersy,players,playerCount);
break;
case 'u':
cout<<"Enter player's jersey number to update rating: "<<endl;cin>>playerJersy;
cout<<"Enter player's new rating: "<<endl;cin>>playerRating;
updatePlayerRating(playerJersy,playerRating,players,playerCount);
break;
case 'r':
cout<<"Enter a rating: "<<endl;cin>>playerRating;
outPutPlayersAboveRating(playerRating,players,playerCount);
break;
case 'o':
outputRoster(players,playerCount);
break;
case 'q':
cout<<"Quit successful."<<endl;
break;
}

}while(menuOp!='q');

return 0;
}
