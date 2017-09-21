#include "iostream"
#include <time.h>
#include <conio.h>

using namespace std;

enum eDir {STOP = 0, DROITE = 1, GAUCHE = 2, HAUT = 3, BAS = 4 };

class cBall{
private:
	int initialX;
	int initialY;

	int X;
	int Y;


public:
	cBall(int posX, int posY){
		X = randValue(posX);
		Y = randValue(posY);
	}

	inline int getX(){ return X; }
	inline int getY(){ return Y; }

	void Reset(int w, int h){
		X = randValue(w);
		Y = randValue(h);
	}

	int randValue(int maxVal){
		int val = (rand()%maxVal-1) + 1;
		return val;
	}
};






class cSnake{
private:
	int X;
	int Y;
	int originalX;
	int originalY;
	eDir direction;
	int lQueue;
	struct longQueue{
		int valX;
		int valY;
	};

	longQueue tabQueue[50];

	


public:
	cSnake(int posX, int posY){
		lQueue = 0;
		direction = STOP;
		originalX = posX;
		originalY = posY;
		X = posX;
		Y = posY;
		tabQueue[0].valX = posX;
		tabQueue[0].valY = posY;
	}

	void Reset(){
		lQueue = 0;
		X = originalX;
		Y = originalY;
	}

	void move(){

		for(int i=0; i<lQueue; i++){
			int val = lQueue - i;

			if(val > 0){
				tabQueue[val].valX = tabQueue[val-1].valX;
				tabQueue[val].valY = tabQueue[val-1].valY;
			}
		}


		switch(direction){
		case GAUCHE:
			X--;
			break;
		case DROITE:
			X++;
			break;
		case HAUT:
			Y--;
			break;
		case BAS:
			Y++;
			break;
		default:
			break;
		}	

		tabQueue[0].valX = X;
		tabQueue[0].valY = Y;

	}

	void changeDirection(eDir dir){
		direction = dir;
	}

	void scoreUp(){
		lQueue++;
		tabQueue[lQueue].valX = X;
		tabQueue[lQueue].valY = Y;
	}

	int getTabX(int val){
		int valX = tabQueue[val].valX;
		return valX;
	}

	int getTabY(int val){
		int valY = tabQueue[val].valY;
		return valY;
	}

	inline int getX(){ return X; }
	inline int getY(){ return Y; }
	inline eDir getDir(){ return direction; }
	inline int getlQueue() { return lQueue; }
	inline void moveUp(){ Y--; }
	inline void moveDown(){ Y++; }
	inline void moveLeft(){ X--; }
	inline void moveRight(){ X++; }

};







class cSystemManager{
private:
	int width;
	int height;
	bool quit;
	char up, down, right, left;

	cBall *ball;
	cSnake *snake;

public:

	cSystemManager(int w, int h){
		width = w;
		height = h;
		quit = false;
		up = 'w';
		left = 'a';
		down = 's';
		right = 'd';
		srand(time(NULL));

		ball = new cBall(width, height);
		snake = new cSnake(w/2, h/2);

		//draw();
	}

	~cSystemManager(){
		delete ball;
		delete snake;
	}

	void draw(){
		system("cls");

		int ballx = ball->getX();
		int bally = ball->getY();
		int snakex = snake->getX();
		int snakey = snake->getY();
		int queue = snake->getlQueue();
		
		

		for(int i=0; i<width+2; i++)
			cout << "\xB2";
		cout << endl;

		for(int i=0; i<height; i++){
			for(int j=0; j<width; j++){
				bool isThere = false;
				if(j == 0)
					cout << "\xB2";

				for(int k=0; k<queue+1; k++){
					if(j == snake->getTabX(k) && i == snake->getTabY(k)){
						cout << "\xFE";
						isThere = true;
						k = queue+1;
					}
						
				}

				if(j == ballx && i == bally)  // Ball
					cout << "O";

				else{
					if(!isThere)
						cout << " ";
				}
					

				if(j == width - 1)
					cout << "\xB2";		
			}
			cout << endl;
		}
		for(int i=0; i<width+2; i++)
			cout << "\xB2";
		cout << endl;

	}

	

	void Run(){
		while(!quit){
			draw();
			input();
			snake->move();
			logic();
		}

		system("PAUSE");
	}

	/*void reset(){
		ball->Reset();
		snake->Reset();
	}*/

	void input(){

		int ballx = ball->getX();
		int bally = ball->getY();
		int snakex = snake->getX();
		int snakey = snake->getY();

		if(_kbhit()){
			char current = _getch();

			if(current == up){
				snake->changeDirection(HAUT);
			}

			if(current == down){
				snake->changeDirection(BAS);
			}

			if(current == left){
				snake->changeDirection(GAUCHE);
			}

			if(current == right){
				snake->changeDirection(DROITE);
			}

			if(current == 'q')
				quit = true;
		}
	}

	void logic(){

		int ballx = ball->getX();
		int bally = ball->getY();
		int snakex = snake->getX();
		int snakey = snake->getY();

		if(snakex <= 0 || snakex > width-1 || snakey <=0 || snakey > height-1){
			quit = true;
		}

		for(int i = 1; i< snake->getlQueue(); i++){
			if(snakex == snake->getTabX(i) && snakey == snake->getTabY(i)){
				quit = true;
			}
		}
		
		if(snakex == ballx && snakey == bally){
			ball->Reset(width, height);
			snake->scoreUp();
			
		}
	}
};






int main(){

	cSystemManager g(60, 20);
	g.Run();

	return 0;
}