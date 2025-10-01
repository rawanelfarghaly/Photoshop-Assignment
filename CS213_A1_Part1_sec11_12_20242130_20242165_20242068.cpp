//FILE: CS213_A1_Part1_sec11/12_20242068_20242130_20242165

//Section: 11/12
// Names and IDs

//ID: 20242130 => Rawan Youssry Ebrahim
//ID: 20242165 => Salma Mohammed
//ID: 20242068 => Aya Mohammad Mohammad

//Filters distribution:

//20242130 : Filter 2: Black and white, Filter 5: Flipping images
//20242165 : Filter 3: Invert images, Filter 6: Blur images
//20242068 : filter 1: gray scale, filter 4: merge 2 images


#include <iostream>
#include <cstdlib>

using namespace std;
#include "Image_Class.h"

 int Save = 1;
 bool Exit = false;
 string filename, file1, file2;
 int choose = 0;

enum enFilter{grayscale = 2, Black_and_white = 3,Invert_Filter = 4, merge_2_images = 5, Flip_image = 6, Blur_Image = 7 };

void Choices()
{
	cout << "\n Please choose what you want:\n\n";
	cout << "(1) Load new image\n";
	cout << "(2) Filter 1: Convert image to Gray scale\n";
	cout << "(3) Filter 2: Convert image to Black and white\n";
	cout << "(4) Filter 3: Invert image\n";
	cout << "(5) Filter 4: Merge 2 images\n";
	cout << "(6) Filter 5: Flip the image:\n    A_Vertically\n    B_Horizontally \n";
	cout << "(7) Filter 6: Blur Image\n";
	cout << "(8) Save image\n";
	cout << "(9) Exit\n";
}

void SaveFunction(Image& image, string& filename)
{

	cout << "If you want to save changes enter 1\n";
	cin >> Save;
	if (Save == 1)
	{
		cout << "Please choose:\n";
		cout << "(1) Save at the same file\n";
		cout << "(2) Save at new file\n";

		int choose;
		cin >> choose;

		switch (choose)
		{
		case 1:
			image.saveImage(filename);
			break;
		case 2:
			cout << "Please enter image name to store new image and and specify extension .jpg, .bmp, .png, .tga: \n";

			cin >> filename;

			image.saveImage(filename);
			break;
		default:
			cout << "Invalid choice\n";
			break;
		}
	}
}

void ExitFunction(Image& image, string& filename)
{
	if (Exit == true)
	{
		Image image(filename);
		SaveFunction(image, filename);
	}

}

void gray_scale(Image& image, string& filename)
{
	for (int w = 0; w < image.width; ++w)
	{
		for (int h = 0; h < image.height; ++h)
		{
			unsigned avg = 0;
			for (int c = 0; c < 3; ++c) 
			{
				avg += image(w, h, c);
			}
			avg /= 3;
			image(w, h, 0) = avg;
			image(w, h, 1) = avg;
			image(w, h, 2) = avg;
		}
	}
    SaveFunction( image, filename);
	system(filename.c_str());
}

void BlackAndWhite(Image& image, string& filename)
{

	for (int i = 0; i < image.width; ++i) {
		for (int j = 0; j < image.height; ++j) {
			unsigned  int avg = 0;

			for (int k = 0; k < 3; ++k) {
				avg += image(i, j, k);
			}

			avg /= 3;
			if (avg >= 127)
			{
				image(i, j, 0) = 255;
				image(i, j, 1) = 255;
				image(i, j, 2) = 255;
			}
			else
			{
				image(i, j, 0) = 0;
				image(i, j, 1) = 0;
				image(i, j, 2) = 0;
			}

		}
	}
	SaveFunction( image, filename);
	system(filename.c_str());
}

void InvertFilter(Image& image, string& filename)
{
	for (int x = 0; x < image.width; ++x)
	{
		for (int y = 0; y < image.height; ++y) 
		{
			image(x, y, 0) = 255 - image(x, y, 0);
			image(x, y, 1) = 255 - image(x, y, 1);
			image(x, y, 2) = 255 - image(x, y, 2);
		}
	}
	SaveFunction(image, filename);
	system(filename.c_str());
}

void Merge2images(Image& image, string& filename)
 {
    string file1, file2;
    cout << "enter the name of first image\n";
    cin >> file1;
    cout << "enter the name of second image\n";
    cin >> file2;

    Image image1(file1);
    Image image2(file2);

    if (image1.height == image2.height && image1.width == image2.width)
	{
        for (int h = 0; h < image1.height; h++) 
		{
            for (int w = 0; w < image1.width; w++)
			{
                for (int c = 0; c < 3; c++) {
                    unsigned char temp = (image1(w, h, c) + image2(w, h, c)) / 2;
                    image1(w, h, c) = temp;
                }
            }
        }
        image1.saveImage(filename);
        SaveFunction(image1, filename);
        system(filename.c_str());
    }
    else { 
        cout << "select merge type: 1-resize image to the larger size and merge, 2-merge the common area only\n";
        int choice;
        cin >> choice;

        int maxHeight = 0, maxWidth = 0;
        int minHeight = 0, minWidth = 0;
        Image newImage(1, 1);

        if (choice == 1) { 
            maxHeight = max(image1.height, image2.height);
            maxWidth = max(image1.width, image2.width);
            newImage = Image(maxWidth, maxHeight);

            for (int h = 0; h < maxHeight; h++)
			{
                for (int w = 0; w < maxWidth; w++)
				{
                    for (int c = 0; c < 3; c++)
					{
                        unsigned char temp = 0;
                        if (h < image1.height && w < image1.width) temp += image1(w, h, c) / 2;
                        if (h < image2.height && w < image2.width) temp += image2(w, h, c) / 2;
                        newImage(w, h, c) = temp;
                    }
                }
            }
        }
        else if (choice == 2)
		{ 
            minHeight = min(image1.height, image2.height);
            minWidth = min(image1.width, image2.width);
            newImage = Image(minWidth, minHeight);

            for (int h = 0; h < minHeight; h++)
			{
                for (int w = 0; w < minWidth; w++) 
				{
                    for (int c = 0; c < 3; c++) 
					{
						unsigned char temp = 0; if (h < image1.height && w < image1.width) temp += image1(w, h, c) / 2;
						if (h < image2.height && w < image2.width) temp += image2(w, h, c) / 2;
						unsigned char temp2 = 0; if (h < image1.height && w < image1.width) temp2 += image1(w, h, c) / 2;
						if (h < image2.height && w < image2.width) temp2 += image2(w, h, c) / 2;
                        newImage(w, h, c) = temp;
                    }
                }
            }
        }
        else {
            cout << "Invalid choice\n";
            return;
        }

		newImage.saveImage(filename);
		SaveFunction(newImage, filename);
		system(filename.c_str());
    }
}


void FlipImage(Image& image, string& filename)
{
	
	cout << "\n\nplease Choose what you want: \n(1) Vertically \n(2) Horizontally\n\n";
	int Choose;
	cin >> Choose;

	switch (Choose)
	{
	case 1:
		for (int i = 0; i < image.width; ++i) {
			for (int j = 0; j < image.height / 2; ++j) {
				for (int k = 0; k < 3; ++k) {
					unsigned int temp = image(i, j, k);
					image(i, j, k) = image(i, image.height - 1 - j, k);
					image(i, image.height - 1 - j, k) = temp;
				}
			}
		}
		
		SaveFunction(image, filename);
		system(filename.c_str());
		break;
	case 2:

		for (int i = 0; i < image.width / 2; ++i) {
			for (int j = 0; j < image.height; ++j) {
				for (int k = 0; k < 3; ++k) {
					unsigned int temp2 = image(i, j, k);
					image(i, j, k) = image(image.width - 1 - i, j, k);
					image(image.width - 1 - i, j, k) = temp2;
				}
			}
		}
		SaveFunction(image, filename);
		system(filename.c_str());
		break;
	default:
		cout << "Invalid choose\n";
		break;
	}
}

void BlurFilter(Image& image, string& filename)
{
	int strength;
	cout << "Enter blur strength (odd number, e.g. 15, 21, 25): \n";
	cin >> strength;

	if (strength % 2 == 0) strength++;
	int offset = strength / 2;

	Image temp = image;

	for (int i = offset; i < image.width - offset; i++) 
	{
		for (int j = offset; j < image.height - offset; j++) 
		{
			for (int k = 0; k < 3; k++) {
				int sum = 0;
				int count = 0;

				for (int x = -offset; x <= offset; x++) 
				{
					for (int y = -offset; y <= offset; y++) 
					{
						sum += image(i + x, j + y, k);
						count++;
					}
				}

				temp(i, j, k) = sum / count;
			}
		}
	}

	SaveFunction(image, filename);
	system(filename.c_str());

	image = temp;
	cout << "Blur applied.\n";
}

void Menue(Image& image, string& filename)
{	

	Choices();

	int Choose;
	cin >> Choose;

	switch (Choose)
	{
	case 1:

		cout << "enter the name of image\n";
		cin >> filename;
		Menue(image, filename);
		break;

	case enFilter::grayscale :

		gray_scale(image, filename);
		break;

	case enFilter::Black_and_white :

		BlackAndWhite(image, filename);
		break;

	case enFilter::Invert_Filter :
		InvertFilter(image, filename);
		break;
	
	case enFilter::merge_2_images:
		Merge2images(image, filename);
		break;

	case enFilter::Flip_image:

		FlipImage(image, filename);
		break;

	case enFilter::Blur_Image :
		BlurFilter(image, filename);
		break;

	case 8:
		SaveFunction(image, filename);
		system(filename.c_str());
	    break;
	case 9:
		ExitFunction(image, filename);
		break;
	default:
		cout << "Invalid choice\n";
		break;
    }
	
	
}


int main()
{
	cout << "Please enter image\n";
	cin >> filename;
	Image image(filename);

	do 
	{
		Menue(image, filename);
		cout << "if you want to Exit please enter 1 and if you do not want to exit enter 0\n";
		cin >> Exit;
		if (Exit == 1) {
			ExitFunction(image, filename);
		}
	} while (Exit == false);
	
}