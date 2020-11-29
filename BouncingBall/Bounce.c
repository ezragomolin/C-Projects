#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Work by Ezra Gomolin Student Id:260926917 (Assignment 5 ECSE-202)
// This program is a conversion from assignement 1 in java to C
//I based it off of the solutions posted by Professor Ferrie

//declaring variables
double Vo;
double theta;
double bLoss;
double bSize;

#define WIDTH 600			// width of screen
#define HEIGHT 600			// height of screen
#define OFFSET 200			// bottom of screen to ground plate
#define TICK 0.1			// clock tick duration in seconds
#define ETHR 0.1			// If KEx or KEy are less than ETHR, stop
#define Xmax 100			// max value of x
#define Ymax 100			// max value of y
#define PD 1.0				// trace point diameter of ovals
#define SCALE HEIGHT/XMAX	// pixels/meter scale
#define k 0.0016            //constant
#define g 9.8				// gravity constant
#define pi 3.141592654		// pi to convert angles
#define Xinit 5.0			// initial ball location x pos


#define true !0  //defining boolean




int main()
{
	// users chooses values for initial velocity, launch angle, energy loss parameter, radius of ball
	printf("Enter the initial velocity of the ball in m/s [0, 100]: ");
	scanf("%lf", &Vo);

	printf("Enter the launch angle [0, 90]: ");
	scanf("%lf", &theta);

	printf("Enter the energy loss parameter [0, 1]: ");
	scanf("%lf", &bLoss);

	printf("Enter the radius of the ball in m [0.1, 5.0]: ");
	scanf("%lf", &bSize);

	//code from A1
	double Vt = g / (4 * pi * bSize * bSize * k);	// vt constant depending on bsize
	double time=0;
	double KEx =ETHR;		// initially no loss of energy in x
	double KEy = ETHR;		// initially no energy loss for y
	double Xo,X,Xlast,Vx,Y,Vy,Ylast;	// declare variables
	double Vox = Vo * cos((theta * pi) / 180);		// creating horizontal velocity parameter
	double Voy = Vo * sin((theta * pi) / 180);		// creating vertical velocity parameter
    Xo=Xinit;
    Y=bSize;
    Ylast=Y;
    Xlast=Xo;


	// repeats function, Code from A1
	while (true)
	{

		X =(Vox * Vt / g * (1 - exp(-g * time / Vt)));						// kinematic equation for X position
		Y = bSize + ((Vt / g * (Voy + Vt) * (1 - exp(-g * time / Vt)) - Vt * time));// kinematic equation for Y position
		Vx = (X - Xlast) / TICK;	// formula for Vx
		Vy = (Y - Ylast) / TICK;	// formula for Vy


		printf("t: %.2f X: %.2f Y: %.2f Vx: %.2f Vy:%.2f\n", time, Xo + X, Y, Vx, Vy); // print ball data
        Xlast=X;
        Ylast=Y;

		// detecting when a collision occurs, Code from A1
		if (Vy < 0 && Y <= bSize)
		{

			KEx = 0.5 * Vx * Vx * (1 - bLoss);	// kinetic energy after loss x pos
			KEy = 0.5 * Vy * Vy * (1 - bLoss);	// kinetic energy after loss y pos
			Vox = sqrt(2 * KEx);
			Voy = sqrt(2 * KEy);
			time = 0;
			Y = bSize;	// resetting y pos
			Xo += X ;	// resetting x pos
			X=0;       //resetting X as 0
			Xlast=X;   //recording last x pos
			Ylast=Y;   //recording last y pos


			// stopping the program
			if (KEx < ETHR || KEy < ETHR) break;

		}
		time+=TICK; //incrementing time
	}
}
