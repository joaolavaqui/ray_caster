#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define Rad PI/180

int main(void) {

  //MAP
  float wh[60], ptr[60], wc[60], wht=0;

  int heightmap[]={
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,3,
  0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,3,
  0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,3,
  0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,3,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
  0,0,0,0,0,0,0,0,1,2,3,4,4,4,4,4,
  0,0,0,0,0,0,0,0,1,2,3,4,4,4,4,4,
  0,0,0,0,0,0,0,0,1,2,3,4,4,4,4,4,
  0,0,0,0,0,0,0,0,1,2,3,4,4,4,4,4};
  int map[]={
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
  1,0,0,1,0,0,2,0,1,0,0,1,2,2,2,2,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,2,0,0,1,0,1,0,0,1,2,2,2,2,
  1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,
  1,0,0,2,2,2,2,2,2,2,2,2,2,2,2,2,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,
  1,0,0,0,0,0,0,2,2,2,2,2,2,2,2,2,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
  
  //PLAYER
  float pX, pY, pA, Speed; int pH;
  pX=2.0;
  pY=2.0;
  pA=0.0;
  pH=0;
  Speed=0.8;

  //RAY
  float rX=0, rY=0, rA=0;
  int rtX=0, rtY=0, input=0;

  //run!
  while(1)
  {
    //calculate walls
    for(int i=-30;i<30;i++)
    {
        //set ray
        rA=pA+i;
        if(rA>360){rA-=360;}
        if(rA<0){rA+=360;}

        rX=pX; rY=pY;
        rtX=rX; rtY=rY;

        //cast ray
        while(map[(rtY*16)+rtX]==0)
        {
          rX+=cos(rA*Rad)*0.1;
          rY+=sin(rA*Rad)*0.1;
          rtX=rX; rtY=rY;
          wht+=0.1;
        }

        //store wall height
        wh[i+30]=(60/wht)/cos(i*Rad);
        ptr[i+30]=(20-wh[i+30]-((heightmap[(rtY*16)+rtX]-pH)/wht*30))/2;
        wc[i+30]=map[(rtY*16)+rtX];
        wht=0;
    }

    //render
    system("cls");
    for(int reY=-10 ; reY<26 ; reY++)
    {
      printf("\n");
      for(int reX=0 ; reX<60 ; reX++)
      {
        if(reY>ptr[reX] && reY<ptr[reX]+wh[reX] && wc[reX]==1)
        {
          printf("%c", 219);
        }
        else if(reY>ptr[reX] && reY<ptr[reX]+wh[reX] && wc[reX]==2)
        {
          printf("%c", 178);
        }
        else if(reY>=ptr[reX]+wh[reX])
        {
          printf("%c", 176);
        }
        else 
        {
          printf(" ");
        }
      }
    }
    printf("\n\n");
    
    //move player
    input=getchar();
    if(input=='a'){pA-=10;}
    if(input=='d'){pA+=10;}
    if(pA>360){pA-=(360);}
    if(pA<0){pA+=360;}
    
    if(input=='w')
    {
      pX+=cos(pA*Rad)* Speed;
      pY+=sin(pA*Rad)* Speed;

      if(map[((int)pY*16)+(int)pX]!=0 || heightmap[((int)pY*16)+(int)pX>pH+1])
      {
        pX-=cos(pA*Rad)* Speed;
        pY-=sin(pA*Rad)* Speed;
      }
    }
    if(input=='s')
    {
      pX-=cos(pA*Rad)* Speed;
      pY-=sin(pA*Rad)* Speed;

      if(map[((int)pY*16)+(int)pX]!=0 || heightmap[((int)pY*16)+(int)pX>pH+1])
      {
        pX+=cos(pA*Rad)* Speed;
        pY+=sin(pA*Rad)* Speed;
      }
    }

    pH=heightmap[((int)pY*16)+(int)pX];

    
  }
  return 0;
}
