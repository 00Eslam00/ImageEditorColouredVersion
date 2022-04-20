// FCI � Programming 1 � 2022 - Assignment 3
// Program Name:    main.cpp
// Last Modification Date: 20/04/2022
// Author 1 and ID and Group: Eslam Amin Mostafa 20210064 S15
// Author 2 and ID and Group: Saead Mohamed Mohamed 20210159 S15
// Author 3 and ID and Group: Karim Mohamed Shebl 20210300 S15
// Teaching Assistant:  Nesma Mohamed & Yousra Ayman
// Purpose: 12 filters to make edits on colored bmp images

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image2[SIZE][SIZE][RGB];
unsigned char image3[SIZE][SIZE][RGB];

void loadRGBImage()
{
	char imageFileName[100];
	// Get coloured image file name
	cout << "Enter Image Name to Process: ";
	cin >> imageFileName;
	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");

	// check if file exist or not
	ifstream image_exist;
	image_exist.open(imageFileName);

	if (image_exist)
	{
		readRGBBMP(imageFileName, image2);
	}
	else
	{
		cout << "\ninvalid name \n";
		cout << "try again: \n";
		loadRGBImage();
	}
}

void loadRGBImage2()
{
	char imageFileName[100];
	// Get coloured image file name
	cout << "Enter Image Name to Process: ";
	cin >> imageFileName;
	// Add to it .bmp extension and load image
	strcat(imageFileName, ".bmp");

	// check if file exist or not
	ifstream image_exist;
	image_exist.open(imageFileName);

	if (image_exist)
	{
		readRGBBMP(imageFileName, image3);
	}
	else
	{
		cout << "\ninvalid name \n";
		cout << "try again: \n";
		loadRGBImage();
	}
}

void saveRGBImage()
{
	char imageFileName[100];
	cout << "Enter New Image Name: ";
	cin >> imageFileName;
	strcat(imageFileName, ".bmp");
	writeRGBBMP(imageFileName, image2);
}

void ConvertBlackAndWhiteRGB()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//check if the sum of colors is greater than average or not ....
			//if sum is greater convert it to white
			if (image2[i][j][0] + image2[i][j][1] + image2[i][j][2] > 384)
			{
				image2[i][j][0] = 255;
				image2[i][j][1] = 255;
				image2[i][j][2] = 255;
			}
			//else convert it to black
			else
			{
				image2[i][j][0] = 0;
				image2[i][j][1] = 0;
				image2[i][j][2] = 0;
			}
		}
	}
}

//invert the image color
void invertRGB()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < RGB; k++)
				//invert every pixal in photo
				image2[i][j][k] = 255 - image2[i][j][k];
		}
	}
}

// take part from image , then enlarge it
void enlargeRGB()
{
	int choice, x, y, z;
	cout << "Enter section you wanna take : ";
	cin >> choice;

	// if else statements to decide which part of photo will be taken

	if (choice == 1)
		x = 0, y = 0, z = 0;

	else if (choice == 2)
		x = 0, y = 128, z = 0;

	else if (choice == 3)
		x = 128, y = 0, z = 128;

	else if (choice == 4)
		x = 128, y = 128, z = 128;

	// array to carry pixels of one part in this photo
	int carry[SIZE][SIZE][RGB] = {{0}, {0}, {0}};

	// for loop to put one skip the other pixel in this array
	for (int i = 0; i < SIZE; i += 2)
	{
		x = z;
		for (int j = 0; j < SIZE; j += 2)
		{
			for (int k = 0; k < RGB; k++)
				carry[i][j][k] = image2[x][y][k];
			x++;
		}
		y++;
	}

	//this for loop to fill the empty pixels with the average of surrounded pixels around it
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < RGB; k++)
			{
				if (j == 0 && carry[i][j][k] == 0)
					carry[i][j][k] = ceil((carry[i - 1][j][k] + carry[i + 1][j][k] + carry[i][j + 1][k]) / 3.0);

				else if (j == 255 && carry[i][j][k] == 0)
					carry[i][j][k] = ceil((carry[i - 1][j][k] + carry[i + 1][j][k] + carry[i][j - 1][k]) / 3.0);

				else if (i == 0 && carry[i][j][k] == 0)
					carry[i][j][k] = ceil((carry[i][j - 1][k] + carry[i + 1][j][k] + carry[i][j + 1][k]) / 3.0);

				else if (i == 255 && carry[i][j][k] == 0)
					carry[i][j][k] = ceil((carry[i - 1][j][k] + carry[i][j - 1][k] + carry[i][j + 1][k]) / 3.0);

				else if (carry[i][j][k] == 0)
					carry[i][j][k] = ceil((carry[i - 1][j][k] + carry[i + 1][j][k] + carry[i][j + 1][k] + carry[i][j - 1][k]) / 4.0);
			}
		}
	}

	// to fill the main array with pixels of sub array "carry"
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < RGB; k++)
				image2[i][j][k] = carry[i][j][k];
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < i; j++)
		{
			swap(image2[i][j], image2[j][i]);
		}
	}
	cin.ignore();
}

//rotate image as user want

void rotate(){
	int all = ceil(SIZE / 2.0);
	for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < i; j++)
			{
				swap(image2[i][j], image2[j][i]);
			}
		}

		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < all; j++)
			{
				swap(image2[i][j], image2[i][SIZE - j]);
			}
		}
	
}


void rotateRGB()
{
	int  ch;
	cout << "choose \n [ 1 ] rotate 90 \n [ 2 ] rotate 180 \n [ 3 ] rotate 270 \n choice : ";
	cin >> ch;
	if (ch == 1)
	{
		rotate();
	}

	else if (ch == 2)
	{
		rotate();
		rotate();
	}
	else if (ch == 3)
	{
		rotate();
		rotate();
		rotate();
	}
	//cin.ignore();
}


//shuffle image parts
void shuffle_imageRGB()
{
	int ch[4];

	cout << "Enter all order of photos separeted by spaces : ";
	for (int i = 0; i < 4; i++)
		cin >> ch[i];

	int x = 0, y = 0;
	//to store new image parts
	int imaget[SIZE][SIZE][RGB] = {0};

	// first quarter
	int imaget1[SIZE / 2][SIZE / 2][3];

	// second quarter
	int imaget2[SIZE / 2][SIZE / 2][3];

	// third quarter
	int imaget3[SIZE / 2][SIZE / 2][3];

	// fourth quarter
	int imaget4[SIZE / 2][SIZE / 2][3];

	// fill first part of image
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = 0; j < SIZE / 2; j++)
		{
			for (int k = 0; k < 3; k++)
				imaget1[i][j][k] = image2[i][j][k];
		}
	}
	// fill second part of image
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = SIZE / 2; j < SIZE; j++)
		{
			for (int k = 0; k < 3; k++)
				imaget2[x][y][k] = image2[i][j][k];
			y++;
		}
		y = 0;
		x++;
	}

	// fill third part of image
	x = 0, y = 0;
	for (int i = SIZE / 2; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE / 2; j++)
		{
			for (int k = 0; k < 3; k++)
				imaget3[x][y][k] = image2[i][j][k];
			y++;
		}
		y = 0;
		x++;
	}

	// fill fourth part of image
	x = 0, y = 0;
	for (int i = SIZE / 2; i < SIZE; i++)
	{
		for (int j = SIZE / 2; j < SIZE; j++)
		{
			for (int k = 0; k < 3; k++)
				imaget4[x][y][k] = image2[i][j][k];
			y++;
		}
		y = 0;
		x++;
	}

	int count = 0;
	for (int s : ch)
	{
		x = 0, y = 0;
		if (count == 0)
		{
			for (int i = 0; i < SIZE / 2; i++)
			{
				for (int j = 0; j < SIZE / 2; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (s == 1)
							imaget[i][j][k] = imaget1[i][j][k];
						else if (s == 2)
							imaget[i][j][k] = imaget2[i][j][k];
						else if (s == 3)
							imaget[i][j][k] = imaget3[i][j][k];
						else if (s == 4)
							imaget[i][j][k] = imaget4[i][j][k];
					}
				}
			}
		}

		else if (count == 1)
		{
			for (int i = 0; i < SIZE / 2; i++)
			{
				for (int j = SIZE / 2; j < SIZE; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (s == 1)
							imaget[i][j][k] = imaget1[x][y][k];
						else if (s == 2)
							imaget[i][j][k] = imaget2[x][y][k];
						else if (s == 3)
							imaget[i][j][k] = imaget3[x][y][k];
						else if (s == 4)
							imaget[i][j][k] = imaget4[x][y][k];
					}
					y++;
				}
				y = 0;
				x++;
			}
		}

		else if (count == 2)
		{
			for (int i = SIZE / 2; i < SIZE; i++)
			{
				for (int j = 0; j < SIZE / 2; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (s == 1)
							imaget[i][j][k] = imaget1[x][y][k];
						else if (s == 2)
							imaget[i][j][k] = imaget2[x][y][k];
						else if (s == 3)
							imaget[i][j][k] = imaget3[x][y][k];
						else if (s == 4)
							imaget[i][j][k] = imaget4[x][y][k];
					}
					y++;
				}
				y = 0;
				x++;
			}
		}

		else if (count == 3)
		{
			for (int i = SIZE / 2; i < SIZE; i++)
			{
				for (int j = SIZE / 2; j < SIZE; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						if (s == 1)
							imaget[i][j][k] = imaget1[x][y][k];
						else if (s == 2)
							imaget[i][j][k] = imaget2[x][y][k];
						else if (s == 3)
							imaget[i][j][k] = imaget3[x][y][k];
						else if (s == 4)
							imaget[i][j][k] = imaget4[x][y][k];
					}
					y++;
				}
				y = 0;
				x++;
			}
		}

		count++;
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < 3; k++)
				image2[i][j][k] = imaget[i][j][k];
		}
	}
}

void flipImageHorizontally()
{
	// flip horizontally
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE / 2; j++)
		{
			swap(image2[i][j], image2[i][SIZE - 1 - j]);
		}
	}
}

void flipImageVertically()
{
	// flip vertically
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			swap(image2[i][j], image2[SIZE - 1 - i][j]);
		}
	}
}

void mirrorDown()
{
	//mirror the down side
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int l = 0; l < RGB; ++l)
			{
				image2[i][j][l] = image2[255 - i][j][l];
			}
		}
	}
}

void mirrorUp()
{
	//mirror the upper side
	for (int i = 0; i < SIZE / 2; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int l = 0; l < RGB; ++l)
			{
				image2[255 - i][j][l] = image2[i][j][l];
			}
		}
	}
}

void mirrorLeft()
{
	// mirror the left side
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE / 2; j++)
		{
			for (int l = 0; l < RGB; ++l)
			{
				image2[i][255 - j][l] = image2[i][j][l];
			}
		}
	}
}

void mirrorRight()
{
	//mirror the right side
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE / 2; j++)
		{
			for (int l = 0; l < RGB; ++l)
			{
				image2[i][j][l] = image2[i][255 - j][l];
			}
		}
	}
}

void detectImageEdges()
{
	//convert black and white
	ConvertBlackAndWhiteRGB();

	// detect the edges
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int l = 0; l < RGB; ++l)
			{
				if (image2[i][j][l] == image2[i][j + 1][l])
				{
					image2[i][j][l] = 255;
				}
				else
				{
					image2[i][j][l] = 0;
				}
			}
		}
	}
}

void mergeImages()
{
	loadRGBImage2();
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				image2[i][j][k] = (image2[i][j][k] + image3[i][j][k]) / 2;
			}
		}
	}
}

void darken_Lighten()
{
	string s;
	cout << "To darken an image press d\nTo lighten an image press l\n";
	cin >> s;
	if (s == "d")
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					image2[i][j][k] *= 0.5;
				}
			}
		}
	}
	else if (s == "l")
	{
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					if (image2[i][j][k] < 170)
					{
						image2[i][j][k] *= 1.5;
					}
					else
					{
						image2[i][j][k] = 255;
					}
				}
			}
		}
	}
}

void shrink()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				image3[i][j][k] = image2[i][j][k];
			}
		}
	}
	int index_i = 0, index_j = 0, value, new_size;
	cin.ignore();
	cout << "enter a shrink value : ";
	cin >> value;
	new_size = SIZE / value;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				if (i < new_size && j < new_size)
				{
					image2[i][j][k] = image3[index_i][index_j][k];
				}
				else
				{
					image2[i][j][k] = 255;
				}
			}
			index_j += value;
		}
		index_j = 0;
		index_i += value;
	}
}

void blurImage()
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				image3[i + 1][j + 1][k] = image2[i][j][k];
			}
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				image2[i][j][k] = (image3[i][j][k] + image3[i][j + 1][k] + image3[i][j + 2][k] + image3[i + 1][j][k] + image3[i + 1][j + 2][k] + image3[i + 2][j][k] + image3[i + 2][j + 1][k] + image3[i + 2][j + 2][k]) / 9;
			}
		}
	}
}

int main()
{
	string choice, flipDetect, mirordetect;
	bool contin = true, load = true;

	while (contin)
	{
		if (load)
		{
			loadRGBImage();
			load = false;
		}

		cout << "\n\n";
		cout << "Enter The Number of the operation \n";
		cout << "1- Black & White Filter \n";
		cout << "2- Invert Image\n";
		cout << "3- Merge Images \n";
		cout << "4- Flip Image \n";
		cout << "5- Rotate Image\n";
		cout << "6- Darken & Lighten an image \n";
		cout << "7- Detect Image Edges \n";
		cout << "8- Enlarge Image\n";
		cout << "9- Shrink an Image \n";
		cout << "a- Mirror 1/2 Image \n";
		cout << "b- Shuffle Image\n";
		cout << "c- Blur an Image \n";
		cout << "s- Save the image to a file \n";
		cout << "n- Make new edit \n";
		cout << "0- Exit \n\n";
		cout << ">>>> ";
		cin >> choice;

		if (choice == "1")
		{
			ConvertBlackAndWhiteRGB();
		}
		else if (choice == "2")
		{
			invertRGB();
		}
		else if (choice == "3")
		{
			mergeImages();
		}
		else if (choice == "4")
		{
			cout << "Flip (h)orizontally or (v)ertically ? \n";
			cin >> flipDetect;

			if (flipDetect == "h")
			{
				flipImageHorizontally();
			}

			else if (flipDetect == "v")
			{
				flipImageVertically();
			}
		}
		else if (choice == "5")
		{
			rotateRGB();
		}

		else if (choice == "6")
		{
			darken_Lighten();
		}
		else if (choice == "7")
		{
			detectImageEdges();
		}

		else if (choice == "8")
		{
			enlargeRGB();
		}

		else if (choice == "9")
		{
			shrink();
		}
		else if (choice == "a")
		{
			cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side? \n";
			cin >> mirordetect;

			if (mirordetect == "d")
			{
				mirrorDown();
			}

			else if (mirordetect == "u")
			{
				mirrorUp();
			}

			else if (mirordetect == "l")
			{
				mirrorLeft();
			}

			else if (mirordetect == "r")
			{
				mirrorRight();
			}
		}

		else if (choice == "b")
		{
			shuffle_imageRGB();
		}

		else if (choice == "c")
		{
			blurImage();
		}
		else if (choice == "n")
		{
			load = true;
		}
		else if (choice == "s")
		{
			saveRGBImage();
		}

		else if (choice == "0")
		{
			cout << "HAVE A NICE DAY !! \n";
			contin = false;
		}

		else
		{
			cout << "Please enter a VALID number ";
		}
	}
	return 0;
}
