#include <gl/glut.h>
#include <cmath>
#define PI 3.1415

void Circle(GLint xc, GLint yc , GLint r)
{
	int x=0, y=r,r2=r*r;
	
	while(x<=y)
	{
		glBegin(GL_POINTS);
		glVertex2f(xc+x,yc+y);
		glVertex2f(xc-x,yc+y);
		glVertex2f(xc+x,yc-y);
		glVertex2f(xc-x,yc-y);

		glVertex2f(xc+y,yc+x);
		glVertex2f(xc-y,yc-x);
		glVertex2f(xc+y,yc-x);
		glVertex2f(xc-y,yc+x);
		glEnd();
		x++;
		if(r2-x*x<y*y)
			y--;
	}
	glFlush();
}

//نیم دایره
void halfCircle(GLint xc, GLint yc , GLint r)
{
	int x=0, y=r,r2=r*r;
	
	while(x<=y)
	{
		glPointSize(2);
		glBegin(GL_POINTS);
		
		glVertex2f(xc+x,yc-y);
		glVertex2f(xc-x,yc-y);

		
		glEnd();
		x++;
		if(r2-x*x<y*y)
			y--;
	}
	glFlush();
}

//معادله قطبی دایره
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius){
	
	int i;
	int triangleAmount = 20; //مثلثی که باهاش شکل پر میکنه
	
	//شعاع
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
		glVertex2f(x, y); //مرکز دایره
		for(i = 0; i <= triangleAmount;i++) { 
			glVertex2f(
		            x + (radius * cos(i *  twicePi / triangleAmount)), 
			    y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	glEnd();
}
//خطوط خورشید
void drawSun()
{
	int p1[]={300,440};//عمود 1
	int p2[]={300,560};//عمود 2
	int p3[]={360,500};//افق 1  
	int p4[]={240,500};//افق 2
	int p5[]={250,540};//چپ به راست 1
	int p6[]={340,460};//چپ به راست 2
	int p7[]={250,460};//راست به چپ 1
	int p8[]={340,540};//راست به چپ 2
	
	glLineWidth(2);

	glBegin(GL_LINES);
	
	glVertex2iv(p1);
	glVertex2iv(p2);
	glVertex2iv(p3);
	glVertex2iv(p4);
	glVertex2iv(p5);
	glVertex2iv(p6);
	glVertex2iv(p7);
	glVertex2iv(p8);
	glEnd();

}

//دریا
void drawSea(int width,int l)
{
	for(float x=0;x<=628;x++)
	{
		Circle(x,width+sin(x/50)*l,10);//موج سطحی
	}
	//بریدگی
	for(float x=628;x<=1256;x++)
	{
		Circle(x,width+sin(x/40)*l,10);//موج سطحی
	}

	//موج ها

	for(float x=0;x<=100;x++)
	{
		glColor3f(.14,.42,.56);//رنگ موج ها

		//چند تا موج درهم تو دریا
		Circle(x+120,width-50+cos((x+120)/10)*5,2);
		Circle(x+450,width-55+sin((x+450)/10)*5,2);
		Circle(x+700,width-57+sin((x+700)/10)*5,2);
		Circle(x,width-100+sin((x+30)/10)*5,2);
		Circle(x+600,width-110+sin((x+600)/10)*5,2);
		Circle(x+500,width-170+cos((x+500)/10)*5,2);
		Circle(x+30,width-200+cos((x+30)/10)*5,2);
		Circle(x+330,width-230+sin((x+330)/10)*5,2);
		Circle(x+650,width-250+sin((x+650)/10)*5,2);
		Circle(x+145,width-255+cos((x+145)/10)*5,2);

	}
	
}
//قایق
void drawBoat()
{
	//خطوط خارجی قایق
	for(float x=100;x<=530;x++)
	{
		glColor3f(0.31,0.12,0);
		Circle(x,150+cos(x/100)*50,5);
		Circle(x,170+cos(x/100)*20,2);
		Circle(x,180+cos(x/50)*10,5);
	}

	//خطوط داخل قایق
	for(int i=1; i<=10 ; i++)
	{
		glLineWidth(10);
		glBegin(GL_LINES);
		glVertex2i(350,150);
		glVertex2i(340,190);
		glVertex2i(300,150);
		glVertex2i(290,190);
		glEnd();
	}

}

void drawMan()
{
	int p1[]={300,230};
	int p2[]={300,170};

	//سر
	drawFilledCircle(320,220,20);

	glLineWidth(2);
	glBegin(GL_LINES);
	//تنه
	glVertex2i(320,200);
	glVertex2i(320,165);
	//دست
	glVertex2i(320,198);
	glVertex2i(330,178);

	glVertex2i(320,198);
	glVertex2i(310,178);
	glEnd();
	//چشم
	glColor3f(0, 0, 0);
	drawFilledCircle(313,225,4);
	drawFilledCircle(328,225,4);
	//دهن
	glColor3f(1, 0, 0);
	halfCircle(320,220,10);
	
	//موها
	glBegin(GL_LINES);
	glColor3f(.8,.8,.8);

	glVertex2i(310,235);
	glVertex2i(300,240);

	glVertex2i(330,235);
	glVertex2i(340,240);

	glVertex2i(313,250);
	glVertex2i(315,240);

	glVertex2i(327,250);
	glVertex2i(325,240);
	glEnd();

}

//رسم شکل
void draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

	glColor3f(1, 1, 0);//زرد رنگ خورشید
	drawSun();//خطای خورشید
	drawFilledCircle(300,500,30);//خورشید
	glColor3f(0,0,1);//رنگ دریا آبی
	drawSea(300,15);//دریا
	glColor3f(0.31,0.12,0);//  قایق رنگ قهوه ای 
	drawBoat();//قایق
	glLineWidth(2);
	glColor3f(.8,.8,.8);//رنگ ادم
	drawMan();//ادم
		
	glEnd();

	glFlush();
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
	
	glClearColor(1.0,1.0,1.0,0.0);
	glutInitWindowPosition( 20, 60 );
	glutInitWindowSize( 360, 360 );
	glutCreateWindow( "Project _ Graphics" );

	glMatrixMode(GL_PROJECTION);

	gluOrtho2D(0,800,0,600);

	glutDisplayFunc(draw);////

	glutMainLoop();
	return 0;
}

