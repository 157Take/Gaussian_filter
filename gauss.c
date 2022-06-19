#include <gd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int array3x3[] = {1,2,1};
static int array5x5[] = {1,4,6,4,1};
static int array7x7[] = {1,6,15,20,15,6,1};

gdImagePtr gauss3x3(gdImagePtr im){
  int w,h,i,j,idx,r,g,b;
  gdImagePtr ret;

  w=gdImageSX(im);
  h=gdImageSY(im);

  ret = gdImageCreateTrueColor(w,h);

  for (i = 0; i < w ; i++){ 
    for (j = 0; j < h ; j++){
      int p,q;
      r = 0, g = 0, b = 0;
      for (p = -1; p < 2; p++){
	for(q = -1; q < 2; q++){
	  r+=array3x3[p+1]*array3x3[q+1]
	    *gdImageRed(im,gdImageGetPixel(im,i+p,j+q));
	  g+=array3x3[p+1]*array3x3[q+1]
	    *gdImageGreen(im,gdImageGetPixel(im,i+p,j+q));
	  b+=array3x3[p+1]*array3x3[q+1]
	    *gdImageBlue(im,gdImageGetPixel(im,i+p,j+q));
	}
      }

      r=(int)(r/16);
      g=(int)(g/16);
      b=(int)(b/16);
      
      r = r > 255 ? 255 : (r < 0 ? 0 : r);
      g = g > 255 ? 255 : (g < 0 ? 0 : g);
      b = b > 255 ? 255 : (b < 0 ? 0 : b);
      idx = gdImageColorExact(ret,r,g,b);
      if(idx==-1){
	idx=gdImageColorAllocate(ret,r,g,b);
      }
      gdImageSetPixel(ret,i,j,idx);
    }
  }
  return ret;
}

gdImagePtr gauss5x5(gdImagePtr im){
  int w,h,i,j,idx,r,g,b;
  gdImagePtr ret;

  w=gdImageSX(im);
  h=gdImageSY(im);

  ret = gdImageCreateTrueColor(w,h);

  for (i = 0; i < w ; i++){ 
    for (j = 0; j < h ; j++){
      int p,q;
      r = 0, g = 0, b = 0;
      for (p = -2; p < 3; p++){
	for(q = -2; q < 3; q++){
	  r+=array5x5[p+2]*array5x5[q+2]
	    *gdImageRed(im,gdImageGetPixel(im,i+p,j+q));
	  g+=array5x5[p+2]*array5x5[q+2]
	    *gdImageGreen(im,gdImageGetPixel(im,i+p,j+q));
	  b+=array5x5[p+2]*array5x5[q+2]
	    *gdImageBlue(im,gdImageGetPixel(im,i+p,j+q));
	}
      }

      r=(int)(r/256);
      g=(int)(g/256);
      b=(int)(b/256);
      
      r = r > 255 ? 255 : (r < 0 ? 0 : r);
      g = g > 255 ? 255 : (g < 0 ? 0 : g);
      b = b > 255 ? 255 : (b < 0 ? 0 : b);
      idx = gdImageColorExact(ret,r,g,b);
      if(idx==-1){
	idx=gdImageColorAllocate(ret,r,g,b);
      }
      gdImageSetPixel(ret,i,j,idx);
    }
  }
  return ret;
}

gdImagePtr gauss7x7(gdImagePtr im){
  int w,h,i,j,idx,r,g,b;
  gdImagePtr ret;

  w=gdImageSX(im);
  h=gdImageSY(im);

  ret = gdImageCreateTrueColor(w,h);

  for (i = 0; i < w ; i++){ 
    for (j = 0; j < h ; j++){
      int p,q;
      int r = 0, g = 0, b = 0;
      for (p = -3; p < 4; p++){
	for(q = -3; q < 4; q++){
	  r+=array7x7[p+3]*array7x7[q+3]
	    *gdImageRed(im,gdImageGetPixel(im,i+p,j+q));
	  g+=array7x7[p+3]*array7x7[q+3]
	    *gdImageGreen(im,gdImageGetPixel(im,i+p,j+q));
	  b+=array7x7[p+3]*array7x7[q+3]
	    *gdImageBlue(im,gdImageGetPixel(im,i+p,j+q));
	}
      }

      r=(int)(r/4096);
      g=(int)(g/4096);
      b=(int)(b/4096);
      
      r = r > 255 ? 255 : (r < 0 ? 0 : r);
      g = g > 255 ? 255 : (g < 0 ? 0 : g);
      b = b > 255 ? 255 : (b < 0 ? 0 : b);
      idx = gdImageColorExact(ret,r,g,b);
      if(idx==-1){
	idx=gdImageColorAllocate(ret,r,g,b);
      }
      gdImageSetPixel(ret,i,j,idx);
    }
  }
  return ret;
}


int main(const int argc,const char *argv[]){

  FILE *out,*in;
  gdImagePtr im,im_gauss;
  int width,height,i,j,color,r,g,b,pixel,y;

  if(argv[1]==NULL||argv[2]==NULL||!strcmp(argv[1],argv[2])){
    printf("argument error\n");
    exit(-1);
  }
  
  if((in=fopen(argv[1],"r"))==NULL){
    printf("file open error for %s\n",argv[1]);
    exit(-1);
  }
  
  if((out=fopen(argv[2],"wb"))==NULL){
    printf("file open error for %s\n",argv[2]);
    exit(-1);
  }

  im = gdImageCreateFromJpeg(in);

  width=gdImageSX(im);
  height=gdImageSY(im);

  //  im_gauss = gauss3x3(im);
  //  im_gauss = gauss5x5(im);
  im_gauss = gauss7x7(im);

  gdImageJpeg(im_gauss,out,-1);

  fclose(in);
  fclose(out);

  return 0;
  
}
