#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

#define B 0
#define G 1
#define R 2
#define RWEIGHT 0.299
#define GWEIGHT 0.587
#define BWEIGHT 0.114
#define QUANTIZATIONDEFAULT 150
#define INVOKEERROR "usage: tf <Image_Path> [-q <Quantization_Amount>]\n"

Mat imageIn, quantized, segmented, region;
int maxRegion;

void luminance()
{
	int sizex = quantized.cols;
	int sizey = quantized.rows;
	for (int i=0;i<sizey;i++)
		for (int j=0;j<sizex;j++)
		{
			Vec3b pixel = quantized.at<Vec3b>(i,j);
			float luminance = RWEIGHT * pixel.val[R] + GWEIGHT * pixel.val[G] + BWEIGHT * pixel.val[B];
			pixel.val[R] = luminance;
			pixel.val[G] = luminance;
			pixel.val[B] = luminance;
			quantized.at<Vec3b>(i,j) = pixel;
		}
}


void quantization(int amount)
{
	int sizex = quantized.cols;
	int sizey = quantized.rows;
	
	int lower = 256;
	int higher = -1;
	
	if(amount == 0)
	{
		std::cout << "Quantization cannot be 0\n";
		exit(0);
	}
	
	// convert image to grayscale
	luminance(); 
	
	// get limits
	for (int i=0;i<sizey;i++)
		for (int j=0;j<sizex;j++)
		{
			Vec3b pixel = quantized.at<Vec3b>(i,j);
			if (pixel.val[R] > higher)
				higher = pixel.val[R];
			if (pixel.val[R] < lower)
				lower = pixel.val[R];
		}	
	
	
	// get bin sizes
	int tam_int = higher - lower + 1;
	
	if (amount >= tam_int)
		return;
	
	int tb = tam_int/amount;
	
	
	// set bin
	for (int i=0;i<sizey;i++)
		for (int j=0;j<sizex;j++)
		{
			Vec3b pixel = quantized.at<Vec3b>(i,j);
			int newVal = (pixel.val[R] - lower)/tb;
			newVal = lower + newVal*tb;
			pixel.val[R] = newVal;
			pixel.val[G] = newVal;
			pixel.val[B] = newVal;
			quantized.at<Vec3b>(i,j) = pixel;			
		}
}

void segment()
{
	int sizex = quantized.cols;
	int sizey = quantized.rows;
	
	bool processed[imageIn.rows][imageIn.cols], current[imageIn.rows][imageIn.cols];
	
	
	
	for(int i=0; i<imageIn.rows; i++)
		for(int j=0; j<imageIn.cols; j++)
		{
			current[i][j] = false;
			processed[i][j] = false;
		}
	int regioni = 0;
	for(int i=0; i<imageIn.rows; i++)
	{
	std::cout << "Segmenting, " << std::setprecision(2) << ((float)i/sizey)*100 << "%     \t\t\r" << std::flush;
		for(int j=0; j<imageIn.cols; j++)
		{
			if (!processed[i][j])
			{
				regioni++;
				int value = (quantized.at<Vec3b>(i,j)).val[R];
				processed[i][j] = true;
				current[i][j] = true;
				bool _continue = true;
				
				// Repeat until converged
				while(_continue)
				{
					_continue = false;
					for(int k=0; k<imageIn.rows; k++)
					{
						for(int l=0; l<imageIn.cols; l++)
						{
							if((k-1 >= 0)&&(current[k-1][l])&&((quantized.at<Vec3b>(k-1,l)).val[R] == value)&&(!current[k][l]))
							{
								_continue = true;
								processed[k][l] = true;
								current[k][l] = true;
								region.at<int>(k,l) = regioni;
							}
							if((k+1 < sizey)&&(current[k+1][l])&&((quantized.at<Vec3b>(k+1,l)).val[R] == value)&&(!current[k][l]))
							{
								_continue = true;
								processed[k][l] = true;
								current[k][l] = true;
								region.at<int>(k,l) = regioni;
							}
							if((l-1 >= 0)&&(current[k][l-1])&&((quantized.at<Vec3b>(k,l-1)).val[R] == value)&&(!current[k][l]))
							{
								_continue = true;
								processed[k][l] = true;
								current[k][l] = true;
								region.at<int>(k,l) = regioni;
							}
							if((l+1 < sizey)&&(current[k][l+1])&&((quantized.at<Vec3b>(k,l+1)).val[R] == value)&&(!current[k][l]))
							{
								_continue = true;
								processed[k][l] = true;
								current[k][l] = true;
								region.at<int>(k,l) = regioni;
							}
						}
					}
				}
			}
			
			int r = rand()%256;
			int g = rand()%256;
			int b = rand()%256;
		
			for(int i=0; i< sizey; i++)
				for(int j=0; j<sizex; j++)
				{
					if(current[i][j])
					{
						current[i][j] = false;
						Vec3b pixel = quantized.at<Vec3b>(i,j);
						pixel.val[R] = r;
						pixel.val[G] = g;
						pixel.val[B] = b;
						quantized.at<Vec3b>(i,j) = pixel;
					}
				}
		}
	}
	printf("\n\n");
	maxRegion = regioni;
}

void erode()
{

}

void dilate()
{

}


int main(int argc, char** argv)
{
	int quantizationAmount;
	char* filename;
	if ( argc < 2 )
    {
        printf(INVOKEERROR);
        return -1;
    }

	filename = argv[1];
    imageIn = imread(filename , 1 );
    for(int i=0; i < argc; i++)
    {
    	if (strcmp(argv[i], "-q") == 0)
    	{
    		if (i+1 < argc)
    		{
    			quantizationAmount = atoi(argv[i+1]);
    		}
    		else
    		{
    		printf(INVOKEERROR);
    		}
		}
    }
    if (quantizationAmount <= 0)
    {
    	quantizationAmount = QUANTIZATIONDEFAULT;
    }
    if ( !imageIn.data )
    {
        printf("No image data \n");
        return -1;
    }

	srand(time(NULL));
    
    quantized = imageIn.clone();
    
    quantization(quantizationAmount);
    
    namedWindow("Input Image", WINDOW_AUTOSIZE );
    namedWindow("Output Image", WINDOW_AUTOSIZE);
    imshow("Input Image", imageIn);
    
    region = Mat::zeros(imageIn.rows, imageIn.cols, CV_16S);
    
    segment();
    
    FILE* dump = fopen("dump.txt", "w");
    for(int i=0; i<imageIn.rows; i++)
    {
    	for(int j=0; j<imageIn.cols; j++)
    	{
    		fprintf(dump, "%d ", region.at<int>(i,j));
    	}
    	fprintf(dump, "\r\n");
    }
    fflush(dump);
    
    imwrite("quantized.jpg", quantized);
    
	imshow("Output Image", quantized);
    
    waitKey(0);
    return 0;
}
