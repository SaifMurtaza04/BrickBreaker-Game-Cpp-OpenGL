//============================================================================
// Name        : Muhammad Saif Murtaza_23i-2588_DS-C
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include <iostream>
#include<fstream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

class Paddle
{
	private:
	float x_position, y_position;
	float width, height;
	 
	public:
	Paddle(){}
	Paddle(float x, float y, float w, float h)
	{
		this->x_position = x;
		this->y_position = y;
		this->width = w;
		this->height = h;
	}
	void Draw()
	{
		DrawRoundRect(x_position, y_position, width, height, colors[WHITE], 30);
		DrawLine(0, y_position - 20, 1020, y_position - 20, 2, colors[WHITE]);
	}
	void Update_position(int mouse_x, int canvas_width)
	{
		// updating position on the basis of mouse input
		x_position = static_cast<float>(mouse_x)-width / 2.0;

		if (x_position < 0)
		{
			x_position = 0;
		}
		if(x_position + width > canvas_width)
		{
			x_position = canvas_width - width;
		}
	}
	void Display()
	{
		Draw();
	}
	float getX() const { return x_position;}
	float getY() const {return y_position;}
	float getWidth() const { return width;}
	float getHeight() const { return height;}
	void setWidth(float x)
	{
		width = x;
	}


};
class Ball
{
	private:
	float x_position, y_position;
	float x_velocity, y_velocity;
	float radius;
	int canvas_width, canvas_height;

	public:
	Ball(){}
	Ball(float x, float y, float vx, float vy, float r, int cw, int ch)
	{
		this->x_position = x;
		this->y_position = y;
		this->x_velocity = vx;
		this->y_velocity = vy;
		this->radius = r;
		this->canvas_height = ch;
		this->canvas_width = cw;
	}
	void Draw()
	{
		DrawCircle(x_position,y_position,radius,colors[DARK_CYAN]);
	}
	void Update()
	{
    	x_position += x_velocity;
    	y_position += y_velocity;

    	if (x_position - radius <= 0 || x_position + radius >= canvas_width)
    	{
        	x_velocity = -x_velocity;
    	}
    	if (y_position - radius <= 0)  
    	{
        	y_velocity = -y_velocity;  
			y_position = radius;
    	}
    	if (y_position + radius >= canvas_height)
    	{
        		y_position = canvas_height - radius;
				y_velocity = -y_velocity;
    	}
		
	}
	void CheckCollision(float paddleX, float paddleY, float paddleW, float paddleH)
	{
		//checking collisiion with paddle, with refrence to paddles starting position and balls radius
		if (x_position + radius >= paddleX && x_position - radius <= paddleX + paddleW &&
			y_position - radius <= paddleY + paddleH && y_position + radius >= paddleY)
		{
			y_velocity = -y_velocity;
		}
		
	}
	// setters and getters
	float getX() const
	{
		return x_position;
	}
	float getY() const{
		return y_position;
	}
	float getRadius() const
	{
		return radius;
	}
	float getXvelocity() const
	{
		return x_velocity;
	}
	float getYvelocity() const
	{
		return y_velocity;
	}
	void setXvelocity(float x)
	{
		x_velocity = x;
	}
	void setYvelocity(float y)
	{
		y_velocity = y;
	}
	void setVelocity(float x, float y)
	{
		x_velocity = x;
		y_velocity = y;
	}
	void setX(float x)
	{
		x_position = x;
	}
	void setY(float y)
	{
		y_position;
	}
};


class Power_up{       // base class for power up
	protected:
	float x_position, y_position;
	float size;
	public:
	int color;
	Power_up(float x, float y, int color) : color(color)
	{
		x_position = x;
		y_position = y;
	}
	virtual void activate_powerup (Paddle& paddle, Ball& ball) = 0;
	virtual void Draw() = 0;
	void move(float speed){
		y_position -= speed;

	}
	bool CheckCollision(const Paddle &paddle){
        
        float powerUpLeft = x_position - size / 2.0;
        float powerUpRight = x_position + size / 2.0;
        float powerUpTop = y_position - size / 2.0;
        float powerUpBottom = y_position + size / 2.0;

        float paddleLeft = paddle.getX() - paddle.getWidth() / 2.0;
        float paddleRight = paddle.getX() + paddle.getWidth() / 2.0;
        float paddleTop = paddle.getY() - paddle.getHeight() / 2.0;
        float paddleBottom = paddle.getY() + paddle.getHeight() / 2.0;

        if (powerUpRight >= paddleLeft && powerUpLeft <= paddleRight &&
            powerUpBottom >= paddleTop && powerUpTop <= paddleBottom){
			return true; 
        }

        return false; 
    }
};
// derived classes for Power_up
class GreenPowerup : public Power_up
{
	public :
	GreenPowerup(float x, float y, int color): Power_up(x,y,color){}
	void activate_powerup(Paddle& paddle, Ball& ball) override
	{
		float size = paddle.getWidth();
		size *= 2;
		paddle.setWidth(size);
	}

	void Draw()
	{
		DrawTriangle(x_position, y_position, x_position - 30, y_position - 30, x_position + 30, y_position, colors[GREEN] );
	}

};
class PinkPowerup: public Power_up
{	
	public:
	PinkPowerup(float x, float y, int color): Power_up(x,y,color){}
	void activate_powerup(Paddle& paddle, Ball& ball) override
	{
		float size = paddle.getWidth();
		size /= 2;
		paddle.setWidth(size);
	}
	void Draw() override
	{
		DrawSquare( x_position , y_position ,30,colors[DEEP_PINK]); 
	}
};
class BluePowerup: public Power_up
{
	public:
	BluePowerup(float x, float y, int color): Power_up(x,y,color){}
	void activate_powerup(Paddle& paddle, Ball& ball) override
	{
		float x_velocity = ball.getXvelocity();
		float y_velocity = ball.getYvelocity();

		x_velocity -= 2;
		y_velocity -= 2;

		ball.setVelocity(x_velocity,y_velocity);
	}
	void Draw() override
	{
		DrawCircle(x_position,y_position,20,colors[BLUE]);
	}

};
class RedPowerup: public Power_up
{
	public:
	RedPowerup(float x,float y,int color):Power_up(x,y,color){}
	void activate_powerup(Paddle& paddle, Ball& ball) override
	{
		float x_velocity = ball.getXvelocity();
		float y_velocity = ball.getYvelocity();

		x_velocity += 2;
		y_velocity += 2;

		ball.setVelocity(x_velocity,y_velocity);
	}
	void Draw() override
	{
		DrawSquare( x_position , y_position ,30,colors[RED]);
		DrawSquare( x_position + 25 , y_position ,30,colors[RED]);
	}

};
class YellowPowerup: public Power_up
{
	public:
	YellowPowerup(float x, float y, int color):Power_up(x,y, color){}
	virtual void activate_powerup (Paddle& paddle, Ball& ball) {
		
	}
	void Draw() override
	{
		DrawSquare( x_position , y_position ,30,colors[GOLD]);
	}

};

class Brick
{
	protected:
	float width;
	float height;
	int durability;
	bool broken;
	float x_position;
	float y_position;
	string color;
	


	public:


	//BrickAttributes attributes[5] = {{"GREEN",1},{"DEEP_PINK",2},{"BLUE",3},{"RED",3},{"GOLD",2}};
	Brick(){}
	Brick(float x, float y, float w, float h, string color){
		x_position = x;
		y_position = y;
		width = w;
		height = h;
		broken = false;
		if (color == "GREEN"){
			this->color = "GREEN";
			this->durability = 1;
		}
		if (color == "DEEP_PINK"){
			this->color = "DEEP_PINK";
			this->durability = 2;
		}
		if (color == "BLUE"){
			this->color = "BLUE";
			this->durability = 3;
		}
		if (color == "RED"){
			this->color = "RED";
			this->durability = 3;
		}
		if (color == "GOLD"){
			this->color = "GOLD";
			this->durability = 2;
		}
	}
void Draw(){
    if (!broken){
        // Draw brick using color
        if (color == "GREEN"){
            DrawRoundRect(x_position, y_position, width, height, colors[GREEN], 30);
        }
        else if (color == "DEEP_PINK"){
            DrawRoundRect(x_position, y_position, width, height, colors[DEEP_PINK], 30);
        }
        else if (color == "BLUE"){
            DrawRoundRect(x_position, y_position, width, height, colors[BLUE], 30);
        }
        else if (color == "RED"){
            DrawRoundRect(x_position, y_position, width, height, colors[RED], 30);
        }
        else if (color == "GOLD"){
            DrawRoundRect(x_position, y_position, width, height, colors[GOLD], 30);
        }
	}
}

	// checking collision of ball with brick 
	bool CheckCollision( float ball_x, float ball_y, float ball_radius, float& ball_x_velocity, float& ball_y_velocity)
	{
		if(!broken && ball_x + ball_radius >= x_position &&
			ball_x - ball_radius <= x_position + width &&
			ball_y + ball_radius >= y_position &&
			ball_y - ball_radius <= y_position + height){

            ball_y_velocity = -ball_y_velocity;
            durability--;
            if (durability <= 0) {
                broken = true;
                return true; 
            }
			
		}
        return false; 
    }
	float getX() const{
		return x_position;
	}
	float getY() const{
		return y_position;
	}
	float getWidth() const{
		return width;
	}
	float getHeight() const{
		return height;
	}
	string getColor() const{
		return color;
	}

};

class Brick_helper: public Brick{
private:
	
    float b_width;
    float b_height;
    int start_x;
    int start_y;
    string color[5] = {"GREEN","DEEP_PINK","BLUE","RED","GOLD"};
	int score;
	
	int main_i;
	int main_j;


public:
 	Brick bricks[50][50];
	Power_up* powerup[50][50];
    Brick_helper(int Main_i, int Main_j) : b_width(100.0), b_height(20.0), start_x(50), start_y(644){
        brick_initialize1(Main_i,Main_j);
    }

	void brick_initialize1(int Main_i, int Main_j) {

		main_i = Main_i;
		main_j = Main_j;
		
    	float startX = 0;
		srand(time(nullptr));
    	for (int i = 0; i < main_i; i++) {
        	for (int j = 0; j < main_j; j++) {
			
				int x = rand() % 5;
            	bricks[i][j] = Brick(startX + j * (b_width + 2), start_y + i * (b_height + 22), b_width, b_height, color[x]);
        	}
    	}

		for (int i = 0; i < main_i; i++) {
        	for (int j = 0; j < main_j; j++) {
				powerup[i][j] = nullptr;
			}
		}
	}

	// failed attempt at creating level 2, sighssssss
	void brick_initialize2(int Main_i, int Main_j){
		main_i = Main_i;
		main_j = Main_j;
    	float startX = 0;
		srand(time(nullptr));
    	
		for (int i = 0; i < main_i; i++) {
        	for (int j = 0; j < main_j; j++) {
			
				int x = rand() % 5;
            	if (i == j || i - main_i+1 == j) bricks[i][j] = Brick(startX + j * (b_width + 2), start_y + i * (b_height + 22), b_width, b_height, color[x]);
        	}
    	}

		for (int i = 0; i < main_i; i++) {
        	for (int j = 0; j < main_j; j++) {
				powerup[i][j] = nullptr;
			}
		}
	}

    void Draw() {
        for (int i = 0; i < main_i; i++) {
        	for (int j = 0; j < main_j; j++) {
                bricks[i][j].Draw();
            }
        }
    }
	void RemoveBrick(int row, int col){
		bricks[row][col]= Brick();
	}

   void CheckCollision(float ball_x, float ball_y, float ball_radius, float& ball_xVelocity, float& ball_yVelocity) {
    for (int i = 0; i < main_i; i++) {
        	for (int j = 0; j < main_j; j++) {
            if (bricks[i][j].CheckCollision(ball_x, ball_y, ball_radius, ball_xVelocity, ball_yVelocity)) {
                score += 10;
                

               
                float brickCenterX = bricks[i][j].getX() + bricks[i][j].getWidth() / 2.0;
                float brickCenterY = bricks[i][j].getY() + bricks[i][j].getHeight() / 2.0;
                float dx = ball_x - brickCenterX;
                float dy = ball_y - brickCenterY;

                if (dx > dy ) {
                    ball_xVelocity = -ball_xVelocity;
                } else {
                    
                    ball_yVelocity = -ball_yVelocity;
                }

				if (bricks[i][j].getColor() == "GREEN"){
					powerup[i][j] = new GreenPowerup(bricks[i][j].getX(), bricks[i][j].getY(),1);
				}
				else if (bricks[i][j].getColor() == "DEEP_PINK"){
					powerup[i][j] = new PinkPowerup(bricks[i][j].getX(), bricks[i][j].getY(),2);
				}
				else if (bricks[i][j].getColor() == "BLUE"){
					powerup[i][j] = new BluePowerup(bricks[i][j].getX(), bricks[i][j].getY(),3);
				}
				else if (bricks[i][j].getColor() == "RED"){
					powerup[i][j] = new RedPowerup(bricks[i][j].getX(), bricks[i][j].getY(),4);
				}
				else{
					powerup[i][j] = new YellowPowerup(bricks[i][j].getX(), bricks[i][j].getY(),5);
				}
				
				RemoveBrick(i, j);

            }
        }
    }
}

int getScore() const {
	return score;
}
};

class Game {
public:
    Paddle paddle;
    Ball ball;
	int powerTimer = 0;

	bool isBall2;
	Ball* ball2;
	int ball2Count = 0;

    Brick_helper brickHelper;
	int counter = 0;
	int lives = 2;
	
	bool game_over = false;
	int highScore = 0;

	int main_i = 5;
	int main_j = 10;

	// file handling part
	void ReadHighScore()
	{
		ifstream inputfile("highScore.txt");
		if(inputfile.is_open())
		{
			inputfile>>highScore;
			inputfile.close();
		}
	}
	void WriteHighScore()
	{
		ofstream outputfile("highScore.txt");
		if(outputfile.is_open())
		{
			outputfile << highScore;
			outputfile.close();
		}
	}



    Game(int canvasWidth, int canvasHeight) : paddle(400.0, 90.0, 100.0, 20.0),
                                              ball(500.0, 200.0, 7.0, 7.0, 10.0, canvasWidth, canvasHeight),
                                              brickHelper(5,10) 
	{
		isBall2=false;
		ReadHighScore();
        
		
    }

    void UpdateGame() 
	{
        ball.Update();
		powerTimer++;
		if (powerTimer >= 300){

		for (int i = 0; i < main_i; i++) {
    		for (int j = 0; j < main_j; j++) {
				if (brickHelper.powerup[i][j] != NULL) {
						
					if (brickHelper.powerup[i][j]->CheckCollision(paddle))
					{	
						powerTimer = 0;
						
						if (brickHelper.powerup[i][j]->color == 5) {
							isBall2 = true;
							ball2 = new Ball(500.0, 200.0, 7.0, 7.0, 10.0, 1020, 840);
						}
						brickHelper.powerup[i][j]->activate_powerup(paddle,ball);
					}
				}
			}
		}
		}
		for (int i = 0; i < main_i; i++) {
    		for (int j = 0; j < main_j; j++) {
				if (brickHelper.powerup[i][j] != NULL) {
						brickHelper.powerup[i][j]->move(5);
				}
			}
		}
        ball.CheckCollision(paddle.getX(), paddle.getY(), paddle.getWidth(), paddle.getHeight());
        float temp_x_velocity = ball.getXvelocity();
        float temp_y_velocity = ball.getYvelocity();
        brickHelper.CheckCollision(ball.getX(), ball.getY(), ball.getRadius(), temp_x_velocity, temp_y_velocity);
        ball.setXvelocity(temp_x_velocity);
        ball.setYvelocity(temp_y_velocity);
		if (ball.getY() - ball.getRadius() <= paddle.getY() - 20) {
        	lives--; 
        	ball.setX(500.0); 
        	ball.setY(200.0);
        	ball.setVelocity(7.0, 7.0); 
    	}

		if (isBall2){
			ball2->Update();
        	ball2->CheckCollision(paddle.getX(), paddle.getY(), paddle.getWidth(), paddle.getHeight());
        	float temp_x_velocity = ball2->getXvelocity();
        	float temp_y_velocity = ball2->getYvelocity();
        	brickHelper.CheckCollision(ball2->getX(), ball2->getY(), ball2->getRadius(), temp_x_velocity, temp_y_velocity);
        	ball2->setXvelocity(temp_x_velocity);
        	ball2->setYvelocity(temp_y_velocity);
			ball2Count++;
			if (ball2Count >= 300){
				isBall2 = false;
				ball2Count = 0;
			}
		}
		
    		
    		if (lives < 0) 
			{
            game_over = true;
            if (brickHelper.getScore() > highScore) {
                highScore = brickHelper.getScore(); 
                WriteHighScore(); 
            }
            exit(0); 
        	}
   		 
    }

	int getHighScore() const{
		return highScore;
	}


    void DrawGame() {
        paddle.Display();
        ball.Draw();
		if (isBall2)  ball2->Draw();
        brickHelper.Draw();
    	
    	DrawString(90, 20, "Score: " + to_string(brickHelper.getScore()), colors[WHITE]);
		DrawString(290, 20, "Lives: " + to_string(lives), colors[WHITE]);
    	DrawString(390, 20, "High Score: " + to_string(getHighScore()), colors[WHITE]);
		DrawString(790, 40, "Saif Murtaza", colors[WHITE]);
		DrawString(790, 10, "23i-2588", colors[WHITE]);
        for (int i = 0; i < main_i; i++) {
    
    		for (int j = 0; j < main_j; j++) {

				if (brickHelper.powerup[i][j] != NULL) {
					brickHelper.powerup[i][j]->Draw();
				}
			}
		}
    }
};


int dx = 400;
Game game(1020,840);
void GameDisplay(){
	// set the background color using function glClearColor.
	glClearColor(0/*Red Component*/, 0,    //148.0/255/*Green Component*/,
            0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	
	game.UpdateGame();
	game.DrawGame();
	glutSwapBuffers(); // do not modify this line..
	glutPostRedisplay();

}


void NonPrintableKeys(int key, int x, int y) {
    if (key
            == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
        // what to do when left key is pressed...
        

    } else if (key
            == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
    dx++;

    } else if (key
            == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

    }

    else if (key
            == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

    }

    /* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
     * this function*/

    glutPostRedisplay();

}


void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B') //Key for placing the bomb
			{
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	glutPostRedisplay();
}

void Timer(int m) {

	game.counter++;

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	game.paddle.Update_position(x,1020);
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	glutPostRedisplay();
}






/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	int width = 1020, height = 840; // i have set my window size to be 800 x 600

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */

