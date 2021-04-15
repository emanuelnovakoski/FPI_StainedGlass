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
#define ERODED 0
#define INVOKEERROR "usage: tf <Image_Path> [-q <quantization_amount>] [-s <steps_amount\n"

Mat imageIn, quantized, region;
int maxRegion = 0;

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
	{
		std::cout << "Quantizing... " << std::setprecision(4) << ((float)i/sizey)*100 << "%     \t\t\r" << std::flush;
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
	printf("Quantizing... 100%%     \n");
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
	int regioni = 1;
	for(int i=0; i<sizey; i++)
	{
	std::cout << "Segmenting... " << std::setprecision(4) << ((float)i/sizey)*100 << "%     \t\t\r" << std::flush;
		for(int j=0; j<sizex; j++)
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
					for(int k=0; k<sizey; k++)
					{
						for(int l=0; l<sizex; l++)
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
							if((l+1 < sizex)&&(current[k][l+1])&&((quantized.at<Vec3b>(k,l+1)).val[R] == value)&&(!current[k][l]))
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
	printf("Segmenting... 100%%     \n");
	maxRegion = regioni;

}

void erode()
{
	int sizex = region.cols;
	int sizey = region.rows;
	Mat temp;
	temp = region.clone();
	for(int r=1; r<maxRegion; r++)
	{
		std::cout << "	Progress... " << std::setprecision(4) << ((float)r/maxRegion)*100 << "%     \t\t\r" << std::flush;
		for(int i=0; i<sizey; i++)
		{
			for(int j=0; j<sizex; j++)
			{
				if((temp.at<int>(i,j) == r) && (
				(((i-1 > 0) && (temp.at<int>(i-1,j) != r))) || 
				(((i+1 < sizey-1) && (temp.at<int>(i+1,j) != r))) || 
				(((j+1 < sizex-1) && (temp.at<int>(i,j+1) != r))) || 
				(((j-1 > 0) && (temp.at<int>(i,j-1) != r))))
				)
				{
					region.at<int>(i,j) = ERODED;
					Vec3b pixel;
					pixel.val[R] = 0;
					pixel.val[G] = 0;
					pixel.val[B] = 0;
					quantized.at<Vec3b>(i,j) = pixel;	
				}	
					
			}
		}
	}
	printf("	Progress... 100%%         \n");
}

void dilate()
{
	int sizex = region.cols;
	int sizey = region.rows;
	Mat temp;
	temp = region.clone();
	for(int r=1; r<maxRegion; r++)
	{
	std::cout << "Progress... " << std::setprecision(4) << ((float)r/maxRegion)*100 << "%     \t\t\r" << std::flush;
		for(int i=1; i<sizey-1; i++)
		{
			for(int j=1; j<sizex-1; j++)
			{
				if((temp.at<int>(i,j) == ERODED) && (
				(((i-1 > 0) && (temp.at<int>(i-1,j) == r))) || 
				(((i+1 < sizey-1) && (temp.at<int>(i+1,j) == r))) || 
				(((j+1 < sizex-1) && (temp.at<int>(i,j+1) == r))) || 
				(((j-1 > 0) && (temp.at<int>(i,j-1) == r))))
				)
				{
					region.at<int>(i,j) = r;
				}	
					
			}
		}
		
	}
	printf("	Progress... 100%%         \n");
}


int main(int argc, char** argv)
{
	int quantizationAmount, stepAmount = 5;
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
		else if (strcmp(argv[i], "-s") == 0)
		{
			if (i+1 < argc)
			{
				stepAmount = atoi(argv[i+1]);
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
    
    region = Mat::zeros(quantized.rows, quantized.cols, CV_32S);
    
    segment();
    
    for(int i=0; i<stepAmount; i++)
    {
    	printf("Eroding... #%d\n", i+1);
    	erode();
    }
    for(int i=0; i<stepAmount + 2; i++)
    {
    	printf("Dilating... #%d\n", i+1);
    	dilate();
    }
	for(int r=0; r<maxRegion; r++)
	{
		int _r = rand() % 256;
		int _g = rand() % 256;
		int _b = rand() % 256;
		
		for(int i=0; i<region.cols; i++)
		{
			for(int j=0; j<region.rows; j++)
			{
				if(region.at<int>(i,j) == r)
				{
					Vec3b pixel;
					pixel.val[R] = _r;
					pixel.val[G] = _g;
					pixel.val[B] = _b;
					quantized.at<Vec3b>(i,j) = pixel;	
				}
			}
		}
	}

    imwrite("quantized.jpg", quantized);
    
	imshow("Output Image", quantized);
    waitKey(0);

    return 0;
}
