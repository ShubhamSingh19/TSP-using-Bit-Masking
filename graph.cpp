#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;
#define INT_MAX 999999

int n;
int choice;
int fcity,sour;

int ary[10][10];

int dist[10];
int ncount;

int dp[1024][10];
int vertex[1024][10];

int  tsp(int mask,int pos){

	if(mask==((1<<n)-1)){
            if(ary[pos][0]!=0)
		        return ary[pos][0];
             else
                return INT_MAX;
	}

	if(dp[mask][pos]!=-1){
	   return dp[mask][pos];
	}

	int ans = INT_MAX;
	int node;

	for(int city=0;city<n;city++){

		if((mask&(1<<city))==0&&ary[pos][city]!=0){

			int newAns = ary[pos][city] + tsp( mask|(1<<city), city);
			if(newAns < ans)
                           {
                              ans = newAns;
                              node = city;
                           }
		}
	}

    vertex[mask][pos] = node;
	return dp[mask][pos] = ans;
}

int parent[10];
int minDistance(int dist[], bool sptSet[],int V)
{
   int min = INT_MAX, min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == false && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}

void dijkstra(int ary[10][10], int src,int V)
{

     bool sptSet[V];
     for (int i = 0; i < V; i++)
     dist[i] = INT_MAX, sptSet[i] = false;
     dist[src] = 0;

     for (int count = 0; count < V-1; count++)
     {
       int u = minDistance(dist, sptSet,V);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && ary[u][v] && dist[u] != INT_MAX
                                       && dist[u]+ary[u][v] < dist[v])
            {
                dist[v] = dist[u] + ary[u][v];
                parent[v]=u;
            }
     }
}

//############################################# Graphics #######################################################

struct
{
    int x;
    int y;
}data[10];

int abs (int n)
{
    return ( (n>0) ? n : ( n * (-1)));
}

void nodeUpdate(int i)
{
    int rx=20,ry=20;
    int xi=data[i-1].x;
    int yi=data[i-1].y;
    char a[2];
    char b[1];
    setcolor(BLACK);
    setbkcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    fillellipse(xi,yi,rx,ry);
    setcolor(BLACK);
    sprintf(a,"%ld",i);
    sprintf(b,"%s",a);
    if(i<10){
        settextstyle(10, HORIZ_DIR, 4);
        outtextxy(xi-9, yi-15, b);
    }
    else
    {
        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(xi-13, yi-11, b);
    }
    setfillstyle(SOLID_FILL,BLACK);
    bar(0,0,20,20);
}

void weightUpdate(int i,int f,int w)
{
    if(w!=0)
    {
        char a[4];
        char b[1];
        setcolor(YELLOW);
        int x0,y0,x1,y1,xm,ym;
        x0=data[i-1].x;
        y0=data[i-1].y;
        x1=data[f-1].x;
        y1=data[f-1].y;
        xm=abs(x1-x0)/2+(x0<x1?x0:x1);
        ym=abs(y1-y0)/2+(y0<y1?y0:y1);
        setbkcolor(YELLOW);
        setfillstyle(SOLID_FILL,YELLOW);
        fillellipse(xm,ym,16,14);
        setcolor(BLACK);
        sprintf(a,"%ld",w);
        sprintf(b,"%s",a);
        if(w<10){
            settextstyle(10, HORIZ_DIR, 2);
            outtextxy(xm-5, ym-10, b);
        }
        else{
            settextstyle(10, HORIZ_DIR, 1);
            outtextxy(xm-11, ym-8, b);
        }
    }

}

void DDA(int i,int f,int w)
{
    if(w!=0)
    {
        int X0=data[i-1].x;
        int Y0=data[i-1].y;
        int X1=data[f-1].x;
        int Y1=data[f-1].y;
        int dx = X1 - X0;
        int dy = Y1 - Y0;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

        float Xinc = dx / (float) steps;
        float Yinc = dy / (float) steps;

        float X = X0;
        float Y = Y0;
        setfillstyle(SOLID_FILL,YELLOW);
        setcolor(YELLOW);
        for (int i = 0; i <= steps; i++)
        {
            fillellipse(X,Y,2,2);
            X += Xinc;
            Y += Yinc;
            delay(1);
        }
        nodeUpdate(i);
        weightUpdate(i,f,w);
        if(f==1 || f==ncount)
        {
           nodeUpdate(f);
        }
    }
}

void drawLine(int i,int f,int w)
{
    char a[4];
    char b[1];
    setcolor(WHITE);
    int x0,y0,x1,y1,xm,ym;
    x0=data[i].x;
    y0=data[i].y;
    x1=data[f].x;
    y1=data[f].y;
    xm=abs(x1-x0)/2+(x0<x1?x0:x1);
    ym=abs(y1-y0)/2+(y0<y1?y0:y1);
    line(x0,y0,x1,y1);
    setbkcolor(WHITE);
    setfillstyle(SOLID_FILL,WHITE);
    fillellipse(xm,ym,16,14);
    setcolor(BLACK);
    sprintf(a,"%ld",w);
    sprintf(b,"%s",a);
    if(w<10){
        settextstyle(10, HORIZ_DIR, 2);
        outtextxy(xm-5, ym-10, b);
    }
    else{
        settextstyle(10, HORIZ_DIR, 1);
        outtextxy(xm-11, ym-8, b);
    }
}

void dl(int i)
{
    int xi=data[i-1].x;
    int yi=data[i-1].y;
    char a[3];
    char b[1];
    int rx=20,ry=20;
    setbkcolor(LIGHTGREEN);
    setcolor(CYAN);
    setfillstyle(SOLID_FILL, CYAN);
    fillellipse(xi,yi,4*rx/3,4*ry/3);
    setcolor(LIGHTGREEN);
    setfillstyle(SOLID_FILL,LIGHTGREEN);
    fillellipse(xi,yi,rx,ry);
    setcolor(BLACK);
    sprintf(a,"%ld",i);
    sprintf(b,"%s",a);
    if(i<10){
        settextstyle(10, HORIZ_DIR, 4);
        outtextxy(xi-9, yi-15, b);
    }
    else
    {
        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(xi-13, yi-11, b);
    }

}
void disp(int x,int y ,char s[])
{
    setcolor(LIGHTGREEN);
    setbkcolor(BLACK);
    settextstyle(10, HORIZ_DIR, 1);
    int tx=textwidth(s);
    int th=textheight(s);
    int x1=x-tx/2;
    int y1=y-th/2;
    outtextxy(x1,y1,s);

}
void cw(int sw,int sh)
{
    int cwx1=sw-350;
    int cwx2=sw;
    int cwy1=1;
    int cwy2=sh-1;
    int dilx1=cwx1+10;
    int dily1=cwy1+75;
    int dilx2=cwx2-10;
    int dily2=(abs(cwy2-cwy1))/2;
    setcolor(CYAN);
    setbkcolor(CYAN);
    setfillstyle(SOLID_FILL, CYAN);
    bar(cwx1,cwy1,cwx2,cwy2);
    setcolor(BLACK);
    settextstyle(10, HORIZ_DIR, 2);
    outtextxy(abs(cwx1-cwx2)/2+min(cwx1,cwx2)-textwidth("Control Window")/2,15,"Control Window");
    setfillstyle(SOLID_FILL, BLACK);
    bar(dilx1,dily1,dilx2,dily2);
    setfillstyle(SOLID_FILL, CYAN);
    bar(cwx1+10,cwy2-20,cwx2-10,(abs(cwy2-cwy1))/2+20);
}

void button(int x,int y,int c,char s[])
{
    int a=80;
    int b=40;
    int tx=textwidth(s);
    int th=textheight(s);
    int x1=a/2+x-tx/2;
    int y1=b/2+y-th/2;
    setcolor(BLACK);
    setbkcolor(c+8);
    setfillstyle(SOLID_FILL, c);
    bar(x,y,x+a,y+b);
    setfillstyle(SOLID_FILL, c+8);
    bar(x+7,y+7,x+a-7,y+b-7);
    settextstyle(10, HORIZ_DIR, 2);
    outtextxy(x1,y1,s);
}
void check1(int dbx1,int dbx2,int dbx3,int dbx4,int dbx5,int dbx6,int dbx7,int dbx8,int dbx9,int dbx10,int dbxr,int dbxe,
           int dby1,int dby2,int dby3,int dby4,int dby5,int dby6,int dby7,int dby8,int dby9,int dby10,int dbyr,int dbye,
           int bgx,int bgy,int cx,int cy,POINT cp)
{
        int ci=2;
        int cf=0;
        int m=400;
        int p=20;
    while(1){
        GetCursorPos(&cp);
        cx=cp.x;
        cy=cp.y;
        if(cx>dbx8 && cx<dbx8+bgx && cy>dby8+p && cy<dby8+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx8,dby8,cf,"8");
            n=8;
            delay(m);
            button(dbx8,dby8,ci,"8");
            break;
        }
        else if(cx>dbx10 && cx<dbx10+bgx && cy>dby10+p && cy<dby10+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx10,dby10,cf,"10");
            n=10;
            delay(m);
            button(dbx10,dby10,ci,"10");
            break;
        }
        else if(cx>dbx4 && cx<dbx4+bgx && cy>dby4+p && cy<dby4+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx4,dby4,cf,"4");
            n=4;
            delay(m);
            button(dbx4,dby4,ci,"4");
            break;
        }
        else if(cx>dbx1 && cx<dbx1+bgx && cy>dby1+p && cy<dby1+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx1,dby1,cf,"1");
            n=1;
            delay(m);
            button(dbx1,dby1,ci,"1");
            break;
        }
        else if(cx>dbx2 && cx<dbx2+bgx && cy>dby2+p && cy<dby2+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx2,dby2,cf,"2");
            n=2;
            delay(m);
            button(dbx2,dby2,ci,"2");
            break;
        }
        else if(cx>dbxr && cx<dbxr+bgx && cy>dbyr+p && cy<dbyr+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbxr,dbyr,cf,"Reset");
            delay(m);
            button(dbxr,dbyr,1,"Reset");
            break;
        }
        else if(cx>dbx3 && cx<dbx3+bgx && cy>dby3+p && cy<dby3+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx3,dby3,cf,"3");
            n=3;
            delay(m);
            button(dbx3,dby3,ci,"3");
            break;
        }

        else if(cx>dbx5 && cx<dbx5+bgx && cy>dby5+p && cy<dby5+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx5,dby5,cf,"5");
            n=5;
            delay(m);
            button(dbx5,dby5,ci,"5");
            break;
        }
        else if(cx>dbx6 && cx<dbx6+bgx && cy>dby6+p && cy<dby6+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx6,dby6,cf,"6");
            n=6;
            delay(m);
            button(dbx6,dby6,ci,"6");
            break;
        }
        else if(cx>dbx7 && cx<dbx7+bgx && cy>dby7+p && cy<dby7+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx7,dby7,cf,"7");
            n=7;
            delay(m);
            button(dbx7,dby7,ci,"7");
            break;
        }

        else if(cx>dbx9 && cx<dbx9+bgx && cy>dby9+p && cy<dby9+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx9,dby9,cf,"9");
            n=9;
            delay(m);
            button(dbx9,dby9,ci,"9");
            break;
        }
        else if(cx>dbxe && cx<dbxe+bgx && cy>dbye+p && cy<dbye+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbxe,dbye,cf,"Exit");
            delay(m);
            button(dbxe,dbye,4,"Exit");
            exit(0);
        }
    }
}
void check2(int dbx1,int dbx2,int dbx3,int dbx4,int dbx5,int dbx6,int dbx7,int dbx8,int dbx9,int dbx10,int dbxr,int dbxe,
           int dby1,int dby2,int dby3,int dby4,int dby5,int dby6,int dby7,int dby8,int dby9,int dby10,int dbyr,int dbye,
           int bgx,int bgy,int cx,int cy,POINT cp)
{
        int ci=2;
        int cf=0;
        int m=400;
        int p=20;
    while(1){
        GetCursorPos(&cp);
        cx=cp.x;
        cy=cp.y;
        if(cx>dbx1 && cx<dbx1+bgx && cy>dby1+p && cy<dby1+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx1,dby1,cf,"1");
            choice=1;
            delay(m);
            button(dbx1,dby1,ci,"1");
            break;
        }
        else if(cx>dbx2 && cx<dbx2+bgx && cy>dby2+p && cy<dby2+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx2,dby2,cf,"2");
            choice=2;
            delay(m);
            button(dbx2,dby2,ci,"2");
            break;
        }
        else if(cx>dbxr && cx<dbxr+bgx && cy>dbyr+p && cy<dbyr+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbxr,dbyr,cf,"Reset");
            delay(m);
            button(dbxr,dbyr,1,"Reset");
        }
        else if(cx>dbxe && cx<dbxe+bgx && cy>dbye+p && cy<dbye+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbxe,dbye,cf,"Exit");
            delay(m);
            button(dbxe,dbye,4,"Exit");
            exit(0);
        }
        else if(cx>dbx3 && cx<dbx3+bgx && cy>dby3+p && cy<dby3+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx3,dby3,cf,"3");
            delay(m);
            button(dbx3,dby3,ci,"3");
        }
        else if(cx>dbx8 && cx<dbx8+bgx && cy>dby8+p && cy<dby8+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx8,dby8,cf,"8");
            delay(m);
            button(dbx8,dby8,ci,"8");
        }
        else if(cx>dbx10 && cx<dbx10+bgx && cy>dby10+p && cy<dby10+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx10,dby10,cf,"10");
            delay(m);
            button(dbx10,dby10,ci,"10");
        }
        else if(cx>dbx4 && cx<dbx4+bgx && cy>dby4+p && cy<dby4+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx4,dby4,cf,"4");
            delay(m);
            button(dbx4,dby4,ci,"4");
        }
        else if(cx>dbx5 && cx<dbx5+bgx && cy>dby5+p && cy<dby5+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx5,dby5,cf,"5");
            delay(m);
            button(dbx5,dby5,ci,"5");
        }
        else if(cx>dbx6 && cx<dbx6+bgx && cy>dby6+p && cy<dby6+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx6,dby6,cf,"6");
            delay(m);
            button(dbx6,dby6,ci,"6");
        }
        else if(cx>dbx7 && cx<dbx7+bgx && cy>dby7+p && cy<dby7+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx7,dby7,cf,"7");
            delay(m);
            button(dbx7,dby7,ci,"7");
        }

        else if(cx>dbx9 && cx<dbx9+bgx && cy>dby9 +p&& cy<dby9+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx9,dby9,cf,"9");
            delay(m);
            button(dbx9,dby9,ci,"9");
        }
    }
}

void check3(int dbx1,int dbx2,int dbx3,int dbx4,int dbx5,int dbx6,int dbx7,int dbx8,int dbx9,int dbx10,int dbxr,int dbxe,
           int dby1,int dby2,int dby3,int dby4,int dby5,int dby6,int dby7,int dby8,int dby9,int dby10,int dbyr,int dbye,
           int bgx,int bgy,int cx,int cy,POINT cp)
{
        int ci=2;
        int cf=0;
        int m=400;
        int p=20;
    while(1){
        GetCursorPos(&cp);
        cx=cp.x;
        cy=cp.y;
        if(cx>dbx1 && cx<dbx1+bgx && cy>dby1+p && cy<dby1+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx1,dby1,cf,"1");
            sour=1;
            delay(m);
            button(dbx1,dby1,ci,"1");
            break;
        }
        else if(cx>dbx2 && cx<dbx2+bgx && cy>dby2+p && cy<dby2+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx2,dby2,cf,"2");
            sour=2;
            delay(m);
            button(dbx2,dby2,ci,"2");
            break;
        }

        else if(cx>dbx3 && cx<dbx3+bgx && cy>dby3+p && cy<dby3+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx3,dby3,cf,"3");
            sour=3;
            delay(m);
            button(dbx3,dby3,ci,"3");
            break;
        }
        else if(cx>dbx8 && cx<dbx8+bgx && cy>dby8+p && cy<dby8+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx8,dby8,cf,"8");
            sour=8;
            delay(m);
            button(dbx8,dby8,ci,"8");
            break;
        }
        else if(cx>dbx10 && cx<dbx10+bgx && cy>dby10+p && cy<dby10+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx10,dby10,cf,"10");
            sour=10;
            delay(m);
            button(dbx10,dby10,ci,"10");
            break;
        }
        else if(cx>dbx4 && cx<dbx4+bgx && cy>dby4+p && cy<dby4+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx4,dby4,cf,"4");
            sour=4;
            delay(m);
            button(dbx4,dby4,ci,"4");
            break;
        }
        else if(cx>dbx5 && cx<dbx5+bgx && cy>dby5+p && cy<dby5+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx5,dby5,cf,"5");
            sour=5;
            delay(m);
            button(dbx5,dby5,ci,"5");
            break;
        }
        else if(cx>dbx6 && cx<dbx6+bgx && cy>dby6+p && cy<dby6+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx6,dby6,cf,"6");
            sour=6;
            delay(m);
            button(dbx6,dby6,ci,"6");
            break;
        }
        else if(cx>dbx7 && cx<dbx7+bgx && cy>dby7+p && cy<dby7+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx7,dby7,cf,"7");
            sour=7;
            delay(m);
            button(dbx7,dby7,ci,"7");
            break;
        }

        else if(cx>dbx9 && cx<dbx9+bgx && cy>dby9+p && cy<dby9+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx9,dby9,cf,"9");
            sour=9;
            delay(m);
            button(dbx9,dby9,ci,"9");
            break;
        }
         else if(cx>dbxr && cx<dbxr+bgx && cy>dbyr+p && cy<dbyr+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbxr,dbyr,cf,"Reset");
            delay(m);
            button(dbxr,dbyr,1,"Reset");
        }
        else if(cx>dbxe && cx<dbxe+bgx && cy>dbye+p && cy<dbye+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbxe,dbye,cf,"Exit");
            delay(m);
            button(dbxe,dbye,4,"Exit");
            exit(0);
        }
    }
}

void check4(int dbx1,int dbx2,int dbx3,int dbx4,int dbx5,int dbx6,int dbx7,int dbx8,int dbx9,int dbx10,int dbxr,int dbxe,
           int dby1,int dby2,int dby3,int dby4,int dby5,int dby6,int dby7,int dby8,int dby9,int dby10,int dbyr,int dbye,
           int bgx,int bgy,int cx,int cy,POINT cp)
{
        int ci=2;
        int cf=0;
        int m=400;
        int p=20;
    while(1){
        GetCursorPos(&cp);
        cx=cp.x;
        cy=cp.y;
        if(cx>dbx1 && cx<dbx1+bgx && cy>dby1+p && cy<dby1+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx1,dby1,cf,"1");
            sour=1;
            delay(m);
            button(dbx1,dby1,ci,"1");
            break;
        }
        else if(cx>dbx2 && cx<dbx2+bgx && cy>dby2+p && cy<dby2+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx2,dby2,cf,"2");
            sour=2;
            delay(m);
            button(dbx2,dby2,ci,"2");
            break;
        }

        else if(cx>dbx3 && cx<dbx3+bgx && cy>dby3+p && cy<dby3+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx3,dby3,cf,"3");
            fcity=3;
            delay(m);
            button(dbx3,dby3,ci,"3");
            break;
        }
        else if(cx>dbx8 && cx<dbx8+bgx && cy>dby8+p && cy<dby8+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx8,dby8,cf,"8");
            fcity=8;
            delay(m);
            button(dbx8,dby8,ci,"8");
            break;
        }
        else if(cx>dbx10 && cx<dbx10+bgx && cy>dby10+p && cy<dby10+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx10,dby10,cf,"10");
            fcity=10;
            delay(m);
            button(dbx10,dby10,ci,"10");
            break;
        }
        else if(cx>dbx4 && cx<dbx4+bgx && cy>dby4+p && cy<dby4+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx4,dby4,cf,"4");
            fcity=4;
            delay(m);
            button(dbx4,dby4,ci,"4");
            break;
        }
        else if(cx>dbx5 && cx<dbx5+bgx && cy>dby5+p && cy<dby5+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx5,dby5,cf,"5");
            fcity=5;
            delay(m);
            button(dbx5,dby5,ci,"5");
            break;
        }
        else if(cx>dbx6 && cx<dbx6+bgx && cy>dby6+p && cy<dby6+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx6,dby6,cf,"6");
            fcity=6;
            delay(m);
            button(dbx6,dby6,ci,"6");
            break;
        }
        else if(cx>dbx7 && cx<dbx7+bgx && cy>dby7+p && cy<dby7+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx7,dby7,cf,"7");
            fcity=7;
            delay(m);
            button(dbx7,dby7,ci,"7");
            break;
        }

        else if(cx>dbx9 && cx<dbx9+bgx && cy>dby9+p && cy<dby9+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbx9,dby9,cf,"9");
            fcity=9;
            delay(m);
            button(dbx9,dby9,ci,"9");
            break;
        }
        else if(cx>dbxr && cx<dbxr+bgx && cy>dbyr+p && cy<dbyr+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbxr,dbyr,cf,"Reset");
            delay(m);
            button(dbxr,dbyr,1,"Reset");
        }
        else if(cx>dbxe && cx<dbxe+bgx && cy>dbye+p && cy<dbye+bgy+p && GetAsyncKeyState(VK_LBUTTON) )
        {
            button(dbxe,dbye,cf,"Exit");
            delay(m);
            button(dbxe,dbye,4,"Exit");
            exit(0);
        }
    }
}
void dispValue(int x,int y,int v)
{
    char a[3];
    char b[1];
    setcolor(LIGHTGREEN);
    setbkcolor(BLACK);
    sprintf(a,"%ld",v);
    sprintf(b,"%s",a);
    settextstyle(10, HORIZ_DIR, 2);
    outtextxy(x, y, b);
}

float angle=270;
struct arccoordstype a, b;
void c1(int a1)
{
    setbkcolor(CYAN);
    setcolor(CYAN);
    arc(getmaxx()/2,getmaxy()/2,angle-a1,angle-a1,35);
    getarccoords(&a);
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,BLACK);
    fillellipse(a.xstart,a.ystart,4,4);
}

main()
{
    int gd = DETECT, gm, x, y,page=0;
    POINT cp;
    float angle1 = 90;
    struct arccoordstype a2, b2;
    int cx,cy;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    DWORD shr=GetSystemMetrics(SM_CYSCREEN);
    DWORD swr=GetSystemMetrics(SM_CXSCREEN);
    int sh=0.9*(shr);
    int sw=(swr);
    int th,tw;
    initwindow(sw,sh,"Travel Agency",-3,-3,false,true);

    //#####################Starting##############################
       delay(800);
   while(angle1<=450)
   {
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,50);
      setcolor(RED);
      getarccoords(&a2);
      circle(a2.xstart,a2.ystart,25);
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,100);
      setcolor(BLUE);
      getarccoords(&a2);
      circle(a2.xstart,a2.ystart,25);
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,150);
      getarccoords(&a2);
      setcolor(CYAN);
      circle(a2.xstart,a2.ystart,25);
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,200);
      setcolor(GREEN);
      getarccoords(&a2);
      circle(a2.xstart,a2.ystart,25);
      setcolor(BLACK);
      arc(getmaxx()/2,getmaxy()/2,angle1,angle1+1,250);
      setcolor(LIGHTCYAN);
      getarccoords(&a2);
      circle(a2.xstart,a2.ystart,50);
      angle1 = angle1+2;
      delay(1);
   }
   delay(500);
   setcolor(LIGHTCYAN);
   outtextxy(30,20,"Shubham Dwivedi");
   outtextxy(30,40,"16103020");
   delay(500);

   outtextxy(sw-120,20,"Ishan Agarwal");
   outtextxy(sw-120,40,"16103242");
   delay(500);

   outtextxy(30,sh-60,"Ritik Jain");
   outtextxy(30,sh-40,"16103240");
   delay(500);

   outtextxy(sw-150,sh-60,"Shubham Kr Singh");
   outtextxy(sw-150,sh-40,"16103030");
   delay(500);

   settextstyle(BOLD_FONT,HORIZ_DIR,3);
   outtextxy(181,sh/2-12,"PRESS");
   delay(400);
   outtextxy(sw/2-7,sh/2-12,"A");
   delay(400);
   outtextxy(sw-250,sh/2-12,"KEY!!");

   getch();
   setbkcolor(CYAN);
   setcolor(CYAN);
   settextstyle(10,HORIZ_DIR,1);
   delay(400);

     while(angle!=1230)
     {
         setactivepage(page);
         setvisualpage(1-page);
         cleardevice();

         setcolor(BLACK);
         outtextxy((getmaxx()/2)-45,(getmaxy()/2)+70,"Loading...");

         if(angle>=0 && angle<=990)
         c1(0);

         if(angle>=300 && angle<=990)
            c1(30);

         if(angle>=330 && angle<=990)
            c1(60);

         if(angle>=360 && angle<=990)
            c1(90);

         if(angle>=390 && angle<=990)
            c1(120);

         if(angle>=420 && angle<=990)
            c1(150);

         if(angle>=450 && angle<=990)
            c1(180);

         if(angle>=480 && angle<=990)
            c1(210);

        if(angle>990 && angle<=1020)
        {
            c1(30);
            c1(60);
            c1(90);
            c1(120);
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1020 && angle<=1050)
        {
            c1(60);
            c1(90);
            c1(120);
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1050 && angle<=1080)
        {
            c1(90);
            c1(120);
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1080 && angle<=1110)
        {
            c1(120);
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1110 && angle<=1140)
        {
            c1(150);
            c1(180);
            c1(210);
        }
        if(angle>1140 && angle<=1170)
        {
            c1(180);
            c1(210);
        }
        if(angle>1170 && angle<=1200)
        {
            c1(210);
        }
        if(angle>1200)
        {

        }
         angle=angle+2;
         delay(1);
         page=1-page;
     }
     setactivepage(page);
     cleardevice();
     outtextxy((getmaxx()/2)-45,(getmaxy()/2)+70,"Lets Go!!");
     getch();
     cleardevice();
    //#####################End Of Strating#######################
    setfillstyle(SOLID_FILL, BLACK);
    bar(0,0,sw,sh);
    setcolor(LIGHTGREEN);
    setbkcolor(BLACK);
    settextstyle(10, HORIZ_DIR, 4);
    outtextxy((sw-350)/2-textwidth("Hello")/2,sh/2-textheight("Hello")/2,"Hello!");
    cw(sw,sh);

    //g=button gap gw=gap width
    int gw=100;
    int gh=60;
    int gx=315;
    int gy=340;

    int cwx1=sw-350;
    int cwx2=sw;
    int cwy1=1;
    int cwy2=sh-1;
    int dilx1=cwx1+10;
    int dily1=cwy1+75;
    int dilx2=cwx2-10;
    int dily2=(abs(cwy2-cwy1))/2;

    int dbx1= sw-gx;
    int dbx2= sw-gx+gw;
    int dbx3= sw-gx+2*gw;
    int dbx4= sw-gx;
    int dbx5= sw-gx+gw;
    int dbx6= sw-gx+2*gw;
    int dbx7= sw-gx;
    int dbx8= sw-gx+gw;
    int dbx9= sw-gx+2*gw;
    int dbx10= sw-gx+gw;

    int dby1= sh-gy;
    int dby2= sh-gy;
    int dby3= sh-gy;
    int dby4= sh-gy+gh;
    int dby5= sh-gy+gh;
    int dby6= sh-gy+gh;
    int dby7= sh-gy+2*gh;
    int dby8= sh-gy+2*gh;
    int dby9= sh-gy+2*gh;
    int dby10= sh-gy+3*gh;

    int dbxr=sw-gx;
    int dbyr=sh-90;
    int dbxe=sw-gx+2*gw;
    int dbye=sh-90;

    int bgx=80;
    int bgy=40;
    int ba=0;

    button(dbx1,dby1+ba,2,"1");
    button(dbx2,dby2+ba,2,"2");
    button(dbx3,dby3+ba,2,"3");

    button(dbx4,dby4+ba,2,"4");
    button(dbx5,dby5+ba,2,"5");
    button(dbx6,dby6+ba,2,"6");

    button(dbx7,dby7+ba,2,"7");
    button(dbx8,dby8+ba,2,"8");
    button(dbx9,dby9+ba,2,"9");

    button(dbx10,dby10+ba,2,"10");


    button(dbxe,dbye+ba,4,"Exit");
    button(dbxr,dbyr+ba,1,"Reset");


    data[0].x=sw/2-350;data[0].y=sh/2-20;
    data[1].x=sw/2-200;data[1].y=sh/2-150;
    data[2].x=sw/2+150;data[2].y=sh/2+50;
    data[3].x=sw/2-225;data[3].y=sh/2+100;
    data[4].x=sw/2-480;data[4].y=sh/2+220;
    data[5].x=sw/2-650;data[5].y=sh/2-50;
    data[6].x=sw/2-400;data[6].y=sh/2-320;
    data[7].x=sw/2+100;data[7].y=sh/2-250;
    data[8].x=sw/2+250;data[8].y=sh/2-150;
    data[9].x=sw/2+250;data[9].y=sh/2+200;

    setfillstyle(SOLID_FILL, BLACK);
    bar(dilx1,dily1,dilx2,dily2);
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-40,"Press no. of cities");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2),"and");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+40,"Give distance inputs");

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);
    check1(dbx1,dbx2,dbx3,dbx4,dbx5,dbx6,dbx7,dbx8,dbx9,dbx10,dbxr,dbxe,
          dby1,dby2,dby3,dby4,dby5,dby6,dby7,dby8,dby9,dby10,dbyr,dbye,
          bgx,bgy,cx,cy,cp);
    setfillstyle(SOLID_FILL, LIGHTRED);
    fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);

    //cout<<"\nEnter distance matrix of cities : ";

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>ary[i][j];
        }
    }

    //starts again
    resetAll:

    setfillstyle(SOLID_FILL, BLACK);
    bar(dilx1,dily1,dilx2,dily2);
    setbkcolor(BLACK);
    bar(0,0,sw-350,sh);
    setcolor(LIGHTGREEN);
    th=textheight("Graphical Representation");
    tw=textwidth("Graphical Representation");
    settextstyle(10, HORIZ_DIR, 3);
    outtextxy((sw-350)/2-tw/2,sh-50,"Graphical Representation");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2),"Updating...");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i!=j && ary[i][j]!=0)
            {
                drawLine(i,j,ary[i][j]);
                delay(100);
            }
        }
    }

    for(int i=1;i<=n;i++)
    {
        dl(i);
        delay(200);
    }
    setfillstyle(SOLID_FILL, BLACK);
    bar(dilx1,dily1,dilx2,dily2);
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-120,"press 1");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-100,"for minimum distance");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-80,"required for coming back");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-60,"to the initial city after");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-40,"after going all cities");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2),"OR");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+40,"press 2");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+60,"for knowing the minimum");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+80,"distance of a city");
    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+100,"from another city");

    setcolor(BLACK);
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);
    check2(dbx1,dbx2,dbx3,dbx4,dbx5,dbx6,dbx7,dbx8,dbx9,dbx10,dbxr,dbxe,
          dby1,dby2,dby3,dby4,dby5,dby6,dby7,dby8,dby9,dby10,dbyr,dbye,
          bgx,bgy,cx,cy,cp);
    setfillstyle(SOLID_FILL, LIGHTRED);
    fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);
        switch(choice)
        {
              case 1 :{
                       for(int i=0;i<(1<<n);i++)
                        {
                            for(int j=0;j<n;j++)
                                {
                                    dp[i][j] = -1;
                                    vertex[i][j] = -1;
                                }
                        }
                        int k=tsp(1,0);
                        if(k==INT_MAX)
                        {
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(dilx1,dily1,dilx2,dily2);
                            disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2),"path not possible");
                            //cout<<"\npath not possible:";
                        }
                        else
                        {
                            vector<int> path;

                            int city = 0;
                            int m = 1;
                            int u;
                            path.push_back(1);
                            while(m != (1<<n)-1)
                            {
                                u = vertex[m][city];
                                path.push_back(u+1);
                                m = m|(1<<u);
                                city = u;
                            }
                                path.push_back(1);
                                if(path.size()!=n+1)
                                {
                                    setfillstyle(SOLID_FILL, BLACK);
                                    bar(dilx1,dily1,dilx2,dily2);
                                    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2),"path not possible");
                                    //cout<<"\nPath not possible:";
                                }
                                else
                                {
                                    setfillstyle(SOLID_FILL, BLACK);
                                    bar(dilx1,dily1,dilx2,dily2);
                                    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-80,"Minimum cost is");
                                    dispValue(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-60,k);
                                    disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+20,"Path is");
                                    //cout<<"\n\nMinimum cost is "<<k;
                                    //cout<<"\nPath is : ";
                                    int i,shift,dshift,gpath;
                                    shift=130;
                                    dshift=30;
                                    for(i=0;i<path.size()-1;i++)
                                    {
                                        gpath=path[i];
                                        dispValue(abs(dilx1-dilx2)/2+min(dilx1,dilx2)-shift,abs(dily1-dily2)/2+min(dily1,dily2)+80,gpath);
                                        shift=shift-dshift;
                                        disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2)-shift,abs(dily1-dily2)/2+min(dily1,dily2)+60,"->");
                                        //cout<<path[i]<<"-->";
                                        int l=ary[path[i]-1][path[i+1]-1];
                                        DDA(path[i],path[i+1],l);
                                    }
                                    gpath=path[i];
                                    dispValue(abs(dilx1-dilx2)/2+min(dilx1,dilx2)-shift,abs(dily1-dily2)/2+min(dily1,dily2)+80,gpath);
                                    //cout<<path[i];
                                }
                            }

                       break;
                     }
              case 2 :{
                        setfillstyle(SOLID_FILL, BLACK);
                        bar(dilx1,dily1,dilx2,dily2);
                       int fcity2;
                       disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2),"Press source city no.");
                       //cout<<"\nEnter source city : ";
                       delay(1000);

                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL, LIGHTGREEN);
                        fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);
                       check3(dbx1,dbx2,dbx3,dbx4,dbx5,dbx6,dbx7,dbx8,dbx9,dbx10,dbxr,dbxe,
                        dby1,dby2,dby3,dby4,dby5,dby6,dby7,dby8,dby9,dby10,dbyr,dbye,
                        bgx,bgy,cx,cy,cp);
                        setfillstyle(SOLID_FILL, LIGHTRED);
                        fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);

                       setfillstyle(SOLID_FILL, BLACK);
                       bar(dilx1,dily1,dilx2,dily2);
                       disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-30,"Press the city no.");
                       disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-10,"whose minimum distance");
                       disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+10,"is required from");
                       disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+30,"the source");
                       //cout<<"\n Enter the city whose minimum distance is required from the source :";
                       delay(1000);
                        setcolor(BLACK);
                        setfillstyle(SOLID_FILL, LIGHTGREEN);
                        fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);

                       check4(dbx1,dbx2,dbx3,dbx4,dbx5,dbx6,dbx7,dbx8,dbx9,dbx10,dbxr,dbxe,
                        dby1,dby2,dby3,dby4,dby5,dby6,dby7,dby8,dby9,dby10,dbyr,dbye,
                        bgx,bgy,cx,cy,cp);

                        setfillstyle(SOLID_FILL, LIGHTRED);
                        fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);
                       fcity=fcity-1;
                       fcity2=fcity;
                       dijkstra(ary,sour-1,n);
                       cout<<endl;
                       vector<int> path1;
                       path1.push_back(fcity+1);
                       while(parent[fcity]!=sour-1)
                       {
                           path1.push_back(parent[fcity]+1);
                           fcity=parent[fcity];
                       }
                       path1.push_back(sour);
                       vector<int> path2;
                       for(int i=path1.size()-1;i>=0;i--)
                       {
                           path2.push_back(path1[i]);
                       }

                       if(dist[fcity2]==INT_MAX||fcity2==sour-1)
                       {
                           setfillstyle(SOLID_FILL, BLACK);
                           bar(dilx1,dily1,dilx2,dily2);
                           disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2),"Path not possible");
                           //cout<<"\nPath not possible";
                       }
                       else
                       {
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(dilx1,dily1,dilx2,dily2);
                            int cDis=dist[fcity2];
                            disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-100,"Minimum distance of");
                            disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-80,"asked city is");
                            dispValue(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)-60,cDis);
                            //cout<<"\n Minimum distance of asked city is:"<<dist[fcity2];
                            //cout<<"\nPath is : ";
                            disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2)+20,"Path is");
                            ncount=path2[path2.size()-1];
                            int i,gpath;
                            // #########graphics
                            int shift=100;
                            int dshift=30;
                            for(i=0;i<path2.size()-1;i++)
                            {
                                gpath=path2[i];
                                dispValue(abs(dilx1-dilx2)/2+min(dilx1,dilx2)-shift,abs(dily1-dily2)/2+min(dily1,dily2)+80,gpath);
                                shift=shift-dshift;
                                disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2)-shift,abs(dily1-dily2)/2+min(dily1,dily2)+60,"->");
                                //cout<<path2[i]<<"-->";
                                int k=ary[path2[i]-1][path2[i+1]-1];
                               DDA(path2[i],path2[i+1],k);
                            }
                            // #########graphics
                            gpath=path2[i];
                            dispValue(abs(dilx1-dilx2)/2+min(dilx1,dilx2)-shift,abs(dily1-dily2)/2+min(dily1,dily2)+80,gpath);
                            //cout<<path2[i];
                       }

                       break;
                      }
              default :{
                            setfillstyle(SOLID_FILL, BLACK);
                            bar(dilx1,dily1,dilx2,dily2);
                            disp(abs(dilx1-dilx2)/2+min(dilx1,dilx2),abs(dily1-dily2)/2+min(dily1,dily2),"Wrong choice entered");
                            //cout<<"\nWrong choice entered";
                            break;
                        }
         }
         setcolor(BLACK);
         setfillstyle(SOLID_FILL, LIGHTGREEN);
         fillellipse(abs(cwx1-cwx2)/2+min(cwx1,cwx2),55,10,10);
         int minutes=400;
         int pp=20;
         while(1){
            GetCursorPos(&cp);
            cx=cp.x;
            cy=cp.y;
            if(cx>dbxr && cx<dbxr+bgx && cy>dbyr+pp && cy<dbyr+bgy+pp && GetAsyncKeyState(VK_LBUTTON) )
            {
                button(dbxr,dbyr,0,"Reset");
                delay(minutes);
                button(dbxr,dbyr,1,"Reset");
                goto resetAll;
            }
            else if(cx>dbxe && cx<dbxe+bgx && cy>dbye+pp && cy<dbye+bgy+pp && GetAsyncKeyState(VK_LBUTTON) )
            {
                button(dbxe,dbye,0,"Exit");
                delay(minutes);
                button(dbxe,dbye,4,"Exit");
                exit(0);
            }
         }

    getch();
    closegraph();
}

