#include <graphics.h>
#include<stdio.h>
#define Maxdinh 20
#define INPUT "heno.txt"
 
struct point{
	int x;
	int y;
	int code;
};


struct point pt[Maxdinh];
int Sodinh;
int xmin = 200;
int ymin = 200;
int xmax = 400;
int ymax = 400;
struct point res[2];
FILE *fp;
float m[Maxdinh];
int Mahoa(struct point p){
	// xet phan giua
	if(p.x >= xmin && p.x <= xmax){
		if(p.x >= ymin && p.y <= ymax){
			return p.code = 0;
		}
		if(p.y < ymin){
			return p.code = 8;
		}
		if(p.y > ymax){
			return p.code = 4;
		}
	}
	// xet phan ben trai
	if(p.x < xmin){
		if(p.y >= ymin && p.y <= ymax){
			return p.code = 1;
		}
		if(p.y < ymin){
			return p.code = 9;
		}
		if(p.y > ymax){
			return p.code = 5;
		}
	}
	// xet ben phai
	if(p.x > xmax){
		if(p.y >= ymin && p.y <= ymax){
			return p.code = 2;
		} 
		if(p.y < ymin){
			return p.code = 10;
		}
		if(p.y > ymax){
			return p.code = 6;
		}
	}
}

void Readfile(){
	fp = fopen(INPUT,"r");
	if(fp==NULL){
		printf("File not found.");
		return;
	}
	fscanf(fp, "%d", &Sodinh);
	for(int i = 0; i< Sodinh; i++){
		fscanf(fp,"%d %d",&pt[i].x,&pt[i].y);
	}
	//tim he so goc
	
	for(int i = 0; i < Sodinh; i++){
		pt[i].code = Mahoa(pt[i]);
	}
	printf("X\tY\tCODE\n");
	for(int i = 0; i < Sodinh; i++){
		printf("%d\t%d\t%d\n", pt[i].x, pt[i].y, pt[i].code);
	}
	fclose(fp);
}
//tim he so goc 
void Hesogoc(){
	for(int i =0; i < Sodinh - 1; i++){
		m[i] = (float)(pt[i+1].y - pt[i].y) / (pt[i+1].x - pt[i].x);
	}
	printf("He so goc cac canh: ");
	for(int i = 0; i < Sodinh - 1;i++){
		printf("%.3f", m[i]);
	}
}
struct point Timgd(struct point p){
//	struct point res;
//	if(p1.code == 0 ){
//		res.x = p.x;
//		res.y = p.y;
//	}
//	if(p.code == 1){
//		res.x = xmin;
//		res.y = p.y+(res.x - p.x); //y = ysau + x - xtruoc 
//	}
//	return res;
//}
//void Cohen(){
//	struct point xy[maxdinh]; // toa do cac dinh sau xen tia
//	int dem = 0;
//	for(int i = 0; i < Sodinh - 1; i++){
////		if(pt[i].code ==0 & pt[i + 1].code == 0){ // nam trong cua so cat
////			x0 = pt [i].x;
////			x0 = pt [i].y;
////			x1 = pt [i + 1].x;
////			y1 = pt [i + 1].y;
////		}
//		xy[dem++] = Timgd(pt[i]);
//	}
//	setlinestyle(1,1,2);
//	setcolor(4);
//	for(int i=0;i<Sodinh,i++){
//		line(xy[i].x, xy[i].y, xy[i + 1].x, xy[i + 1].y);
//	}
//	//ve duong thang noi 2 giao diem
////	line(x0,y0,x1,y1);


	int x0, y0, x1, y1;
	struct point res[2];
	int dem;
	for(int i = 0; i< Sodinh-1; i++){
		if(pt[i].code == 0 && pt[i+1].code == 0){
			res[dem].x = pt[i].x; res[dem++].y = pt[i].y;
			res[dem].x = pt[i+1].x; res[dem++].y = pt[i+1].y;
		}
		if(pt[i].code != 0 && pt[i+1].code != 0){// ca 2 dinh deu nam ngoai cua so cat
//			printf("Ma hoa",(pt[i].code& pt[i+1].code));
			if((pt[i].code & pt[i+1].code) != 0){// khong co giao diem
				res[dem].x = xmin; res[dem++].y = ymin;
				res[dem].x = xmin; res[dem++].y =ymin;
			}
			else{ // co 2 giao diem
			printf("m: %f", m[i]);
			//xet dinh i
				if(pt[i].code == 1){ // ben trai
					res[dem].x = xmin;
					res[dem++].y = pt[i].y + (float) m[i] * (xmin - pt[i].x);
				}
				//xet dinh i = 1
				
				if(pt[i+1].code == 2){ // ben phai
					res[dem].x = xmax;
					res[dem++].y = pt[i].y + (float) m[i] * (xmax - pt[i].x);
					printf("\n(%d,%d)", res[i].x, res[i].y);
				}
			}
		}
		//in ra toa do giao diem
		
		//ve duong thang noi cac dinh
		setlinestyle(1,1,2);
		setcolor(4);
		for(int i = 0; i < dem-1; i++){
		line(res[i].x, res[i].y, res[i + 1].x, res[i + 1].y);
		}
	}
}

void Vecuasocat(){
	setcolor(15);
	setlinestyle(1,1,2);
	rectangle(xmin, ymin, xmax, ymax);
	setlinestyle(1,0,1);
	//ve doan thang bang dau
	for(int i = 0; i < Sodinh - 1; i++){
		line(pt[i].x, pt[i].y, pt[i + 1].x, pt[i + 1].y);
	}
}


int main()
{
	Readfile();
	initwindow(500,500);
	line(100,100,400,400);
	Vecuasocat();
//	Cohen();
	getch();
	return 0;
}
